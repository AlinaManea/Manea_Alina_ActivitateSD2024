

#include <stdio.h>
#include <malloc.h>

typedef struct Biblioteca Biblioteca;



struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};


//def alias sa nu mai fol struct struct
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;


struct Nod {
	Biblioteca info;
	//struct Nod* next;
	Nod* next;
	Nod* prev;
};

//struct care va retine cei doi pointeri
//Lista dublu inlantuita - parcurgere inversa
struct ListaDubla {
	Nod* head;
	Nod* tail;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca b; //cream ob
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

//cream un nou nod
void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {
	Nod* nod = (char*)malloc(sizeof(Nod));
		//ii alocam spatiu pe heap nu pe stack , d aia ... pointer
	nod->info = b;
	nod->next = listaDubla->head;
	nod->prev = NULL;

	if (listaDubla->head) {
		listaDubla->head->prev = nod;
		//listaDubla->head = nod;
	}
	else
	{

		
		listaDubla->tail = nod;
	}

	listaDubla->head = nod;

		//facem shallow copy


		//next pointeaza catre ce avem, adica cap
}


void afisareListaInceput(ListaDubla listaDubla)
{
	while (listaDubla.head)
	{
		//parcurgem pana devine NULL si afisam
		printf("Biblioteca: %s; Numar cititori %d; Numar carti %d\n ", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
		listaDubla.head = listaDubla.head->next;
	}
	printf("\n");
}


void stergereNodNume(ListaDubla* listaDubla, const char* nume)
{
	Nod* aux = listaDubla->head;
	while (aux && strcmp(nume, aux->info.nume) != 0)
	{
		aux = aux->next;
	}

	if (aux)
	{
		if (aux == listaDubla->head)
		{
			if (aux == listaDubla->tail)
			{
				listaDubla->head = aux;
				listaDubla->head = aux;
				//free(aux->info.nume); de fpt stergerea o lasam la final
			}
			else
			{
				{
					listaDubla->head = listaDubla->head->next;
					listaDubla->head->prev = NULL;
				}
			}
		}
		else {
			if (aux == listaDubla->tail)
			{
				aux->prev->next = NULL;
				listaDubla->tail = aux->prev;
			}
			else
			{   //ala din mijloc gennn
				aux->next->prev = aux->prev;
				aux->prev->next = aux->next;
			}
		}
		free(aux->info.nume);
		free(aux);
	}
}

void stergereLista(ListaDubla* listaDubla)
{
	while (listaDubla->head)
	{
		free(listaDubla->head->info.nume);
		Nod* aux = listaDubla->head;
		listaDubla->head = listaDubla->head->next;
		free(aux);
	}

	
		listaDubla->head = NULL;
	    listaDubla->tail = NULL;
}

//nr total de carti din toate bibliotecile noastre dar parcurgerea safie inversa



int nrCartiTotal(ListaDubla listaDubla)
{
	int rezultat = 0;
	while (listaDubla.tail)
	{
		rezultat += listaDubla.tail->info.nrCarti;
		listaDubla.tail = listaDubla.tail->prev;

	}
	return rezultat;
}


void main() {
	
	
	Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	

	ListaDubla listaDubla; // e un obiect, prin valoare va face o copie si s emodif in acea copie si cand se intoarce nu mai deci fie returnam fie transmitem prin pointer
	listaDubla.head = NULL;
	listaDubla.tail = NULL;
	//lista noastra vidaa gen am fc alta structura si are aia doi ambii NULL - pointeri inc si final


	inserareInceput(&listaDubla, b1);
	inserareInceput(&listaDubla, b2);
	inserareInceput(&listaDubla, b3);
	afisareListaInceput(listaDubla);


	int rezultat = nrCartiTotal(listaDubla);
	printf("nr total de carti->%d", rezultat);
	/*stergereNodNume(&listaDubla, "Ioan Slavici");
	afisareListaInceput(listaDubla);
	stergereNodNume(&listaDubla, "Mihai Eminescu");
	afisareListaInceput(listaDubla);
	stergereNodNume(&listaDubla, "Tudor Arghezi");*/


	stergereLista(&listaDubla);
	afisareListaInceput(listaDubla);

	
	
}



