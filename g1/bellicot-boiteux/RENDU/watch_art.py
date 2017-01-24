#! usr/bin/python

# Projet Watch'Art BELLICOT-BOITEUX
# Enclenche le buzzer, allume la LED et envoie un message d'alerte via Gmail.

# MATERIEL UTILISE : GrovePi + Capteur à ultrasons + Buzzer + LED
# http://www.seeedstudio.com/wiki/Grove_-_Ultrasonic_Ranger
# http://www.seeedstudio.com/wiki/Grove_-_Buzzer
# http://www.seeedstudio.com/wiki/Grove_-_LED_Socket_Kit

import grovepi

# Importation de smtplib pour la fonction d'envoi, et de time pour la duree d'action du buzzer
import smtplib, time

# Importation du paquet nécessaire à l'envoi d'un message
from email.mime.multipart import MIMEMultipart

print("Démarrage du système")

# Assignation de la LED au port 3 et du buzzer au port 5 du Raspberry Pi
etat_led = 3
buzzer = 5

# Possibilité d'assigner au port 4 le capteur ultrasons pour l'ajouter dans la fonction ultrasonicRead()
# capteur_US = 4

SMTP_UTILISATEUR = ''            # ID de l'expéditeur à saisir
SMTP_MOTDEPASSE = ''             # Mot de passe de l'expéditeur à saisir
SMTP_DESTINATAIRE = ''           # Adresse mail du destinataire (personne à prevenir en cas d'intrusion)
SMTP_SERVEUR = 'smtp.gmail.com'  # Adresse du serveur SMTP (ici Gmail, mais modifiable selon les besoins)
SSL_PORT = 465

while True:                                   # Dans le cas d'une erreur de saisie ou de renvoi, on redémarre le programme
    try:
        if grovepi.ultrasonicRead() < 30:     # Si une personne s'approche à moins de 30cm du capteur
            print("Intrusion détectée")
            grovepi.analogWrite(buzzer,100)   # Fait sonner le buzzer à un volume de 100%
            time.sleep(.5)
            grovepi.analogWrite(buzzer,0)     # Eteint le buzzer
            grovepi.digitalWrite(etat_led,1)  # Allume la LED pour indiquer qu'une personne a été détectée

            # Création du message à envoyer
            A = SMTP_DESTINATAIRE
            DE = SMTP_UTILISATEUR
            message = MIMEMultipart()
            message.preamble = 'Le Raspberry Pi a envoyé une image'

            # Envoi du message via Gmail
            print("Envoi du message")
            serveur = smtplib.SMTP_SSL(SMTP_SERVEUR, SSL_PORT)
            serveur.login(SMTP_UTILISATEUR, SMTP_MOTDEPASSE)
            serveur.sendmail(DE, [A], message.as_string())
            serveur.quit()
            print("Message envoyé")

            grovepi.digitalWrite(etat_led,0)  # Extinction de la LED 
    except IOError:
        print("Erreur")
