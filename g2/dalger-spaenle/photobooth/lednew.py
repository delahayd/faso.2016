import time
from grovepi import *


led = 7
pinMode(led,"OUTPUT")
time.sleep(1)
for i in range(0,5):
	try:
		digitalWrite(led,1)
		time.sleep(1)
		digitalWrite(led,0)
		time.sleep(1)
	except KeyboardInterrupt:
		digitalWrite(led,0)
		break
	except IOError:
		print "Error"
