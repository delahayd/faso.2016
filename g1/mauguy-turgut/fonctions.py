import ftplib
from ftplib import FTP
import os 
import grovepi
import time
import smtplib
import traceback
import zipfile
import datetime
from os import path
import requests
from time import gmtime, strftime
import json

def envoiePhoto(idRasp): 
	#données: adresse mac du raspberry
	#résultat: envoie une photo prise par la camera pi au serveur FTP dans le dossier qui correspond à l'adresse Mac du raspberry.
	
	host = "ftp.cluster005.hosting.ovh.net"  # adresse du serveur FTP
	user = "onamafrqkc"  # votre identifiant
	password = "K2vm0r67"  # votre mot de passe
	datestring = datetime.datetime.fromtimestamp(time.time()).strftime('%Ysl%msl%d-%H:%M:%S')
	
	print('datestring='+datestring)
# 	p = path.splitext('../photos/photo.jpg')#on enregistre le chemin de la photo et on le divise en un tableau de deux elements; ceux avant le point et ceux apres#
	newpic = '/home/fabien/photos/'+ datestring + '.jpg'#on dit que la nouvelle photo est = au chemin + le string avec la date + le .jpg
	# print('newpic='+newpic)
	pictosend = datestring + '.jpg' #le nom de la photo seule est photo-date.jpg
	# print(pictosend)
	try: ## traitement  
		
		try:  
			os.system('raspistill -w 1280 -h 960 -n -q 5 -o '+newpic) #prise de photo
		except Exception:
		    print("Erreur lors de la prise de l'image")
		
		connect = FTP(host, user, password)  # on se connecte
		# Connexion
		print "Connexion a " +host
		etat = connect.getwelcome()
		print "Etat : ",etat
		print("------------")
			 
		# Ouverture Fichier
		
		
# 			filezipe = zipfile.ZipFile("compfile2.zip",'w', zipfile.ZIP_DEFLATED)
#			filezipe.write("imagetest25.jpg")
#			filezipe.close()
#			lieudepart = "./compfile2.zip"

#			filetosend = open(lieudepart, 'rb')
		print(idRasp)
		filetosend= open(newpic, "rb") #on ouvre le fichier a envoyer dans filetosend
					
		# Envoi Fichier
		connect.storbinary('STOR '+'www/Projet_Fas/Raspberry'+idRasp+'/'+pictosend ,filetosend) #on envoie la filetosend dans le dossier et on la nomme comme pictosend
		connect.quit() 		
 		os.system('rm '+newpic)		
	except Exception as e:
		print(e)



def getMAC(interface):
	#données: eth0 du raspberry
  # Resultat: String contenant l'adresse mac du raspberry
  try:
    str = open('/sys/class/net/' + interface + '/address').read()
  except:
    str = "00:00:00:00:00:00"
  return str[0:2]+str[3:5]+str[6:8]+str[9:11]+str[12:14] +str[15:17]

adresseMac = getMAC("eth0")


def getParametre(adresseMac):
	#donnees: adresseMac du raspberry en String
	#resultat: String correspondant à un objet json. Cet objet contient les parametres du programme
	#envoyés par le site apres une requete utilisant l'adresse Mac.

	r = requests.post('https://www.onama.fr/Projet_Fas/ComRasp.php', data={'IdRasp':adresseMac })
	#print(adresseMac)
	#print(r.status_code)
	#print(r.url)
	print(r.text)
	#print(r.content)
	#print(r.json()['mail'])
	return json.loads(r.text)


