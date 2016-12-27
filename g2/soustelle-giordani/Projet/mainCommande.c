//gcc -I/usr/include/python2.7 -lpython2.7 main2.c -o call
#include <Python.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define com "communication.txt"

double script(int argc, char *argv[]){
	
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    long tmp;

    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();
    
    PySys_SetArgv(argc,argv);
    
    pName = PyString_FromString(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);

    Py_DECREF(pName);
   
	
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) {
                pValue = PyInt_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {/*
				tmp = PyFloat_AsDouble(pValue);
                printf("Result of call: %ld\n", tmp);*/
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    Py_Finalize();

    return tmp;
}

long getYaw(){
	char* argument[5];
	argument[0] = "mainCommande";
	argument[1] = "interfaceSenseHat";
	argument[2] = "getYaw";
	
	return script(3,argument);
}


long getCompass(){
	char* argument[5];
	argument[0] = "mainCommande";
	argument[1] = "interfaceSenseHat";
	argument[2] = "getCompass";
	
	return script(3,argument);
}
	
long getAccelerometer(){
	char* argument[5];
	argument[0] = "mainCommande";
	argument[1] = "interfaceSenseHat";
	argument[2] = "getAccelerometer";
	
	return script(3,argument);
}


int click(){
	char* argument[5];
	argument[0] = "mainCommande";
	argument[1] = "interfaceSenseHat";
	argument[2] = "click";
	
	return (int)script(3,argument);
}

int main(int argc, char *argv[]){
	//while(1){
		while(readFile(com,1) == 0){ //Tant que la borne n'a pas donne le numero de l'oeuvre
			//Traitement Buzzer
			
			char tmp[1];
			tmp[0] = (char)(1 + 48);
			writeFile(com,tmp);
		
		}
		//Guider
		
		char* argument[4];
		argument[0] = "mainCommande";
		argument[1] = "interfaceSenseHat";
		argument[2] = "main";
		char tmp[1];
		tmp[0] = (char)(readFile(com,1) + 48);
		printf("%c\n", tmp[0]);
		argument[3] = tmp;
		
		script(4,argument);
		
		//script(argc,argv);
		//drawArrow(3);
	/*
		int tmp = (int)click();
		while(tmp != 1){
			sleep(3);
			tmp = click();
			printf("%d \n", tmp);
		}
		printf("%d \n", click());
		*/
		
		while(readFile(com,1) != 0){ //Tant que le programme python n'a pas fini

		}
		/*
		char currentCh[] = "0";
		if(writeFile(com,currentCh) == -1){//Remettre a 0 le fichier pour finir
			printf("Error !");
			return -1;
		}*/
	//}
}

int drawArrow(int direction){
	char* argument[5];
	argument[0] = "mainCommande";
	argument[1] = "interfaceSenseHat";
	argument[2] = "arrow";
	char tmp[1];
	tmp[0] = (char)(direction + 48);
	argument[3] = tmp;
	
	script(4,argument);
	return 0;
}

int writeFile(char* filename, char buffer[]){
	FILE *fp;
	fp = fopen(filename,"w");
	int nbwrite = fwrite(buffer, 1, sizeof(buffer), fp);
	fclose(fp);
	if(nbwrite == sizeof(buffer))
		return 0;	
	return -1;
}

int readFile(char* filename, int curseur){
	FILE * fp;
	fp = fopen(filename, "r");
	int x;
	for(x = 0; x < curseur -1; x = x +1){
		fgetc(fp);
	}
	int tmp = (int)(fgetc(fp)) - 48;
	fclose(fp);
	return tmp;
}
