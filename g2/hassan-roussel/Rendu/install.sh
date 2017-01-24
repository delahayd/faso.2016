#!/bin/bash
echo "Bienvenue dans notre script d'installation"
echo "Veuillez patienter"
sudo apt-get update
sudo apt-get install python-pip python-dev build-essential python-opencv 

sudo pip install grovepi yeecli numpy ubidots

Installation terminee
