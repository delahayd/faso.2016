from subprocess import call #appel systeme 
import tkFileDialog
import glob #recuperer dossier recursivement
import os
import os.path
import time
try:
    import picamera as mycamera
except ImportError:
    import cv2_camera as mycamera
from time import sleep
if False:
    import gdata
    import gdata.photos.service
    import gdata.media
    import gdata.geo
    import gdata.gauth
    import webbrowser
    from datetime import datetime, timedelta
    from oauth2client.client import flow_from_clientsecrets
    from oauth2client.file import Storage
from credentials import OAuth2Login

from PIL import Image
import serial
import config
import custom
import httplib2

from constants import SCREEN_W, SCREEN_H, WHITE, BLACK

FONTSIZE=100
font = ('Times', FONTSIZE)

def safe_set_led(camera, state):
    try:
        camera.led = state
    except:
        pass

def setup_google():
    global client

    out = True
    try:
        configdir = os.path.expanduser('./')
        client_secrets = os.path.join(configdir, 'OpenSelfie.json')
        credential_store = os.path.join(configdir, 'credentials.dat')

        client = OAuth2Login(client_secrets, credential_store, config.username)

    except KeyboardInterrupt:
        raise
    except Exception, e:
        print 'could not login to Google, check .credential file\n   %s' % e
        out = False
        # raise ### uncomment to debug google oauth shiz
    return out

def countdown(camera, can, countdown1):
    camera.start_preview()
    can.delete("image")
    led_state = False
    safe_set_led(camera, led_state)
    camera.preview_alpha = 100
    camera.preview_window = (0, 0, SCREEN_W, SCREEN_H)
    camera.preview_fullscreen = False

    can.delete("all")

    for i in range(countdown1):
        can.delete("text")
        can.update()
        can.create_text(SCREEN_W/2 - 0, 200, text=str(countdown1 - i), font=font, tags="text")
        can.update()
        if i < countdown1 - 2:
            time.sleep(1)
            led_state = not led_state
            safe_set_led(camera, led_state)
        else:
            for j in range(5):
                time.sleep(.2)
                led_state = not led_state
                safe_set_led(camera, led_state)
    can.delete("text")
    can.update()
    camera.stop_preview()

def snap(can, countdown1, effect='None'):
    global image_idx

    try:
        if custom.ARCHIVE and os.path.exists(custom.archive_dir) and os.path.exists(custom.PROC_FILENAME):
            image_idx += 1
            new_filename = os.path.join(custom.archive_dir, '%s_%05d.%s' % (custom.PROC_FILENAME[:-4], image_idx, custom.EXT))
            command = (['cp', custom.PROC_FILENAME, new_filename])
            call(command)
        camera = mycamera.PiCamera()
        countdown(camera, can, countdown1)
        camera.capture(custom.RAW_FILENAME, resize=(1366, 768))
        snapshot = Image.open(custom.RAW_FILENAME)


            
        camera.close()
            
    
        if custom.logo is not None:
            # snapshot.paste(logo,(0,SCREEN_H -lysize ),logo)
            # snapshot.paste(custom.logo,(SCREEN_W/2 - custom.logo.size[0]/2,
            #                             SCREEN_H -custom.lysize ),
            #                             custom.logo)
            size = snapshot.size
            logo_size = custom.logo.size
            yoff = size[1] - logo_size[1]
            xoff = (size[0] - logo_size[0]) // 2
            snapshot.paste(custom.logo,(xoff, yoff),
                           custom.logo)
        snapshot.save(custom.PROC_FILENAME)
    except Exception, e:
        print e
        snapshot = None
    return snapshot
snap.active = False


if custom.ARCHIVE: 
    if not os.path.exists(custom.archive_dir):
        print 'Directory not found.  Not archiving'
        custom.ARCHIVE = False
    image_idx = len(glob.glob(os.path.join(custom.archive_dir, '%s_*.%s' % (custom.PROC_FILENAME[:-4], custom.EXT))))

SERIAL = None
def findser():
    global SERIAL
    if SERIAL is None: ## singleton
        SERIAL = serial.Serial('/dev/ttyS0',19200, timeout=.1)
        print 'using AlaMode'
    return SERIAL


def googleUpload(filen):
    if custom.albumID != 'None':
        album_url ='/data/feed/api/user/%s/albumid/%s' % (config.username, custom.albumID)
        photo = client.InsertPhotoSimple(album_url,'NoVa Snap',custom.photoCaption, filen ,content_type='image/jpeg')
    else:
        raise ValueError("albumID not set")
        
