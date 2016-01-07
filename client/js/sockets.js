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
	socket.send({'action': 'getPlayers'});
}

// todo:
// połączyć wszystkie funkcje typu *Error

var on_received = function(data)
{
	if(data.action)
	{
		switch(data.action){
			case 'playersList':
				console.log(data.list);
				//zaktualizować listę graczy: imię, stan
				break;
			case 'setColor':
				console.log('My color: '+data.color);
				sessionStorage.setItem('playerColor', data.color);
				//przydzielić gdzieś graczowi kolor
				break;
			case 'gameState':
				if(data.state == 1)
				{
					socket.send({'action': 'getColor'});
					console.log('All ready. Game state: '+data.state);
				}
				break;
			case 'error':
				console.log('Error. '+data.error);
				break;
			case 'hello':
				console.log('Connected.');
				break;
			case 'joinState':
				if(data.joined == true)
				{
					console.log('Joined game as '+data.playerName+'.');
					sessionStorage.setItem('playerName', data.playerName);
					//ukryć pole do wpisywania imienia
				}	
				else
				{
					console.log('Failed to join. Reason: '+data.reason);
					//nie ukrywać pola, ewentualnie wyświetlić komunikat czemu się nie udało
				}
				break;
			case 'turn':
				console.log('Turn for player '+data.player);
				console.log(data.tokens);
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
				break;
			case 'tokenMoved':
				//log o przesunięciu
				//przesunąć
				//odblokować interfejs
			case 'tokenAddError':
				console.log('Failed to add token.');
				//cofnąć dodanie tokenu, odblokować interfejs
				break;
			case 'tokenMoveError':
				console.log('Failed to move token.');
				//cofnąć przesunięcie tokenu, odblokować interfejs
				break;
			case 'tokenPushError':
				console.log('Failed to push token.');
				//cofnąć pchnięcie tokenu, odblokować interfejs
				break;
		}
	}
}

var endTurn = function()
{
	socket.send({'action': 'nextTurn'});
	//zablokować interfejs
}

var moveToken = function(src_q, src_r, dst_q, dst_r)
{
	socket.send({'action': 'move', 'src_q': src_q, 'src_r': src_r, 'dst_q': dst_q, 'dst_r': dst_r});
}

var pushToken = function(src_q, src_r, dst_q, dst_r)
{
	socket.send({'action': 'push', 'src_q': src_q, 'src_r': src_r, 'dst_q': dst_q, 'dst_r': dst_r});
}

var battle = function()
{
	socket.send({'action': 'battle'});
}

//byc moze nie potrzebne
var whoseTurn = function()
{
	socket.send({'action': 'currentPlayer'});
}

var putToken = function(id, q, r, angle)
{
	socket.send({'action': 'putToken', 'id': id, 'q': q, 'r': r, 'angle': angle});
	//zawieś interfejs aż do uzyskania odpowiedzi - action:tokenAdded
}

var join = function(data)
{
	socket.send({'action': 'join', 'name': data});
}

var setReady = function(is_ready)
{
	socket.send({'action': 'ready', 'is_ready': is_ready})
}

function sockets_start()
{
socket = new io.Socket();
socket.connect();
socket.on('connect', on_connected);
socket.on('message', on_received);
}
window.onload = sockets_start;