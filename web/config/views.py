## @file web/views.py
#  @brief main server interface to client

"""
main interface to server
"""

import django.http
import json
import traceback

#all modules should be imported here
import calcpy
import calcpy.views

## for test working server
def index(request):
    """for test working server"""
    return django.http.HttpResponse("MyApp server" )

