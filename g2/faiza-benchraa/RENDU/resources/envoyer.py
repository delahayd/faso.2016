import smtplib
import sys
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders
 
fromaddr = "soufianebenchraa2@gmail.com"
toaddr = "soufianebenchraa2@gmail.com"
 
msg = MIMEMultipart()
 
msg['From'] = fromaddr
msg['To'] = toaddr
msg['Subject'] = "LE MUSEE EST EN DANGER"
 
body = "Un suspect s'est approche de l'oeuvre."
 
msg.attach(MIMEText(body, 'plain'))

""" 
#pour envoyer des fichiers multiple
i = int(1)
while (i<len(sys.argv)):
        filename = sys.argv[i]
        attachment = open("/home/sbenchra2/"+sys.argv[i], "rb")
        part = MIMEBase('application', 'octet-stream')
        part.set_payload((attachment).read())
        encoders.encode_base64(part)
        part.add_header('Content-Disposition', "attachment; filename= %s" % filename)
        msg.attach(part)
        i=i+1
"""
 
filename = sys.argv[1]
attachment = open("/home/faizabenchraa/museum_security/"+filename, "rb")
	
part = MIMEBase('application', 'octet-stream')
part.set_payload((attachment).read())
encoders.encode_base64(part)
part.add_header('Content-Disposition', "attachment; filename= %s" % filename)
 
msg.attach(part)
	 
server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(fromaddr, "touria123")
text = msg.as_string()
server.sendmail(fromaddr, toaddr, text)
 
server.quit()
