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
				break;
			case 'setColor':
				console.log('My color: '+data.color);
				break;
			case 'gameState':
				if(data.state == 1)
					socket.send({'action': 'getColor'});
				console.log('All ready. Game state: '+data.state);
				break;
			case 'hello':
				console.log('Connected.');
				break;
		}
	}
}

var join = function(data)
{
	socket.send({'action': 'join', 'name': data});
}

var set_ready = function(name, is_ready)
{
	socket.send({'action': 'ready', 'name': name, 'is_ready': is_ready})
}

function sockets_start()
{
socket = new io.Socket();
socket.connect();
socket.on('connect', on_connected);
socket.on('message', on_received);
}
window.onload = sockets_start;