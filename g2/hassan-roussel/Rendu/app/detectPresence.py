from picamera.array import PiRGBArray
from picamera import PiCamera
import cv2
import numpy as np
import time

# Initialiser la camera et capturer saisir une reference a la capture brute de la camera
camera = PiCamera()
rawCapture = PiRGBArray(camera)
kernel = np.ones((10,10),np.uint8)
#camera.capture('background.jpg')
background = cv2.imread('background.jpg')
cv2.GaussianBlur(background,(5,5),0)
	
camera.resolution = (1024, 768)
camera.capture('frame.jpg')
frame = cv2.imread('frame.jpg')
cv2.GaussianBlur(frame,(5,5),0)

diff = cv2.absdiff(frame,background)
gray = cv2.cvtColor(diff,cv2.COLOR_BGR2GRAY)
cv2.threshold(gray,50,255,cv2.THRESH_BINARY,gray)
erosion = cv2.erode(gray,kernel,iterations = 3)
dilate = cv2.dilate(erosion,kernel,iterations = 3)
contours,hierarchy = cv2.findContours(dilate,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

f = open('presence.txt', 'w')
presence = len(contours)>0 #Vrai si la personne est presente dans la piece

f.write(str(presence))

