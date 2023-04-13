#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct drzewo {
	int wartosc;
	struct drzewo *lewo;
	struct drzewo *prawo;
} drzewo;

void start() {
	system("cls");
	printf("Binarne drzewo wyszukiwan\n"
	"--------------------------------------------------------\n"
	"[0] Wyjscie z programu\n"
	"[1] Dodaj wezel\n"
	"[2] Wyswietl drzewo\n"
	"[3] Wyswietl liczbe elementow na danym poziomie\n"
	"[4] Wyswietl wysokosc drzewa\n"
	"[5] Usun element z drzewa\n"
	"[6] Sprawdz czy drzewo jest kopcem\n"
	"[7] Przedstaw drzewo w formie tabeli, jezeli to mozliwe\n"
	"--------------------------------------------------------\n\n"
	"Wybrana komenda: ");
}

int bylo(int x, int* tab, int ile) {
    if(ile==0)
        return 0;
    int i;
    for(i=0;i<ile;i++)
    	if(tab[i]==x)
            return i+1;
    return 0;
}

int hBST(drzewo* korzen) {
    if(korzen==NULL)
        return 0;
    else {
        int lewo=hBST(korzen->lewo);
        int prawo=hBST(korzen->prawo);
        if (lewo>prawo)
            return (lewo+1);
        else
            return (prawo+1);
    }
}

int countLevBST(drzewo* korzen, int poziom) {
	int sum=0;
	if(poziom==0)
        return sum+1;
    else if(poziom > 0) {
    	if(korzen->lewo!=NULL)
        	sum+=countLevBST(korzen->lewo, poziom-1);
        if(korzen->prawo!=NULL)
        	sum+=countLevBST(korzen->prawo, poziom-1);
        return sum;
    }
}

void LO(drzewo* korzen) {
    int h=hBST(korzen);
    int i;
    for(i=0; i<h; i++) {
    	printf("Poziom %d: ", i);
    	LO_wyswietl_poziom(korzen, i);
    	printf("\n");
	}
}

int LO_wyswietl_poziom(drzewo* korzen, int poziom) {
    if(poziom==0)
        printf("%5d", korzen->wartosc);
    else if(poziom>0) {
    	if(korzen->lewo!=NULL)
        	LO_wyswietl_poziom(korzen->lewo, poziom-1);
        if(korzen->prawo!=NULL)
        	LO_wyswietl_poziom(korzen->prawo, poziom-1);
    }
}

void insertBST(drzewo **korzen, int key) {
	drzewo *nowy;
	nowy=(drzewo*)malloc(sizeof(drzewo));
	nowy->lewo=NULL;
	nowy->prawo=NULL;
	nowy->wartosc=key;
	if(*korzen==NULL)
		*korzen=nowy;
	else {
		drzewo *temp=*korzen;
		while(temp) {
			if(nowy->wartosc>=temp->wartosc)
				if(temp->prawo!=NULL)
					temp=temp->prawo;
				else {
					temp->prawo=nowy;
					break;
				}
			else if(nowy->wartosc<temp->wartosc)
				if(temp->lewo!=NULL)
					temp=temp->lewo;
				else {
					temp->lewo=nowy;
					break;
				}
		}
	}
}

void LVR(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		if(korzen->lewo!=NULL)
			LVR(korzen->lewo);
		printf("%d ", korzen->wartosc);
		if(korzen->prawo!=NULL)
			LVR(korzen->prawo);
	}
}

void VLR(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		printf("%d ", korzen->wartosc);
		if(korzen->lewo!=NULL)
			VLR(korzen->lewo);
		if(korzen->prawo!=NULL)
			VLR(korzen->prawo);
	}
}

void LRV(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		if(korzen->lewo!=NULL)
			LRV(korzen->lewo);
		if(korzen->prawo!=NULL)
			LRV(korzen->prawo);
		printf("%d ",korzen->wartosc);
	}
}

void graficznie(drzewo* korzen, int x) {
	int i;
	if(korzen==NULL)
        return;
    x++;
    graficznie(korzen->prawo, x);
    printf("\n");
    for (i=1; i<x; i++)
        printf("\t");
    printf("%d\n", korzen->wartosc);
	graficznie(korzen->lewo, x);
}

drzewo* nastepnik(drzewo* korzen) {
    struct drzewo* temp=korzen;
    while (temp && temp->lewo!=NULL)
        temp=temp->lewo;
    return temp;
}

drzewo* removeBST(drzewo* korzen, int x) {
	if(korzen==NULL)
        return korzen;
    if(x<korzen->wartosc)
        korzen->lewo=removeBST(korzen->lewo, x);
    else if(x>korzen->wartosc)
        korzen->prawo=removeBST(korzen->prawo, x);
    else {
        if(korzen->lewo==NULL && korzen->prawo==NULL)
            return NULL;
        else if(korzen->lewo==NULL) {
            struct drzewo* temp=korzen->prawo;
            free(korzen);
            return temp;
        }
        else if(korzen->prawo==NULL) {
            struct drzewo* temp=korzen->lewo;
            free(korzen);
            return temp;
        }
        struct drzewo* temp=nastepnik(korzen->prawo);
        korzen->wartosc=temp->wartosc;
        korzen->prawo=removeBST(korzen->prawo, temp->wartosc);
    }
    return korzen;
}

