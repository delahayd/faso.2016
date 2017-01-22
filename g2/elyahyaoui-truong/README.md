ELYAHYAOUI TRUONG

PROJET DOMOTIQUE : faciliter le quotidien d'une personne

rappel du projet : allumer/ eteindre à distance un appareil soit vocalement, soit grâce à un site internet 

Le fichier git est composé de 3 sous-fichier 

-EMISSION ONDES RADIO : 
        .DS_Store: 
        CHACON-send.cpp : envoi des ondes radios avec temps d'attente, conversion décimal binaire, envoi depulsations et de bits 

-INTERFACE WEB : 
on y trouve des fichiers pour l'affichage du site web (html) et récupération de la base de donnée (php) des appareils à controler 
         yuri.php : on y trouve les fonction qui correspondent a ce que YURI va répondre lorsqu'un cas est appelé
                    le tableau de correspondance des appareils aux pins GPIO du RASPBERRY PI
                    recupération de la date, heure et identification de l'inteface vocale 
                    réponse par défaut si aucune action n'a été spécifiée 
                    

-YURI SPEECH : 
         WSMR.cmd : fait appel au logiciel SPEECH TO TEXT de windows pour pouvoir convertir la voix en text .
         
         macros : receuil des éléments grâce à WSMR.cmd et selon ce qui est dit fait utilise un des fichier suivant 
                  date.xml : fait appel à la fonction de yuri.php pour récupérer la date 
                  time.xml : fait appel à la fonction de yuri.php pour récupérer l'heure 
                  insulte.xml: fait appel a la fonction de yuri.php pour dire une insulte 
                  presentation : fait appel à une fonction de yuri.php pour se présenter 
                  hcc_yuri.xml.xml : fait appel à une fonction de yuri.php pour allumer/éteindre les appareils 
                  fr-FR.grxml: vérification et adaptation de l'heure et de la date au format souhaité
                  
                  
                  
                  
         
         
          
