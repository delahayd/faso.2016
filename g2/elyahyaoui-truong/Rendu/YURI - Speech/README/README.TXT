Pré Requis:
===========

- Brancher un micro (ou Kinect)
- Installer le Framework .Net
- Installer les Driver Microsoft SAPI
- Installer les Driver Kinect (si Kinect)


Configuration:
==============

- Ne pas dézipper dans un chemin contenant des espaces (ou trop long)

Usage:
======
- Lancer WSRMicro.cmd (ou WSRKinect.cmd si vous avez un kinect) 
- Parlez à Yuri !

Changer la voie:
=======

Télécharger les voie sur le net

Installer les voix Voix_Hortense_FR et Voix_Viginie_FR
Lancer l'executable: %windir%\SysWOW64\speech\SpeechUX\sapi.cpl
Choisir la voie qui vous convient le mieux

Liste des Fichiers:
====================

- WSRKinect.cmd => Le C# qui charge/écoute les grammaire (WSRMacro.exe sans Kinect)
- WSRNode.cmd => Le NodeJS qui lance un serveur HTTP
- /bin => executables appelés par NodeJS
- /macros => grammaire XML de Speech
- /plugin => dossier vide mais obligatoire




