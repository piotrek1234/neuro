var on_connected = function()
{
	socket.send({'action': 'getPlayers'});
}

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
				//przydzielić gdzieś graczowi kolor
				break;
			case 'gameState':
				if(data.state == 1)
				{
					socket.send({'action': 'getColor'});
					console.log('All ready. Game state: '+data.state);
				}
				break;
			case 'hello':
				console.log('Connected.');
				break;
			case 'joinState':
				if(data.joined == true)
				{
					console.log('Joined game.');
					//ukryć pole do wpisywania imienia
				}	
				else
				{
					console.log('Failed to join. Reason: '+data.reason);
					//nie ukrywać pola, ewentualnie wyświetlić komunikat czemu się nie udało
				}
		}
	}
}

var join = function(data)
{
	socket.send({'action': 'join', 'name': data});
}

var set_ready = function(is_ready)
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