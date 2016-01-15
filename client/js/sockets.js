/*
 *  trzymane w sessionStorage:
 *	playerName - własne imię
 *	playerColor - własny kolor
 *	currentTurn - imię gracza który teraz wykonuje ruch
 *	players - słownik z graczami (klucz: imię gracza)
 *		{'color': int - kolor gracza
 *		 'tokens': lista intów - żetonów na ręku gracza
 *		}
 */
var on_connected = function()
{
	sessionStorage.clear();
	socket.send({'action': 'getPlayers'});
}

var on_received = function(data)
{
	if(data.action)
	{
		switch(data.action){
			case 'playersList':
				console.log(data.list);

				playerListEvents.forEach(function (callback) {
					callback(data.list);
				});

				//zaktualizować listę graczy: imię, stan
				break;
			case 'setColor':
				console.log('My color: '+data.color);
				sessionStorage.setItem('playerColor', data.color);
				//przydzielić gdzieś graczowi kolor
				setColorEvents.forEach(function (callback) {
					callback(data.color);
				});
				break;
			case 'gameState':
				if(data.state == 1)
				{
					socket.send({'action': 'getColor'});
					console.log('All ready. Game state: '+data.state);
				}
				gameStateEvents.forEach(function (callback) {
					callback(data.state);
				});
				break;
			case 'hello':
				console.log('Connected. Game state: '+data.gameState);
				gameStateEvents.forEach(function (callback) {
					callback(data.gameState);
				});
				break;
			case 'joinState':
				if(data.joined == true)
				{
					console.log('Joined game as '+data.playerName+'.');
					sessionStorage.setItem('playerName', data.playerName);
					//ukryć pole do wpisywania imienia
					joinStateEvents.forEach(function (callback) {
						callback(data.joined, data.playerName);
					});
				}	
				else
				{
					console.log('Failed to join. Reason: '+data.reason);
					//nie ukrywać pola, ewentualnie wyświetlić komunikat czemu się nie udało
					joinStateEvents.forEach(function (callback) {
						callback(data.joined, data.reason);
					});
				}
				break;
			case 'turn':
				console.log('Turn for player '+data.player+' (remaining tokens: '+data.stackSize+')');
				console.log(data.tokens);
				turnEvents.forEach(function (callback) {
					callback(data.player, data.tokens, data.stackSize);
				});
				sessionStorage.setItem('currentTurn', data.player);
				// zaktualizować konkretnemu graczowi tokeny i je wyświetlić
				if(data.turn == sessionStorage.playerName)
				{
					//odblokować interfejs do żetonów, poinformować że jest tura gracza
				}
				break;
			case 'tokenAdded':
				console.log('New token on board: color('+data.color+'), id('+data.id+'), name('+data.name+
					'), pos('+data.q+', '+data.r+'), angle('+data.angle+').');
				//wstawić na planszę żeton
				//odblokować interfejs
				tokenAddEvents.forEach(function (callback) {
					callback(data);
				});
				break;
			case 'tokenMoved':
				//komunikat odbierany po pomyślnym przesunięciu lub pchnięciu
				console.log('Token have been moved: color('+data.color+'), id('+data.id+'), name('+data.name+
					'), from('+data.src_q+','+data.src_r+'), to('+data.dst_q+','+data.dst_r+').');
				//przesunąć
				//odblokować interfejs
				tokenMovedEvents.forEach(function (callback) {
					callback(data);
				});
				break;
			case 'afterBattle':
				console.log('Battle.');
				console.log(data.board);
				console.log(data.players);
				//w data.board siedzi aktualny stan planszy
				// -> wywalic wszystkie zetony z planszy i powstawiac nowe
				//w data.players siedzi aktualny stan graczy
				// -> graczom z zerowym zyciem wyszarzyc tokeny czy cos w tym stylu 
				afterBattleEvents.forEach(function (callback) {
					callback(data.board, data.players);
				});
				break;
			case 'gameEnd':
				console.log('Game has ended. Winner: '+data.winner);
				//wyswietlic popup z wynikiem
				gameEndEvents.forEach(function (callback) {
					callback(data.winner);
				});
				break;
			case 'board':
				console.log('Board contents:');
				console.log(data.board);
				break;
			case 'error':
				handleError(data.errCont);
				errorEvents.forEach(function (callback) {
					callback(data.errorType);
				});
				break;
		}
	}
}

