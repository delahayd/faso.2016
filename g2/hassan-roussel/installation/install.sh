#! /bin/bash

# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
       echo "This script must be run as root" 1>&2
          exit 1
      fi
      dpkg --purge tightvncserver
      apt-get install xbitmaps
      apt-get install x11-apps
      apt-get install x11-session-utils
      apt-get install xbase-clients
      apt-get install vnc4server
      # Restart vnc running script in background
      systemctl restart vncboot.service

