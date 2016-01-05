from django_socketio.events import on_connect
from django_socketio.events import on_message
from django_socketio.events import on_disconnect
from django_socketio import broadcast
from calc import Color
from calc import CommandManager

cm = CommandManager()
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
	del game['players'][tmp_k]
	sendPlayersList()

@on_message
def messageFromPlayer(request, socket, context, message):
	global game
	print '>>>> ', message
	if message['action'] == 'join':
		game['players'][message['name']]= \
			{'state': False, 'socket': socket.session.session_id}
		socket.send({'action':'info', 'content': 'Dodany.'})
		sendPlayersList()
	elif message['action'] == 'getPlayers':
		socket.send({'action':'playersList', 'list': game['players']})
	elif message['action'] == 'ready':
		game['players'][message['name']]['state'] = message['is_ready']
		sendPlayersList()
		all_ready = True
		for p in game['players'].itervalues():
			if not p['state']:
				all_ready = False
		if all_ready:
			game['state']=1
			broadcast({'action': 'gameState', 'state':1})

def sendPlayersList():
	global game
	broadcast({'action':'playersList', 'list': game['players']})