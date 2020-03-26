from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    #path('/cournot/', views.home, name='home')
    path('/cournot/', views.Cournot, name='cournot_view')
    # url(r'^success$', successpage, name='successpage'),
    # path('display/<str:filename>', views.download_file, name='download_file')
]
