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
	# cv.removePlayer(message['name'])
	del game['players'][tmp_k]
	sendPlayersList()

@on_message
def messageFromPlayer(request, socket, context, message):
	global game
	print '>>>> ', message
	act = message['action']

	if act == 'join':
		if game['state'] != 0:
			# gra juz trwa
			socket.send({'action': 'joinState', 'joined': False, 'reason': 'gameInProgress'})
		elif game['players'].__len__() > 3:
			# za duzo graczy
			socket.send({'action': 'joinState', 'joined': False, 'reason': 'playersCount'})
		elif message['name'] in game['players']:
			# gracz o podanym imieniu istnieje
			socket.send({'action': 'joinState', 'joined': False, 'reason': 'nameNotAvailable'})
		else:
			game['players'][message['name']]= \
				{'ready': False, 'socket': socket.session.session_id, 'color': Color.NONE.real}
			socket.send({'action':'joinState', 'joined': True})
			sendPlayersList()
	elif act == 'getColor':
		for p in game['players'].itervalues():
			if p['socket'] == socket.session.session_id:
				socket.send({'action': 'setColor', 'color': p['color'].real})
	elif act == 'getPlayers':
		socket.send({'action':'playersList', 'list': game['players']})
	elif act == 'ready':
		all_ready = True
		for p in game['players'].itervalues():
			if p['socket'] == socket.session.session_id:
				p['ready'] = message['is_ready']
			if not p['ready']:
				all_ready = False
		sendPlayersList()
		if all_ready:
			colors = (Color.BLUE, Color.RED, Color.YELLOW, Color.GREEN)
			i=0
			for name in game['players'].iterkeys():
				game['players'][name]['color'] = colors[i].real
				cv.addPlayer(name)
				i=i+1
			game['state']=1
			broadcast({'action': 'gameState', 'state':1})

def sendPlayersList():
	global game
	broadcast({'action':'playersList', 'list': game['players']})