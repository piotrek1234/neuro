## @file calcpy/events.py
#  @brief websockets events handler

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
	'''handles new connections from players'''
	print '>>>> connected'
	socket.send({'action':'hello', 'gameState': game['state']})

@on_disconnect
def playerDisconnected(request, socket, context):
	'''handles player disconnect event'''
	global game
	tmp_k = ''
	for k, v in game['players'].iteritems():
		if v['socket'] == socket.session.session_id:
			print '>>>> ', k, ' disconnected'
			if game['state'] == 1:
				cv.killPlayer(Color.values[v['color']])
				if game['current_player'] == k:
					nextTurn()
			tmp_k = k

	if tmp_k != '':
		del game['players'][tmp_k]
		if (game['players'].__len__() == 1 and game['state'] == 1):
			game['state'] = 3
			for i in game['players'].iterkeys():
				winner = i
			broadcast({'action': 'gameEnd', 'winner': winner})
	if game['players'].__len__() == 0:
		cv.restartGame()
		game['state'] = 0
	sendPlayersList()

@on_message
def messageFromPlayer(request, socket, context, message):
	'''handles messages from players'''
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
				{'ready': False, 'socket': socket.session.session_id, 'color': Color.NONE.real, 'life': 20}
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
				tokens = []
				game['current_player'] = player['name']
				for i in player['tokens']:
					tokens.append(cv.getTokenHand(i, player['color']))
					tokens[-1]['color'] = tokens[-1]['color'].real
				broadcast({'action': 'turn', 'player': player['name'] ,'tokens': tokens, \
					'stackSize': player['stack_size']})

	# wlasciwa rozgrywka
	elif act == 'nextTurn':
		if getNameBySocket(socket) == game['current_player']:
			nextTurn()
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
	elif act == 'throw':
		if getNameBySocket(socket) == game['current_player']:
			thrown = cv.throwToken(message['id'], \
				Color.values[game['players'][getNameBySocket(socket)]['color']])
			if thrown:
				currentTurn()
			else:
				sendError(socket, 'throwFailed')
		else:
			sendError(socket, 'notYourTurn')
	# byc moze nie potrzebne
	elif act == 'currentPlayer':
		currentTurn()
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
		else:
			sendError(socket, 'notYourTurn')
	elif act == 'getBoard':
		socket.send({'action': 'board', 'board': getBoard()})
		print cv.getBoard()

def sendPlayersList():
	'''broadcasts updated list of players'''
	global game
	broadcast({'action':'playersList', 'list': game['players']})

def getNameBySocket(socket):
	'''finds name of player based on given socket'''
	for k, v in game['players'].iteritems():
		if v['socket'] == socket.session.session_id:
			return k

def getNameByColor(color):
	'''finds name of player based on given color'''
	for k, v in game['players'].iteritems():
		if v['color'] == color:
			return k

def nextTurn():
	'''changes turn for next player'''
	player = cv.getNextPlayer()
	game['current_player'] = player['name']
	tokens = []
	for i in player['tokens']:
		tokens.append(cv.getTokenHand(i, player['color']))
		tokens[-1]['color'] = tokens[-1]['color'].real
	if tokens.__len__() == 0:
		# bitwa koncowa
		game['state'] = 2
		performBattle()
	elif isBoardFull():
		performBattle()
	elif game['players'][player['name']]['life'] < 1:
		nextTurn()
	else:
		broadcast({'action': 'turn', 'player': player['name'] ,'tokens': tokens, \
			'stackSize': player['stack_size']})

def isBoardFull():
	'''tells if board has no empty hexes'''
	if cv.getBoard().__len__() == 19:
		return True
	else:
		return False

def currentTurn():
	'''broadcasts information about current player and his tokens on hand'''
	player = cv.getCurrentPlayer()
	tokens = []
	for i in player['tokens']:
		tokens.append(cv.getTokenHand(i, player['color']))
		tokens[-1]['color'] = tokens[-1]['color'].real
	broadcast({'action': 'turn', 'player': player['name'] ,'tokens': tokens, \
			'stackSize': player['stack_size']})

def performBattle(tokenActionId=-1, color=Color.NONE):
	'''handles battle and its effects'''
	if tokenActionId == -1:
		cv.performBattle()
	else:
		cv.actionTokenBattle(tokenActionId, color)
	#ustawic zycie graczom
	life = {}
	for col in (1,2,3,4):
		life[col] = 0

	board = getBoard()

	# znalezienie hq i przypisanie ich zycia odpowiedniemu kolorowi
	for tok in board.itervalues():
		#print tok['token']
		if 'hq' in tok['token']['name']:
			life[tok['token']['color']] = tok['token']['life']

	# przypisanie kazdemu graczowi zycia na podstawie zycia hq
	for player in game['players'].itervalues():
		player['life'] = life[player['color']]

	# sprawdzenie czy zyje tylko 1 gracz
	alive = 0
	best = 0
	for name, p in game['players'].iteritems():
		if p['life'] > 0:
			alive = alive + 1
		if p['life'] > best:
			best = p['life']
			winner = name

	if alive == 1:
		game['state'] = 3

	broadcast({'action': 'afterBattle', 'board': board, 'players': game['players']})

	if game['state'] == 1:
		nextTurn()
	else:	# 2 lub 3
		#koniec gry
		game['state'] = 3
		broadcast({'action': 'gameEnd', 'winner': winner})

def sendError(socket, error):
	'''builds and sends error message'''
	socket.send({'action': 'error', 'errCont': error})

def getBoard():
	'''returns tokens on board in form readable by javascript'''
	board = cv.getBoard()
	retbrd = []
	i=0
	for k, v in board.iteritems():
		v['color'] = v['color'].real
		retbrd.append({'q': k[0], 'r': k[1], 'token': v})
		i=i+1
	return retbrd