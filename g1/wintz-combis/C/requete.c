#include <stdio.h>
#include <string.h>
#include "../curl/include/curl/curl.h"

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    char user = "Lolo";
    char lat = "10.8985";
    char lng = "-42.12683";
    char date = "aujourd'hui";
    char url = "http://www.wintz-combis.16mb.com/Application_Web/controleur/controleur-carte.php?action=SEND_POS&user=";

    /* on ajoute les variables a envoyer sur le serveur */
    strcat(url,user);
    strcat(url,"&lat=");
    strcat(url,lat);
    strcat(url,"&lng=");
    strcat(url,lng);
    strcat(url,"&date=");
    strcat(url,date);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
