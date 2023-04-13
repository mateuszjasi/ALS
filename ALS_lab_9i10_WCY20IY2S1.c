#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max(x, y) ((x > y)? x:y) //definicja funkcji max
#define col(x) ((x)? 'R':'B') //zwraca litere R, kiedy element jest czerwony lub w przeciwnym wypadku B

typedef struct drzewo {
	int t1, t2, max, bf, col; //t1 - key, col - kolor 1-czerwony 0-czarny
	struct drzewo *r, *l, *p; //r - prawo | l - lewo | p - rodzic
} drzewo;

drzewo *korzen=NULL;

void start() {
	system("cls");
	printf("Drzewo czerwono czarne\n"
	"--------------------------------------------------------\n"
	"[0] Wyjscie z programu\n"
	"[1] Dodaj wezel\n"
	"[2] Wyswietl drzewo\n"
	"[3] Szukaj elementu\n"
	"[4] Sprawdz czy spelnione sa zasady drzewa RB\n"
	"[5] Usun element z drzewa\n"
	"[6] Usun wszystkie elementy drzewa\n"
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

int bfRB(drzewo* korzen) {
    if(korzen==NULL)
        return 0;
    return wysokosc(korzen->l)-wysokosc(korzen->r);
}

void LVR(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		if(korzen->l!=NULL)
			LVR(korzen->l);
		printf("[%d, %d] ", korzen->t1, korzen->t2);
		if(korzen->r!=NULL)
			LVR(korzen->r);
	}
}

void VLR(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		printf("[%d, %d] ", korzen->t1, korzen->t2);
		if(korzen->l!=NULL)
			VLR(korzen->l);
		if(korzen->r!=NULL)
			VLR(korzen->r);
	}
}

void LRV(drzewo *korzen) {
	if(korzen==NULL)
		printf("Drzewo jest puste!");
	else {
		if(korzen->l!=NULL)
			LRV(korzen->l);
		if(korzen->r!=NULL)
			LRV(korzen->r);
		printf("[%d, %d] ", korzen->t1, korzen->t2);
	}
}

int wysokosc(drzewo* korzen) {
    if(korzen==NULL)
        return 0;
    else {
        int lewo=wysokosc(korzen->l);
        int prawo=wysokosc(korzen->r);
        return 1+max(lewo, prawo);
	}
}

void graficznie(drzewo* korzen, int x) {
	int i;
	if(korzen==NULL)
        return;
    x++;
    graficznie(korzen->r, x);
    printf("\n");
    for (i=1; i<x; i++)
        printf("\t");
    printf("%c[%d, %d], max: %d, bf: %d", col(korzen->col), korzen->t1, korzen->t2, korzen->max, korzen->bf);
	graficznie(korzen->l, x);
}

void RRotate(drzewo* temp) {
	drzewo* left=temp->l;
	temp->l=left->r;
	if(temp->l)
		temp->l->p=temp;
    left->p=temp->p;
    if(!temp->p)
		korzen=left;
    else if(temp==temp->p->l)
		temp->p->l=left;
    else
		temp->p->r=left;
	left->r=temp;
    temp->p=left;
}

void LRotate(drzewo* temp) {
	drzewo* right=temp->r;
	temp->r=right->l;
	if(temp->r)
		temp->r->p=temp;
	right->p=temp->p;
	if(!temp->p)
		korzen=right;
    else if(temp==temp->p->l)
		temp->p->l=right;
    else
		temp->p->r=right;
	right->l=temp;
	temp->p=right;
}

drzewo* nowy_el(int x, int y) {
    drzewo* nowy=(drzewo*)malloc(sizeof(nowy));
    nowy->t1=x;
    nowy->t2=y;
    nowy->l=NULL;
    nowy->r=NULL;
    nowy->p=NULL;
    nowy->col=1;
    return(nowy);
}

drzewo* insertBST(drzewo* korzen, drzewo* temp) {
    if(korzen==NULL)
		return temp;
    if(temp->t1 < korzen->t1) {
    	korzen->l=insertBST(korzen->l, temp);
        korzen->l->p=korzen;
    }
    else if(temp->t1 >= korzen->t1) {
        korzen->r=insertBST(korzen->r, temp);
        korzen->r->p=korzen;
    }
    return korzen;
}

int main() {
	srand(time(0));
	int wylosowane[3000];
	int i, polecenie, n, x, y, ile_wyl=0, wyswietl;
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
					x=rand()%2999+1;
					y=rand()%(3000-x)+1+x;
					//scanf("%d%d", &x, &y);
					if(!bylo(x, wylosowane, ile_wyl)) {
						wylosowane[ile_wyl]=x;
						ile_wyl++;
						drzewo *temp=nowy_el(x,y);
						korzen=insertBST(korzen, temp);
						fix(korzen, temp);
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
				printf("4 - graficzna (tekstowa) reprezentacja.\n");
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
						else {
							for(i=0;i<wysokosc(korzen);i++)
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
				
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 4:
				
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
					//korzen=remAVL(korzen, x);
					printf("Pomyslnie usunieto wartosc.\n");
				} else
					printf("Takiej wartosci nie ma w drzewie.\n\n");
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 6:
				//if(korzen) remALL(korzen);
				korzen=NULL;
				printf("Usunieto wszystkie elementy drzewa\nKliknij aby kontynuowac.");
				getch();
				break;
		}
	} while(polecenie);
	//if(korzen) remALL(korzen);
		free(korzen);
	return 0;
}
