import time
import grovepi

# Connect the Grove PIR Motion Sensor to digital port D8
# NOTE: Some PIR sensors come with the SIG line connected to the yellow wire and some with the SIG line connected to the white wire.
# If the example does not work on the first run, try changing the pin number
# For example, for port D8, if pin 8 does not work below, change it to pin 7, since each port has 2 digital pins.
# For port 4, this would pin 3 and 4

pir_sensor = 7
buzzer = 8
motion=0
sensor = 1
display = 5
grovepi.pinMode(display,"OUTPUT")
grovepi.pinMode(pir_sensor,"INPUT")
grovepi.pinMode(buzzer,"OUTPUT")


print ("Test 1) Initialise")
grovepi.fourDigit_init(display)
time.sleep(.5)
print ("Test 2) Set brightness")
for i in range(0,8):
    grovepi.fourDigit_brightness(display,i)
    time.sleep(.2)
time.sleep(.3)
while True:
	try:
               
		# Sense motion, usually human, within the target range
		motion=grovepi.digitalRead(pir_sensor)
		if motion==0 or motion==1:	# check if reads were 0 or 1 it can be 255 also because of IO Errors so remove those values
			if motion==1:
				print ('Motion Detected')
				#grovepi.digitalWrite(buzzer,1)
				#time.sleep(0.2)
				#grovepi.digitalWrite(buzzer,0)

                                grovepi.fourDigit_segment(display,0,57) # 57 = C
                                grovepi.fourDigit_segment(display,1,63) # 63 = O
                                grovepi.fourDigit_segment(display,2,63) # 63 = O
                                grovepi.fourDigit_segment(display,3,56) # 56 = L
                                time.sleep(.5)
                                grovepi.fourDigit_segment(display,0,0) # 57 = C
                                grovepi.fourDigit_segment(display,1,0) # 63 = O
                                grovepi.fourDigit_segment(display,2,0) # 63 = O
                                grovepi.fourDigit_segment(display,3,0)
				#temp = grovepi.temp(sensor,'1.1')
                                #print("temp =", temp)

			else:
				print ('-')

			# if your hold time is less than this, you might not see as many detections
		time.sleep(.1)
		
        except KeyboardInterrupt:
            grovepi.digitalWrite(buzzer,0)
            grovepi.fourDigit_off(display)
            break
    
	except IOError:
		print ("Error")
