#!/usr/bin/python
# coding: utf8
#Desktop/GoPiGo/Projects/ProjetFAS
from gopigo import *
from math import *
from random import *
import picamera

compteur=0#Compteur pour numéroter les photos
pinMode(10,"OUTPUT")#Le buzzer est branché sur le port D11 (le pin est égal à 10)

def photo(compteur):
	#But : Prend une photo à l'aide de la caméra et l'enregistre sous la forme "obstacleNum.jpg" dans le dossier où le code est présent. Le Num évolue au cours du temps
	#      en fonction du nombre de photos déjà prises
    with picamera.PiCamera() as camera:
		camera.resolution=(1024,768)
		camera.brightness=60
		camera.start_preview()
		#Camera warm-up time
		time.sleep(2)
		avant="obstacle"
		apres=".jpg"
		chaine=("%s%s%s"%(avant,compteur,apres))#on construit le nom de la photo
		camera.capture(chaine)
                
def avancer():
	#But : Fait avancer le GoPiGo tant qu'un obstacle n'a pas été détécté sur son chemin
    delay=.01
    ang=45 #Angle de départ
    lim=250
    continuer=True #tant qu'il n'y a pas d'obstacles

	servo(ang) #Positionnement du servo
	time.sleep(.03)
	fwd() #activation des moteurs
	set_speed(100) #Vitesse choisie

    while continuer: 
        distance=us_dist(15) #Mesure de la distance avec le capteur ultrason (qui est sur le port A1 de pin 15)
        while distance<7 and distance >0: #Bug du capteur ultrason qui donnait des valeurs égalent à 5 ou 6 alors que la distance était convenable
            distance=us_dist(15)
        if distance>lim or distance <0: #Si la distance est trop grande ou négative, on l'initialise à la valeur max
            distance=lim
        if distance<13/sin(ang/57.2958): #Si la distance est inférieure, c'est à dire qu'un obstacle est trop proche du GoPiGo, il ne peut donc plus avancer. On divise par 57.2958 pour se ramener en degré
            continuer=False
        else: #On continue le sondage de la zone
            ang+=5
            servo(ang)
            time.sleep(delay)
                        
        if ang>135: #Si on a balayé toute la zone, on recommence
            ang=45
			servo(ang)
			time.sleep(.03)
	stop() #Si un obstacle a été détecté, on arrête les moteurs
	
def changerDirection():
	#But : Regarde dans quelle direction le GoPiGo peut avancer. Si une direction est trouvée, il place alors le GoPiGo dans cette direction. Il retourne True si une direction a été trouvée, False sinon
    changementDirection=True
    L=[0,1,2] #0 on toune a gauche, 1 on tourne a droite et 2 on fait demi-tour
    direction=choice(L) #On chosit aléatoirement une direction
	if direction==0:
        left_rot()
        time.sleep(1.7)
        stop()
        if(not directionPossible()):
			L=[1,2] #1 on tourne a droite et 2 on fait demi-tour
			direction=choice(L) #On chosit aléatoirement une direction
			if direction==1:
                left_rot()
                time.sleep(4)
                stop()
                if(not directionPossible()):
                    right_rot()
                    time.sleep(1.7)
                    stop()
                    if(not directionPossible()):
                       	print "aucune direction possible pour le moment"
                        changementDirection=False
            else:
                left_rot()
                time.sleep(1.7)
                stop()
                if(not directionPossible()):
                    left_rot()
                    time.sleep(1.7)
                    stop()
                    if(not directionPossible()):
                        print "aucune direction possible pour le moment"
                        changementDirection=False
    if direction==1:
        right_rot()
        time.sleep(1.7)
        stop()
        if(not directionPossible()):
			L=[0,2] #0 on toune a gauche et 2 on fait demi-tour
			direction=choice(L) #On chosit aléatoirement une direction
			if direction==0:
                right_rot()
                time.sleep(4)
                stop()
                if(not directionPossible()):
                    left_rot()
                    time.sleep(1.7)
                    stop()
                    if(not directionPossible()):
                    	print "aucune direction possible pour le moment"
                    	changementDirection=False
            else:
                right_rot()
                time.sleep(1.7)
                stop()
                if(not directionPossible()):
                    right_rot()
                    time.sleep(1.7)
                    stop()
                    if(not directionPossible()):
                        print "aucune direction possible pour le moment"
                        changementDirection=False
    if direction==2:
        right_rot()
        time.sleep(4)
        stop()
        if(not directionPossible()):
			L=[0,1] #0 on toune a gauche et 1 on tourne a droite
			direction=choice(L) #On chosit aléatoirement une direction
			if direction==0: 
		        right_rot()
		        time.sleep(1.7)
		        stop()
		        if(not directionPossible()):
		            right_rot()
		            time.sleep(1.7)
		            stop()
		            if(not directionPossible()):
		                print "aucune direction possible pour le moment"
		                changementDirection=False
        else:
            left_rot()
            time.sleep(1.7)
            stop()
            if(not directionPossible()):
                left_rot()
                time.sleep(4)
                stop()
                if(not directionPossible()):
                    print "aucune direction possible pour le moment"
                    changementDirection=False
    return changementDirection
                
        
			
def directionPossible():
	#But : Scan devant le GoPiGO pour savoir si un obstacle est present. Renvoie True si aucun obstacle n'est trouvé, False sinon
    possible=True
    ang=45
    delay=.01
    lim=250
	servo(ang) #Positionnement du servo
    while possible and ang<135: #Mesure de la distance avec le capteur ultrason (qui est sur le port A1 de pin 15)
        distance=us_dist(15)
        while distance<7 and distance >0: #Bug du capteur ultrason qui donnait des valeurs égalent à 5 ou 6 alors que la distance était convenable
            distance=us_dist(15)
        if distance>lim or distance <0: #Si la distance est trop grande ou négative, on l'initialise à la valeur max
            distance=lim 
        if distance<13/sin(ang/57.2958): #Si la distance est inférieure, c'est à dire qu'un obstacle est trop proche du GoPiGo, il ne peut donc plus avancer. On divise par 57.2958 pour se ramener en degré
            possible=False
        else: #On continue le sondage de la zone
            ang+=5
            servo(ang)
            time.sleep(delay)

    return possible
                

while True:
    enable_servo()
    avancer()
    digitalWrite(10,1) #On fait bipper le buzzer
    time.sleep(0.1)
    digitalWrite(10,0) #On arrête le buzzer
    time.sleep(0.2)
    digitalWrite(10,1) #On fait bipper le buzzer
    time.sleep(0.1)
    digitalWrite(10,0) #On arrête le buzzer
    time.sleep(0.2)
    digitalWrite(10,1) #On fait bipper le buzzer
    time.sleep(0.1)
    digitalWrite(10,0) #On arrête le buzzer
    photo(compteur)
    compteur+=1 #On augmente le compteur de 1 car une photo a été prise
    if(not changerDirection()): 
       	time.sleep(15) #Si on peut pas changer de direction alors on attend 15 secondes avant de scanner à nouveau
       	if(not directionPossible()): 
        	changerDirection() #Si on ne peut pas aller devant nous alors on regarde les autres directions
    disable_servo()



