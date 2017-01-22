#-*- coding: utf-8 -*-

import os
import grovepi
import time
import smtplib	
import fonctions

# Connect the Grove Ultrasonic Ranger to digital port D4
# SIG,NC,VCC,GND
ultrasonic_ranger = 4

#L'utilisateur rentre son mail
#+ Le temps de latence minimum entre les mails. 
################
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText

msg = MIMEMultipart()
msg['From'] = 'instant.solarltd@gmail.com'
##msg['To'] = str(mail) 
msg['Subject'] = 'Alerte'
message = 'Des photos ont ete prises.'
msg.attach(MIMEText(message))
mailserver = smtplib.SMTP('smtp.gmail.com', 587)
mailserver.ehlo()
mailserver.starttls()
mailserver.ehlo()
mailserver.login('instant.solarltd@gmail.com', 'nikolatesla')
#################




dejaPrevenu = False
tempsDepuisDejaPrevenu = 0

parametre =fonctions.getParametre(fonctions.getMAC("eth0"))
mail = parametre["mail"]
infSup = parametre["infSup"]
distance =int(parametre["distance"])
tpsLatence = int(parametre["tpsLatence"])
etatProgramme = parametre["etatProgramme"] 
tempsDepuisDerniereCo = time.time()


while True:
	if(time.time() > tempsDepuisDerniereCo + 10):
		parametre =fonctions.getParametre(fonctions.getMAC("eth0"))
		mail = parametre["mail"]
		infSup = parametre["infSup"]
		distance = int(parametre["distance"])
		tpsLatence =int(parametre["tpsLatence"])
		etatProgramme = parametre["etatProgramme"] 
		tempsDepuisDerniereCo = time.time()	
	if (etatProgramme=="1"):
	    try:
	    # Read distance value from Ultrasonic
		distanceMesuree = grovepi.ultrasonicRead(ultrasonic_ranger)

		if(infSup == "Inf" and  distanceMesuree <= distance):	
			for i in range(1,3):		 	
				fonctions.envoiePhoto(fonctions.getMAC("eth0"))
			
			if(not dejaPrevenu):
			 	mailserver.sendmail('instant.solarltd@gmail.com', mail, msg.as_string())
				dejaPrevenu = True
				tempsDepuisDejaPrevenu = time.time()
			
		if(infSup == "Sup" and distanceMesuree >= distance):
			
			for i in range(0,3): 
				fonctions.envoiePhoto(fonctions.getMAC("eth0"))
			
			if(not dejaPrevenu):
				mailserver.sendmail('instant.solarltd@gmail.com', mail, msg.as_string())
				dejaPrevenu = True
				tempsDepuisDejaPrevenu = time.time()

		if(time.time() > tempsDepuisDejaPrevenu + tpsLatence*60  and dejaPrevenu):
			dejaPrevenu = False
	    except TypeError as e:
	        print (e)

mailserver.quit()
