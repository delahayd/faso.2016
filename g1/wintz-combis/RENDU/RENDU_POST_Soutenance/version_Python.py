# coding: utf-8

# Programme principal version Python
import os
import sys
import time
from math import *


def deg2rad(deg):
    return (deg * pi / 180)


def rad2deg(rad):
    return (rad * 180 / pi)


def distance(lat,lng, lat_arr,lng_arr):
# Fonction qui converti lat et lng en coordonnees degres decimaux, calcule la distance au point d'arrivee.
    theta = lng - lng_arr
    # Formule de calcul de la distance avec les coordonnees GPS de 2 points
    dist = sin(lat) * sin(lat_arr) + cos(lat) * cos(lng_arr) * cos(theta)
    print "distance :"
    print dist
    dist = acos(dist)
    dist = dist * 60
    dist = dist * 1.609344
    return dist

def buzz():
# Buzz 5 fois toutes les 2 secs.
# Connecter le Grove Buzzer sur le port digital D8.
    buzzer = 8

    grovepi.pinMode(buzzer,"OUTPUT")
    i = 0;
    while i<5:
        try:
            # Buzz pendant 1 seconde
            grovepi.digitalWrite(buzzer,1)
            time.sleep(1)

            # S'arrête pendant 1 seconde
            grovepi.digitalWrite(buzzer,0)
            time.sleep(1)

        except KeyboardInterrupt:
            grovepi.digitalWrite(buzzer,0)
            break
        except IOError:
            print ("Error")

        i = i+1


def main(lat_arr,lng_arr,user):
    fichier  = open("trackerTest.txt","r")
    # On lit chaque ligne du fichier
    prec = sys.float_info.max
    for line in fichier:
        # Traitement de la ligne courante
        line = line.split(',')
        date = line[1];
        # conversion des coordonnees en degres decimaux
        latitude = float(line[3])
        lat = int(latitude)/100
        latitude = lat + (latitude- lat*100)/60

        longitude = float(line[5])
        lng = int(longitude)/1000
        longitude = lng + (longitude -lng*1000)/60

        # calcul de la distance avec le point d'arrivee
        print latitude
        print longitude
        dist = distance(latitude,longitude,lat_arr,lng_arr)

        if (dist >prec):
            #buzz()
            print "vous vous etes eloignes"

        print prec
        print dist
        prec = dist

print "res:"
print distance(48.862725,2.287592,44.8564,2.856)
#main(44.8564,2.856,"u")
