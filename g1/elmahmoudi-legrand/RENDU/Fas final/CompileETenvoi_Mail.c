#include "grovepi.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
	system("gcc envoiemail.c -o EnvoiMail");
	system("./EnvoiMail");
   	return 1;
}

