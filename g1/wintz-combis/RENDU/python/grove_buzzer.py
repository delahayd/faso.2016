import time
import grovepi

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
