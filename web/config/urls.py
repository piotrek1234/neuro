## @file web/urls.py
#  @brief Django urls

from django.conf.urls import patterns, include, url
#from django.conf import settings

import views
import version.models

web_srv_prefix = version.models.getWebSrvPrefix()

urlpatterns = patterns('',
                       url("", include('django_socketio.urls')),
                       url(r'^$', views.index, name='index')
)

