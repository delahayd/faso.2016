#!/usr/bin/python
import sys
import time
from sense_hat import SenseHat

sense = SenseHat()
arrowDirection = [[3,2,1],[0,3,2],[1,0,3]]
chemin = [[1,2,0],[]]
cheminInverse = [[2,0,1],[]]

def textScroll(text):
	sense.set_rotation(180)
	red = (255, 0, 0)
	sense.show_message(text, text_colour=red)

def arrow(rotation) :
	X = (255, 0, 0)
	O = (255, 255, 255)
	rot = [0, 90, 180, 270]
	
	question_mark = [
		O, O, O, X, X, O, O, O,
		O, O, X, X, X, X, O, O,
		O, X, O, X, X, O, X, O,
		X, O, O, X, X, O, O, X,
		O, O, O, X, X, O, O, O,
		O, O, O, X, X, O, O, O,
		O, O, O, X, X, O, O, O,
		O, O, O, X, X, O, O, O
	]

	sense.set_pixels(question_mark)

	sense.set_pixel(0, 0, 255, 0, 0)
	sense.set_pixel(0, 7, 0, 255, 0)
	sense.set_pixel(7, 0, 0, 0, 255)
	sense.set_pixel(7, 7, 255, 0, 255)

	sense.set_rotation(rot[rotation])
	return 0

def getYaw():
	sense.set_imu_config(False,True,False)
	return str(sense.get_gyroscope()['yaw'])
		
def getCompass():
	sense.set_imu_config(True,False,False)
	return str(sense.get_compass())
	
def getAccelerometer():
	sense.set_imu_config(False,False,True)
	return str(sense.get_accelerometer())

def click():
	event = sense.stick.get_events()
	if(len(event) > 0 ):
		if(event[0].action == 'released' and event[0].direction == 'middle'):
			return 1
	return 0

def displayNextDoor(direction):
	while(1):
		yaw = getYaw()
		if((float(getYaw()) > 300 and float(getYaw()) < 360) or (float(getYaw()) > 0 and float(getYaw()) < 60)):
			arrow(direction)
		if(float(getYaw()) > 60 and float(getYaw()) < 120):
			arrow(arrowDirection[direction][0])
		if(float(getYaw()) > 120 and float(getYaw()) < 240):
			arrow(arrowDirection[direction][1])
		if(float(getYaw()) > 240 and float(getYaw()) < 300):
			arrow(arrowDirection[direction][2])
		
		if(click() == 1):
			return
	# 1 vers les usb, 2 droite, 3 oppose, 0  gauche
	# 1 en face, 2 droite, 0  gauche

def writeFile(toWrite):
	f = open("communication.txt","w")
	f.write(str(toWrite))
	f.close()

def main(oeuvre):
	print("PYTHON :" + str(oeuvre))
	for x in chemin[oeuvre - 1]:
		displayNextDoor(x)
	textScroll("Click pour retour")
	while(click() != 1):
		print("wait")
	for x in cheminInverse[oeuvre - 1]:
		displayNextDoor(x)
	writeFile(0)
	
while(1):
	if(sense.get_gyroscope()["roll"] > 20 and sense.get_gyroscope()["roll"] < 340):
		print("ROLL")
	if(sense.get_gyroscope()["pitch"] > 20 and sense.get_gyroscope()["pitch"] < 340):
		print("PITCH")
	#print(sense.get_gyroscope())
