//matr de adiacenta
//redun=dante, ocupa multa memorie degeaba unde am tatea 0 uri in matr de adiac



//GRAFURI
//conexe neconexe
//orientate neorientate
//complet
//ponderat


//lista
//next si inf, inf de tipul structurii
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//lucu cu grafuri

typedef struct Metrou Metrou;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Metrou
{
	int serie;
	int nrStatie;
	char* magistrala;
};

struct NodPrincipal
{
	Metrou info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie initializare Metrou
Metrou creareMetrou(int serie, int nrStatii, const char* magistrala)
{
	Metrou m;
	m.serie = serie;
	m.nrStatie = nrStatii;
	m.magistrala = (char*)malloc(sizeof(char) * (strlen(magistrala) + 1));
	strcpy(m.magistrala, magistrala);
	return m;
}

//functie inserare la inceput in lista principala
void inserarePrincipala(NodPrincipal** cap, Metrou m)//trb sa transmit noul cap al listei, **
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}


//functie de cautare Nod dupa serie
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie)
{
	while (graf && graf->info.serie != serie)//cat timp e diferit si exista, ne deplasam
	{
		graf = graf->next;
	}//daca nu gaseste seria returneaza NULL
	return graf;
	//returneaza lista unde pot sa inserez un nod
}

//functie inserare la final in lista secundara
NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* nod)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nod->next = NULL;
	nou->nod = nod;
	//parcurgem lista:
	if (cap)
	{
		NodSecundar* p = cap;//nu pot cu cap pt ca imi returneaza tot capul
		while (p->next)//daca ii dau NULL ajung tot pe NULL(while(P))
		{
			p = p->next;
		}
		p->next = nou;//am facut leg catre noul nod
		return cap;
	}
	else
	{
		return nou;
	}
}

//functie de inserare muchie
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop)
{
	//cautam dupa serieStart ca sa identificam nodul cautat dupa acea serie
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);//caut serie start in graf si mi returneaza adresa nodului care contine acea serie
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	if (nodStart && nodStop)
	{
		nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);//nodStop->nodul pe care il inseram
		nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
	}
}

#pragma region Coada
//definim regiune coada
typedef struct NodCoada NodCoada;

struct  NodCoada {
	int serie;
	NodCoada* next;
};
// daca facem inserare la un capat extragerea o facem la celalalt capat

void inserareCoada(NodCoada** cap, int serie)
{
	NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
	nodNou->serie = serie;
	nodNou->next = NULL;
	if (*cap)
	{
		NodCoada* aux = (*cap);
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else
	{
		*cap = nodNou;
	}
}


int extragereCoada(NodCoada** cap)
{
	//este extras capul,pt ca daca am inserat la inceput extragem la sfarsit gen

	if ((*cap))
	{
		int rezultat = (*cap)->serie;
		NodCoada* aux = (*cap);
		*cap = aux->next;
		free(aux);
		return rezultat;
	}
	else
		return -1;
}

#pragma endregion

//afisare parcurgere in latime

int getnumarNoduri(NodPrincipal* graf)
{
	int nr = 0;
	while (graf->next != NULL)
	{
		nr++;
		graf = graf->next;
	}
	return nr;
}

void afisareMetrou(Metrou m)
{
	printf("%d. numar statii:%d magistrala: %s", m.serie, m.nrStatie, m.magistrala);
	  
}


void afisareLatime(NodPrincipal* graf, int serie)
{
	NodCoada* coada = NULL;
	int nrNoduri = getnumarNoduri(graf);
	char* vizitate = (char*)malloc(nrNoduri);

	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareCoada(&coada, serie);
	vizitate[serie] = 1;
	while (coada)
	{
		int serieNoua= extragereCoada(&coada);
		NodPrincipal* nou = cautaNodDupaSerie(graf, serieNoua);

		afisareMetrou(nou->info);
		NodSecundar* temp = nou->vecini;

		while (temp)
		{
			if (temp->nod->info.serie == 0)
			{
				vizitate[temp->nod->info.serie] = 1;
				inserareCoada(&coada, temp->nod->info.serie);

			}
			temp = temp->next;
		}

		if (vizitate)
			free(vizitate);

	}


}



//functie de dezalocare
void dezalocareGraf(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* aux = *graf;
		free(aux->vecini);
		{
			NodSecundar* temp = aux->vecini;
			aux->vecini = temp->next;
		}
	 }
}

void main()
{
	NodPrincipal* graf = NULL;

	//5 noduri fara muchii:
	inserarePrincipala(&graf, creareMetrou(4, 6, "M2"));
	inserarePrincipala(&graf, creareMetrou(3, 7, "M3"));
	inserarePrincipala(&graf, creareMetrou(2, 8, "M4"));
	inserarePrincipala(&graf, creareMetrou(1, 12, "M5"));
	inserarePrincipala(&graf, creareMetrou(0, 4, "M6"));

	//creeam muchiile:
	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);


	afisareLatime(graf, 0);
}