int licz_elementy(drzewo* korzen) {
	if(korzen==NULL)
		return 0;
	return (1+licz_elementy(korzen->prawo)+licz_elementy(korzen->lewo));
}

int checkBST(drzewo* korzen, int i, int ile_el) {
    if(korzen==NULL)
        return 1;
    if(i>=ile_el)
        return 0;
    if(checkBST(korzen->lewo, 2*i+1, ile_el) && checkBST(korzen->prawo, 2*i+2, ile_el))
		return 1;
	return 0;
}

void tableBST(drzewo* korzen) {
	int i;
	printf("Index:\t");
	for(i=1;i<=licz_elementy(korzen);i++)
		printf("%5d", i);
	printf("\nWartosc:");
	for(i=0;i<=hBST(korzen);i++)
		LO_wyswietl_poziom(korzen, i);
}

int main() {
	srand(time(0));
	//wartosci od 1 do 1000
	drzewo *korzen=NULL;
	int wylosowane[1000];
	int i, polecenie, n, x, ile_wyl=0, wyswietl;
	do {
		start();
		scanf("%d", &polecenie);
		system("cls");
		switch(polecenie) {
			case 0:
				printf("Zakonczono dzialanie programu.");
				break;
			case 1:
				while(1) {
					printf("Podaj liczbe elementow do dodania: ");
					scanf("%d", &n);
					if(n+ile_wyl<=1000)
						break;
					else
						printf("Nie mozna wprowadzic wiecej jak 1000 liczb!\nObecnie w drzewie jest %d wartosci.\n\n", ile_wyl);
				}
				for(i=0;i<n;i++) {
					x=rand()%1000+1;
					//scanf("%d", &x);
					if(!bylo(x, wylosowane, ile_wyl)) {
						wylosowane[ile_wyl]=x;
						ile_wyl++;
						insertBST(&korzen, x);
					} else
						i--;
				}
				printf("Pomyslnie dodano liczby.\n\nKliknij aby kontynuowac.");
				getch();
				break;
			case 2:
				printf("Tryby wyswietlania\n"); 
				printf("1 - inorder (LVR),\n");
				printf("2 - preorder (VLR),\n");
				printf("3 - postorder (LRV),\n");
				printf("4 - level order,\n");
				printf("5 - graficzna (tekstowa) reprezentacja.\n");
				printf("Podaj tryb: ");
				scanf("%d", &wyswietl);
				switch(wyswietl) {
					case 1:
						printf("Kolejnosc przechodzenia: ");
						LVR(korzen);
						break;
					case 2:
						printf("Kolejnosc przechodzenia: ");
						VLR(korzen);
						break;
					case 3:
						printf("Kolejnosc przechodzenia: ");
						LRV(korzen);
						break;
					case 4:
						if(korzen==NULL)
							printf("Drzewo jest puste!");
						else
							LO(korzen);
						break;
					case 5:
						if(korzen==NULL)
							printf("Drzewo jest puste!");
						else {
							for(i=0;i<hBST(korzen);i++)
								printf("%d\t",i);
							graficznie(korzen, 0);
						}
						break;
					default:
						printf("Nie ma takiego trybu.");
						break;
				}
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 3:
				if(korzen==NULL)
					printf("Drzewo jest puste!");
				else {
					while(1) {
						printf("Podaj poziom: ");
						scanf("%d",&x);
						if(x>hBST(korzen))
							printf("Nie ma takiego poziomu!\n");
						else {
							printf("Liczba elementow na %d poziomie wynosi: %d", x, countLevBST(korzen, x));
							break;
						}
					}
				}
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 4:
				if(korzen==NULL)
					printf("Drzewo nie istnieje.");
				else
					printf("Wysokosc drzewa wynosi: %d", hBST(korzen)-1);
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 5:
				printf("Podaj wartosc do usuniecia: ");
				scanf("%d", &x);
				if(bylo(x, wylosowane, ile_wyl)) {
					for(i=bylo(x, wylosowane, ile_wyl)-1;i<ile_wyl;i++)
						wylosowane[i]=wylosowane[i+1];
					ile_wyl--;
					korzen=removeBST(korzen, x);
					printf("Pomyslnie usunieto wartosc.\n");
				} else
					printf("Takiej wartosci nie ma w drzewie.\n\n");
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 6:
				if(korzen==NULL)
					printf("Drzewo nie istnieje!\n");
					else if(checkBST(korzen, 0, licz_elementy(korzen)))
						printf("Drzewo jest kopcem.\n");
					else
						printf("Drzewo nie jest kopcem.\n");
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 7:
				if(korzen==NULL)
					printf("Drzewo nie istnieje!\n");
				else {
					if(checkBST(korzen, 0, licz_elementy(korzen)))
						tableBST(korzen);
					else
						printf("Nie mozna przedstawic drzewa w formie tabeli.\n");
				}
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
		}
	} while(polecenie);
	for(i=0;i<ile_wyl;i++)
		removeBST(korzen, wylosowane[i]);
	return 0;
}
