typedef struct Ultrason Ultrason;
 // permet d'appeler la structure par Utrason au lieu de "struct  Ultrason"
struct Ultrason{
	const int PORT;//port sur lequel est branche le capteur
	int distance; // distance entre le capteur et l'objet
	char *orientation; //orientation du capteur

};

void calculDistance (Ultrason *capteur); // ne renvoie rien  
