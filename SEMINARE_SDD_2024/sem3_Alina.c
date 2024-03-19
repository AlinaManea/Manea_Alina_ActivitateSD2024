////
////#define _CRT_SECURE_NO_WARNINGS
////
////#include<stdio.h>
////#include<stdlib.h>
//#include<string.h>
////#include<malloc.h>
////
//////fisiere - in care vom avea mai multe aeroporturi pe care sa le citim
////struct Aeroport {
////	int id;
////	char* nume;
////	int nrTerminale;
////
////};
////
////struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
////	//transmitere prin valoare, se va copie intr o zona de memorie
////	//daca aveam pointer la aeroport trebuia mereu sa deferentiem
////	//dimensiunea o dam prin pointer pentru ca o vom modifica
////	//op + are propr mai mare fata de deferentiere
////{
////	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));
////	copie[(*dimensiune)] = aeroport; //shallow copy
////
////	for (int i = 0; i < (*dimensiune); i++)
////	{
////		copie[i] = vector[i];
////	}
////	(*dimensiune)++;
////	//dupa ce am copiat elem intr un alt vector le vom sterge
////
////	//for nj ce - ca sa stergem pointerii - daca aveam deep copy
////
////	if (vector)
////		free(vector);
////
////	return copie;
////}
////
////struct Aeroport* citireFisier(const char* numeFisier, int nrAeroporturi)
////{
////	struct Aeroport* vectorAeroporturi; //aici avem 0
////	vectorAeroporturi = NULL;
////	FILE* f = fopen(numeFisier, "r");
////	
////	if (f != NULL)
////	{
////		//fread citeste pana la linie \n
////
////		int *nrAeroporturi = 0;
////		char buffer[100]; //la dinamic erau tot 100
////		while (fgets(buffer, 99, f)!=NULL) {
////
////			struct Aeroport aeroport;	                                     //citim maxim 100 si string ul din care citim
////			strtok(buffer, ",\n");                                          //adresa catre ceea ce a citit
////		   //,\n - sir de delimitatoare; declaram o variabila in care sa avem acestea in caz ca le schimba cnv
////			char* delimitator[] = { ",\n" };
////			char* token = strtok(buffer, delimitator);
////			aeroport.id = atoi(token);
////			token = strtok(NULL, delimitator);
////			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
////			strcpy(aeroport.nume, token);
////			
////			token = strtok(NULL, delimitator);
////			aeroport.nrTerminale = atoi(token);
////
////
////			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);
////
////		}
////
////		fclose(f);
////	}
////	return vectorAeroporturi;
////}
////
////void afisareAeroporturi(struct Aeroport* aeroport)
////{
////	printf("Aeroportul cu ID: %d cu numele %s are %d terminale.\n\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
////	//accesam prin sageata caci fiind pointeri treb sa facem si deferentiere
////}
////
//////indexarrea are cea mai mare prioritate
////
////void afisarevectorAeroporturi(struct Aeroport* aeroporturi, int dim)
////{
////	printf("AFISARE VECTOR:\n");
////	for (int i = 0; i < dim; i++)
////	{
////		afisareAeroporturi(&aeroporturi[i]);
////	}
////}
////
//////void dezalocareVector(struct Aeroport** aeroporturi, int* dim)
//////{
//////	for (int i = 0; i < (*dim); i++)
//////	{
//////		free(aeroporturi[i]->nume);
//////
//////	}
//////}
////// 
////
////struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int idCautat)
////{
////	for(int i=0;i<dim;i++)
////		if (aeroporturi[i].id == idCautat)
////		{
////			return aeroporturi[i];
////		}
////
////	//struct
////}
////
////
////
////void main() {
////
////	int dimensiune=3;
////	//ca sa l transform in pointer extrag adresa/referinta gen &dimensiune
////
////	struct Aeroport* aeroporturi = NULL;
////	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);
////	afisarevectorAeroporturi(aeroporturi, dimensiune);
////}
//
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


struct Aeroport
{
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
{
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}
	if (vector)
	{
		free(vector);
	}

	(*dimensiune)++;

	
	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi)
{
//	//creem un vectori de aeroporturi
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;
//	//deschidem fisierul
	FILE* f= fopen(numeFisier, "r");

	if (f != NULL)
	{
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)//ne returneaza referinta la ceea ce a citit
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token= strtok(buffer, delimitator);//lista de delimitatoare
//			//salvam valoarea in structura noastra
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);
		}
		fclose(f);
	}
	return vectorAeroporturi;
	
}

void afisareAeroport(struct Aeroport* aeroport) 
{
	printf ( "aeroportul cu id: %d cu numele: %s are %d terminale.\n\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("afisare vector: \n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}



void main()
{
	int dimensiune=0;
	struct Aeroport* aeroporturi = NULL;
	aeroporturi= citireFisier("aeroporturi.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);

}

 