var handleError = function(errorType)
{
	switch(errorType){
		case 'addFailed':
			console.log('Failed to add token.');
			//cofnąć dodanie tokenu, odblokować interfejs
			addFailedEvents.forEach(function (callback) {
				callback(errorType);
			});
			break;
		case 'moveFailed':
			console.log('Failed to move token.');
			//cofnąć przesunięcie tokenu, odblokować interfejs
			break;
		case 'pushFailed':
			console.log('Failed to push token.');
			//cofnąć pchnięcie tokenu, odblokować interfejs
			break;
		case 'notYourTurn':
			console.log('Wait for your turn.');
			break;
		case 'throwFailed':
			console.log('Failed to throw token (HQ or not your token).');
			break;
		default:
			console.log('Error. Code: '+errorType);
	}
}

function sockets_start()
{
	socket = new io.Socket();
	socket.connect();
	socket.on('connect', on_connected);
	socket.on('message', on_received);
}

window.onload = sockets_start;

var socketServer = {
	getPlayers: function () {
		socket.send({'action': 'getPlayers'});
	},
	endTurn: function () {
		socket.send({'action': 'nextTurn'});
		//zablokować interfejs
	},
	moveToken: function (tokenActionId, src_q, src_r, dst_q, dst_r) {
		socket.send({'action': 'move', 'token': tokenActionId, 'src_q': src_q, 'src_r': src_r,
			'dst_q': dst_q, 'dst_r': dst_r});
	},
	pushToken: function (tokenActionId, src_q, src_r, dst_q, dst_r) {
		socket.send({'action': 'push', 'token': tokenActionId, 'src_q': src_q, 'src_r': src_r,
			'dst_q': dst_q, 'dst_r': dst_r});
	},
	battle: function (tokenActionId) {
		socket.send({'action': 'battle', 'token': tokenActionId});
		// zablokuj interfejs, tura gracza sie zakonczyla
	},
	getBoard: function () {
		socket.send({'action': 'getBoard'});
	},
	throwToken: function (tokenId) {
		socket.send({'action': 'throw', 'id': tokenId});
	},
	//byc moze nie potrzebne
	whoseTurn: function () {
		socket.send({'action': 'currentPlayer'});
	},
	putToken: function (msg) {
		console.log(msg)
		socket.send({'action': 'putToken', 'id': msg.id, 'q': msg.q, 'r': msg.r, 'angle': msg.angle});
	},
	join: function (data) {
		socket.send({'action': 'join', 'name': data});
	},
	setReady: function (is_ready) {
		socket.send({'action': 'ready', 'is_ready': is_ready})
	}
};



var playerListEvents = [];
var setColorEvents = [];
var gameStateEvents = [];
var turnEvents = [];
var joinStateEvents = [];
var tokenAddEvents = [];
var tokenMovedEvents = [];
var afterBattleEvents = [];
var gameEndEvents = [];
var errorEvents = [];

var addFailedEvents = [];

function subscribeOnPlayerList (callback) {
	playerListEvents.push(callback);
};
function subscribeOnSetColor (callback) {
	setColorEvents.push(callback);
};
function subscribeOnGameState (callback) {
	gameStateEvents.push(callback);
};
function subscribeOnTurn (callback) {
	turnEvents.push(callback);
};
function subscribeOnJoinState (callback) {
	joinStateEvents.push(callback);
};
function subscribeOnTokenAdd (callback) {
	tokenAddEvents.push(callback);
};
function subscribeOnTokenMove (callback) {
	tokenMovedEvents.push(callback);
};
function subscribeOnAfterBattle (callback) {
	afterBattleEvents.push(callback);
};
function subscribeOnGameEnd (callback) {
	gameEndEvents.push(callback);
};
function subscribeOnError (callback) {
	errorEvents.push(callback);
};

function subscribeOnAddFailed (callback) {
	addFailedEvents.push(callback);
};