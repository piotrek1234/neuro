from django_socketio.events import on_connect
from django_socketio.events import on_message

@on_connect
def my_message_handler(request, socket, context):
	print '>>>> connected'
	socket.send({'odp':'Witaj'})

@on_message
def odbior(request, socket, context, message):
	print '>>>> ', message
	socket.send({'odp': 'ok'})

