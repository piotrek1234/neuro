## @file web/settings.py
#  @brief Django settings file

"""
Django settings file
"""

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)

import os
BASE_DIR = os.path.dirname(os.path.dirname(__file__))

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'kw$@=pa)zdjmjx^6z65-+x3c5j+^ydyj1!t!@_q+z2qw06&1*i'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True
TEMPLATE_DEBUG = True

ALLOWED_HOSTS = []

#CORS_ORIGIN_ALLOW_ALL = True

# Application definition
INSTALLED_APPS = (
    #'corsheaders',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
#    'django.contrib.staticfiles',
    'version',
    'current',
    'calcpy',
    'django_socketio'
)

MIDDLEWARE_CLASSES = (
    #'corsheaders.middleware.CorsMiddleware',
    #'django.middleware.common.CommonMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
)

ROOT_URLCONF = 'config.urls'

SOCKETIO_HOST = '127.0.0.1'
SOCKETIO_PORT = '50007'

STATIC_URL = '/static/'
STATIC_ROOT = '/'

WSGI_APPLICATION = 'config.wsgi.application'

import version.models

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql_psycopg2',
        'NAME': version.models.getDBName(),
        'HOST': '',
        'PORT': '5432',
        'USER': version.models.getDBUser(),
        'PASSWORD': version.models.getDBPassword()
    }
}

# Internationalization
# https://docs.djangoproject.com/en/1.6/topics/i18n/

LANGUAGE_CODE = 'en-us'

TIME_ZONE = 'UTC'

USE_I18N = True

USE_L10N = True

USE_TZ = True


# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/1.6/howto/static-files/

