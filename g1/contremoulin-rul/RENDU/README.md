Groupe : Paul CONTREMOULIN / Marion RUL

Projet Miroir (Miroir connecté)

Le projet consiste à créer un miroir connecté qui affiche la météo, les actualités, l'emploi du temps du jour et le nombre de personnes présentes dans la maison.
Pour cela, deux capteurs seront présents en bas du miroir et détecteront si une personne rentre ou sort, ce qui modifiera le nombre de personnes présentes et donc l'affichage.
Le miroir sera acrylique pour pouvoir voir l'affichage de l'écran disposé derrière relié au Raspberry Pi.

Concernant la hiérarchie des fichiers nous avons :
- Un répertoire "Projet"
Ce répertoire contient les deux fichiers grovepi.c et grovepi.h, ce sont les librairies qui nous permettent d'avoir les fonctions de base pour utiliser GrovePi en C.
Il contient également le fichier prog.c, ce fichier est notre programme principal concernant nos capteurs, il est expliqué plus en détail dans le rapport de synthèse de notre projet.

- Un répertoire "MagicMirror"
Ce répertoire contient seulement deux autres répertoires (nous ne vous avons pas envoyé tous les répertoires de l'application, certains n'étant pas important pour notre projet). Il y a le répertoire
config avec les fichiers de configuration des différents modules affichés sur l'écran et un répertoire modules contenant un autre répertoire default où nous avons rajouté notre module nbpersonnes.

-Le rapport de synthèse de notre projet 
