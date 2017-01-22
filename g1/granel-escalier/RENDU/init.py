import io
import os
import tweepy
import time
try:
        import json
except ImportError:
        import simplejson as json

auth = tweepy.OAuthHandler("0hc8nDJTFnKWFYFwaZIVIW78D", "h2c2pFH1XPeAMbkbxp0ieAShQceOBZSTknqOkkTddBFkN991ZP") #mises des informations d'authentification
auth.set_access_token("799158684047802369-B5CLGbKQ2M5oX7lR9mlULgkN4ohdqIv", "TEEwPgujye8CROFOfID9Dx1lZ20BYFsvqSJJizke7wVZb")
id_tweet=int(0)
api = tweepy.API(auth)
if os.path.exists("tweet.txt"): #supprime le fichier tweet s'il existe
        os.remove("tweet.txt")

hash_file = open("Hashtag.txt","r") #affecte a hashtag le string dans Hashtag.txt
hashtag=str(hash_file.readline())
hash_file.close()


id_file = open("id.txt","rw")
id_tweet=int(id_file.readline()) #affecte a id_tweet la valeur dans le fichier id.txt
id_file.close()

results = api.search(q="%23"+hashtag, result_type="recent", count = 100, since_id=id_tweet) #recherche des tweet pour le hashtag donné
fichier = open("tweet.txt","w")
for k in range (0,len(results)): #ecriture dans le fichier tweet.txt des tweet sous format json
        status=results[k]
        tweets=json.dumps(status._json)
        fichier.write(tweets+"\n")
fichier.close()

tweets_file = open("tweet.txt","r")
for line in tweets_file : #recuperation de la plus grande id des tweets stockés précèdement
        tweet = json.loads(line.strip())
        if int(tweet['id'])>id_tweet:
                os.remove("id.txt")
                id_file = open("id.txt","w")
                id_file.write(str(tweet['id'])) 
                id_file.close()
                id_tweet=int(tweet['id'])


