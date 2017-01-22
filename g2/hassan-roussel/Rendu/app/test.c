#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int detectPersonne(char presence[]){
	return strcmp(presence,"True%");
}

int main(){
	system("python detectPresence.py");
	//Lire le fichier contenant le booleen
	FILE *fp;
	char buff[255];
	fp = fopen("presence.txt", "r");
	fscanf(fp, "%s", buff);
	fclose(fp);
	printf("%d",detectPersonne(buff));
	return 0;
}

