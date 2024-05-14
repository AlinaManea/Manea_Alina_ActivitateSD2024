

//arbore: graf conex aciclic
//arbore binar: fiecare parinte are maxim 2 descendenti
//stanga: mai mic decat ce e in radacina
//dreapta: mai mare decat ce e in radacina


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>




typedef struct Elev Elev;
typedef struct Nod Nod;


struct Elev
{
	int id;
	int nrMedii;
	float* medii;
};

struct Nod
{
	Elev info;
	Nod* st;
	Nod* dr;
};

//inordine:radacina la mijloc, stanga, radacina, dreapta
//preordine: radacina, stanga, dreapta
//postordine: stranga, dreapta, radacina


Nod* rotireSpreDreapta(Nod* radacina)
{
	Nod* nod;
	nod = radacina->st;
	radacina->dr = nod->st;
	nod->dr = radacina;
	radacina = nod;

	return nod;
}


Nod* rotireSpreStanga(Nod* radacina) {
	Nod* nod;
	nod = radacina->dr;
	radacina->dr = nod->st;
	nod->st = radacina;
	return nod;
}

//functie care insereaza in arbore, care sa respecte principiul(STANGA mic, DREAPTA mare)
void inserareArbore(Nod** radacina, Elev e) {
	if (*radacina != NULL) {
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);
		}

		int grad = gradEchilibru(*radacina); 

		if (grad == 2) {
			if (gradEchilibru((*radacina)->st) == 1) { 
				*radacina = rotireSpreDreapta(*radacina);
			}
			else { 
				(*radacina)->st = rotireSpreStanga((*radacina)->st);
				*radacina = rotireSpreDreapta(*radacina);
			}
		}
		else if (grad == -2) {
			if (gradEchilibru((*radacina)->dr) == -1) { 
				(*radacina)->dr = rotireSpreDreapta((*radacina)->dr);
				*radacina = rotireSpreStanga(*radacina);
			}
			else { 
				*radacina = rotireSpreStanga(*radacina);
			}
		}

	}
	else {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}




int inaltime(Nod* radacina)
{

	if (radacina == NULL)
		return 0;
	else
	{
		int inaltimeStanga = inaltime(radacina->st);
		int inaltimeDreapta = inaltime(radacina->dr);
		/*if (inaltimeStanga < inaltimeDreapta)
			return 1 + inaltimeStanga;
		else
			return 1 + inaltimeDreapta;*/

		return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);

	}

}

int gradEchilibru(Nod* radacina)
{
	int inaltimeStanga = inaltime(radacina->st);
	int inaltimeDreapta = inaltime(radacina->dr);
	return inaltimeStanga - inaltimeDreapta;



}



Elev citireElev(FILE* fp)
{
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);

	e.medii = malloc(sizeof(float) * e.nrMedii);

	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%f", &(e.medii[i]));
	}
	return e;
}


Nod* citireFisier(char* numeFisier)
{
	Nod* arbore = NULL;


	if (!numeFisier)
	{
		return NULL;
	}
	else
	{
		FILE* fp = fopen(numeFisier, "r");

		int nrElevi;
		fscanf(fp, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++)
		{
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);
		}
		fclose(fp);
	}
	return arbore;
}

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are mediie ", e.id);
	for (int i = 0; i < e.nrMedii; i++)
	{
		printf("%5.2f", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrder(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);
	}
}

//functie care calculeaza media generala a tuturor elevilor, a clasei
float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)
	{
		float suma = 0;
		//radacina
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii; //procesarea radacinii
		//stanga
		float SumaS = calculeazaSumaNote(arbore->st, nrNote);
		//dreapta
		float SumaD = calculeazaSumaNote(arbore->dr, nrNote);
		return suma + SumaS + SumaD;
	}
	else
	{
		return 0;
	}
}

float calculeazaMedieGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0)
	{
		return suma / nrNote;
	}
	else
	{
		return 0;
	}
}


void afisarePreordine(Nod* radacina)
{
	if (radacina)
	{
		afisareElev(radacina->info);
		afisarePreordine(radacina->st);
		afisarePreordine(radacina->dr);

		
	}
}

void stergereArbore(Nod** radacina)
{
	if (*radacina)
		stergereArbore(&((*radacina)->st)); //prioritziam accesare
		stergereArbore(&((*radacina)->dr));

		free((*radacina)->info.medii);
		free((*radacina));
		*radacina = NULL;

}


void main()
{

	Nod* arbore = citireFisier("Elev.txt");
	if (arbore != NULL)
	{
		afisareInOrder(arbore);

		printf("Media este: %5.2f", calculeazaMedieGenerala(arbore));

		stergereArbore(&arbore);
	}
	afisarePreordine(arbore);
}
