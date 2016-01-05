from django_socketio.events import on_connect, on_message, on_disconnect
from django_socketio import broadcast
from calc import Color
from calcpy import views as cv

# Color na int: Color.RED.real lub Color.RED.__int__()
# int na Color: Color.values[liczba]

cv.addTokenConfigPath(Color.BLUE, 'calc/blue.xml')
cv.addTokenConfigPath(Color.RED, 'calc/red.xml')
cv.addTokenConfigPath(Color.GREEN, 'calc/green.xml')
cv.addTokenConfigPath(Color.YELLOW, 'calc/yellow.xml')

game = {'state': 0,
		'players': {},
		'current_player': ''
		}

@on_connect
def playerConnected(request, socket, context):
	print '>>>> connected'
	socket.send({'action':'hello'})

@on_disconnect
def playerDisconnected(request, socket, context):
	global game
	for k, v in game['players'].iteritems():
		if v['socket'] == socket.session.session_id:
			print '>>>> ', k, ' disconnected'
			tmp_k = k
	# usunac gracza z c++
	# cv.removePlayer(message['name'].encode("utf-8"))
	del game['players'][tmp_k]
	sendPlayersList()

@on_message
def messageFromPlayer(request, socket, context, message):
	global game
	print '>>>> ', message
	act = message['action']
	if act == 'join':
		#brakuje sprawdzania czy taki gracz juz jest i czy nie ma za duzo graczy
		#cv.addPlayer przydziela kolor od razu, trzeba to zgrac ze soba
		game['players'][message['name']]= \
			{'ready': False, 'socket': socket.session.session_id, 'color': Color.NONE.real}
		cv.addPlayer(message['name'].encode("utf-8"))
		socket.send({'action':'info', 'content': 'Dodany.'})
		sendPlayersList()
	elif act == 'getColor':
		for p in game['players'].itervalues():
			if p['socket'] == socket.session.session_id:
				socket.send({'action': 'setColor', 'color': p['color'].real})
	elif act == 'getPlayers':
		socket.send({'action':'playersList', 'list': game['players']})
	elif act == 'ready':
		game['players'][message['name']]['ready'] = message['is_ready']
		sendPlayersList()
		all_ready = True
		for p in game['players'].itervalues():
			if not p['ready']:
				all_ready = False
		if all_ready:
			colors = (Color.BLUE, Color.RED, Color.YELLOW, Color.GREEN)
			i=0
			for name in game['players'].iterkeys():
				game['players'][name]['color'] = colors[i].real
				i=i+1
			game['state']=1
			broadcast({'action': 'gameState', 'state':1})

def sendPlayersList():
	global game
	broadcast({'action':'playersList', 'list': game['players']})