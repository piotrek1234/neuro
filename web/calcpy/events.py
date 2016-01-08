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

#game['state']: 0=oczekiwanie na graczy, 1=gra, 2=bitwa koncowa, 3=gra zakonczona
game = {'state': 0,
		'players': {},
		'current_player': ''
		}

@on_connect
def playerConnected(request, socket, context):
	print '>>>> connected'
	socket.send({'action':'hello', 'gameState': game['state']})

@on_disconnect
def playerDisconnected(request, socket, context):
	global game
	tmp_k = ''
	for k, v in game['players'].iteritems():
		if v['socket'] == socket.session.session_id:
			print '>>>> ', k, ' disconnected'
			tmp_k = k
	# usunac gracza z c++
	# cv.removePlayer(message['name'])
	if not tmp_k:
		del game['players'][tmp_k]
	if game['players'].__len__() == 0:
		cv.restartGame()
		game['state'] = 0
	sendPlayersList()

@on_message
def messageFromPlayer(request, socket, context, message):
	global game
	print '>>>> ', message
	act = message['action']

	# oczekiwanie na graczy: join, getColor, getPlayers, ready
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
			socket.send({'action':'joinState', 'joined': True, 'playerName': message['name']})
			sendPlayersList()
	elif act == 'getColor':
		socket.send({'action': 'setColor', 'color': game['players'][getNameBySocket(socket)]['color']})
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
			if game['players'].__len__() > 1:
				#colors = (Color.BLUE, Color.RED, Color.YELLOW, Color.GREEN)
				i=1
				for name in game['players'].iterkeys():
					game['players'][name]['color'] = i
					cv.addPlayer(name)
					i=i+1
				game['state']=1
				broadcast({'action': 'gameState', 'state': 1})
				player = cv.getCurrentPlayer()
				tokens = {}
				game['current_player'] = player['name']
				for i in player['tokens']:
					tokens[i] = cv.getTokenHand(i, player['color'])
					tokens[i]['color'] = tokens[i]['color'].real
				broadcast({'action': 'turn', 'player': player['name'] ,'tokens': tokens})

	# wlasciwa rozgrywka
	elif act == 'nextTurn':
		if getNameBySocket(socket) == game['current_player']:
			player = cv.getNextPlayer()
			game['current_player'] = player['name']
			tokens = {}
			for i in player['tokens']:
				tokens[i] = cv.getTokenHand(i, player['color'])
				tokens[i]['color'] = tokens[i]['color'].real
			if tokens.__len__() == 0:
				game['state'] = 2
				performBattle()
				#
			else:
				broadcast({'action': 'turn', 'player': player['name'] ,'tokens': tokens})
		else:
			sendError(socket, 'notYourTurn')
	elif act == 'putToken':
		if getNameBySocket(socket) == game['current_player']:
			color = Color.values[game['players'][getNameBySocket(socket)]['color']]
			added = cv.addToken(message['id'], color, message['q'], message['r'], message['angle'])
			if added:
				token = cv.getTokenBoard(message['q'], message['r'])
				broadcast({'action': 'tokenAdded', 'color': color.real, 'id': message['id'],\
					'name': token['name'],'q': message['q'], 'r': message['r'], 'angle': message['angle']})
			else:
				sendError(socket, 'addFailed')
		else:
			sendError(socket, 'notYourTurn')
	# byc moze nie potrzebne
	elif act == 'currentPlayer':
		player = cv.getCurrentPlayer()
		tokens = {}
		for i in player['tokens']:
			tokens[i] = cv.getTokenHand(i, player['color'])
			tokens[i]['color'] = tokens[i]['color'].real
		socket.send({'action': 'turn', 'player': player['name'] ,'tokens': tokens})
	elif act == 'move':
		if getNameBySocket(socket) == game['current_player']:
			player = cv.getCurrentPlayer()
			token = cv.getTokenBoard(message['src_q'], message['src_r'])
			if token.__len__() == 0:
				sendError(socket, 'moveFailed')
				return
			moved = cv.actionTokenMove(message['token'], player['color'], message['src_q'], message['src_r'], \
				message['dst_q'], message['dst_r'])
			if moved:
				# broadcast: info o przesunietym tokenie
				broadcast({'action': 'tokenMoved', 'id': token['id'], 'color': token['color'].real, \
					'src_q': message['src_q'], 'src_r': message['src_r'], 'dst_q': message['dst_q'], \
					'dst_r': message['dst_r'], 'name': token['name']})
			else:
				sendError(socket, 'moveFailed')
		else:
			sendError(socket, 'notYourTurn')
	elif act == 'push':
		if getNameBySocket(socket) == game['current_player']:
			player = cv.getCurrentPlayer()
			token = cv.getTokenBoard(message['src_q'], message['src_r'])
			if token.__len__() == 0:
				sendError(socket, 'pushFailed')
				return
			pushed = cv.getTokenBoard(message['dst_q'], message['dst_r'])
			if pushed.__len__() == 0:
				sendError(socket, 'pushFailed')
				return
			moved = cv.actionTokenPush(message['token'], player['color'], message['src_q'], message['src_r'], \
				message['dst_q'], message['dst_r'])
			if moved:
				pushed_q = 2*message['dst_q']-message['src_q']
				pushed_r = 2*message['dst_r']-message['src_r']
				broadcast({'action': 'tokenMoved', 'id': pushed['id'], 'color': pushed['color'].real, \
					'src_q': message['dst_q'], 'src_r': message['dst_r'], 'dst_q': pushed_q, \
					'dst_r': pushed_r, 'name': pushed['name']})
			else:
				sendError(socket, 'pushFailed')
		else:
			sendError(socket, 'notYourTurn')
	elif act == 'battle':
		if getNameBySocket(socket) == game['current_player']:
			player = cv.getCurrentPlayer()
			performBattle(message['token'], player['color'])
			#broadcast({'action': 'battle', 'newBoard': board})
			#broadcast o smierci graczy
			#ewentualny broadcast o koncu gry
		else:
			sendError(socket, 'notYourTurn')
	elif act == 'getBoard':
		socket.send({'action': 'board', 'board': getBoard()})
		print cv.getBoard()

def sendPlayersList():
	global game
	broadcast({'action':'playersList', 'list': game['players']})

def getNameBySocket(socket):
	for k, v in game['players'].iteritems():
			if v['socket'] == socket.session.session_id:
				return k

def performBattle(tokenActionId, color):
	#cv.battle
	#przeslac plansze
	#ustawic zycie graczom
	#przeslac aktualna liste graczy
	#przeslac plansze po bitwie
	if game['state'] == 1:
		#next turn
		pass
	else:
		#koniec gry
		game['state'] = 2
		#oglosic wyniki

def sendError(socket, error):
	socket.send({'action': 'error', 'errCont': error})

def getBoard():
	board = cv.getBoard()
	retbrd = {}
	i=0
	for k, v in board.iteritems():
		v['color'] = v['color'].real
		retbrd[i] = {'q': k[0], 'r': k[1], 'token': v}
		i=i+1
	return retbrd