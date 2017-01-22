
import io
import os
import tweepy
import time
try:
	import json
except ImportError:
	import simplejson as json 


auth = tweepy.OAuthHandler("0hc8nDJTFnKWFYFwaZIVIW78D", "h2c2pFH1XPeAMbkbxp0ieAShQceOBZSTknqOkkTddBFkN991ZP") #mise des données d'authentification au serveur tweeter
auth.set_access_token("799158684047802369-B5CLGbKQ2M5oX7lR9mlULgkN4ohdqIv", "TEEwPgujye8CROFOfID9Dx1lZ20BYFsvqSJJizke7wVZb")
id_tweet=int(0)
api = tweepy.API(auth)
if os.path.exists("tweet.txt"): #supprime tweet.txt s'il existe
       	os.remove("tweet.txt")

hash_file = open("Hashtag.txt","r")
hashtag=str(hash_file.readline()) # affecte a hashtag le string dans Hashtag.txt
hash_file.close()

id_file = open("id.txt","rw")
id_tweet=int(id_file.readline()) # affecte a id_tweet la valeur dans id.txt
id_file.close()				
									
results = api.search(q="%23"+hashtag, result_type="recent", count = 100, since_id=id_tweet) #recuperation des tweets concernant un hashtag donné
fichier = open("tweet.txt","w")
for k in range (0,len(results)):
	status=results[k]
	tweets=json.dumps(status._json)
	fichier.write(tweets+"\n") # stocke les tweets sous format json dans le fichier tweet.txt
fichier.close()
	
tweets_file = open("tweet.txt","r")
if os.path.exists("Listetweet.txt"):
        os.remove("Listetweet.txt") # supprime le fichier Listetweet.txt s'il existe
ArrayTweets_file = io.open("Listetweet.txt","w",encoding='utf8')
for line in tweets_file :
	tweet = json.loads(line.strip())
	if int(tweet['id'])>id_tweet:
		os.remove("id.txt")
		id_file = open("id.txt","w")
		id_file.write(str(tweet['id'])) #recuperation et ecriture dans le fichier id.txt du tweet recuperer pour ne récupérer que le tweet plus recent que celui-ci
		id_file.close()
		id_tweet=int(tweet['id'])
	if 'text' in tweet :
		ArrayTweets_file.write(tweet["user"]["name"]+'\n') #recuperation et ecriture dans le fichier Listetweet.txt du nom de l'utilisateur qui a tweeté et passe à la ligne
		ArrayTweets_file.write(tweet["text"]+'\n') #recuperation et ecriture dans le fichier Listetweet.txt du texte du tweet recuperer et passe à la ligne 
