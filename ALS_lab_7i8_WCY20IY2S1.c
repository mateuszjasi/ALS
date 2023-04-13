#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include<math.h> - biblioteka math nie ma funkcji max
#define max(x, y) ((x > y)? x:y) //definicja funkcji max

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
	"[3] Balansowanie BST\n"
	"[4] Usun element z drzewa\n"
	"[5] Usun wszystkie elementy drzewa\n"
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

int wysokosc(drzewo* korzen) {
    if(korzen==NULL)
        return 0;
    else {
        int lewo=wysokosc(korzen->lewo);
        int prawo=wysokosc(korzen->prawo);
        return 1+max(lewo,prawo);
	}
}

int bfAVL(drzewo* korzen) {
    if(korzen==NULL)
        return 0;
    return wysokosc(korzen->lewo)-wysokosc(korzen->prawo);
}

drzewo* insertAVL_new(int x) {
    drzewo* nowy=(drzewo*)malloc(sizeof(nowy));
    nowy->wartosc=x;
    nowy->lewo=NULL;
    nowy->prawo=NULL;
    return(nowy);
}

drzewo* RRotate(drzewo *y) {
    drzewo* x=y->lewo;
    drzewo* z=x->prawo;
    x->prawo=y;
    y->lewo=z;
    return x;
}

drzewo* LRotate(drzewo *x) {
    drzewo* y=x->prawo;
    drzewo* z=y->lewo;
    y->lewo=x;
    x->prawo=z;
    return y;
}

drzewo* insertAVL(drzewo* korzen, int x) {
    if(korzen==NULL)
        return(insertAVL_new(x));
    if(x<korzen->wartosc)
        korzen->lewo=insertAVL(korzen->lewo, x);
    else if(x>=korzen->wartosc)
        korzen->prawo=insertAVL(korzen->prawo, x);
    int balans=bfAVL(korzen);
    // LL
    if(balans>1 && x<korzen->lewo->wartosc)
        return RRotate(korzen);
    // RR
    if(balans<-1 && x>korzen->prawo->wartosc)
        return LRotate(korzen);
    // LR
    if(balans>1 && x>korzen->lewo->wartosc) {
        korzen->lewo=LRotate(korzen->lewo);
        return RRotate(korzen);
    }
    // RL
    if(balans<-1 && x<korzen->prawo->wartosc) {
        korzen->prawo=RRotate(korzen->prawo);
        return LRotate(korzen);
    }
	return korzen;
}

drzewo* nastepnik(drzewo* korzen) {
    drzewo* temp=korzen;
    while(temp->lewo!=NULL)
        temp=temp->lewo;
    return temp;
}

drzewo* remAVL(drzewo* korzen, int x) {
    if(korzen==NULL)
        return korzen;
    if(x<korzen->wartosc)
        korzen->lewo=remAVL(korzen->lewo, x);
    else if(x>korzen->wartosc)
        korzen->prawo=remAVL(korzen->prawo, x);
    else {
        if(korzen->lewo==NULL || korzen->prawo==NULL) {
            drzewo *temp=(korzen->lewo)? korzen->lewo : korzen->prawo;
            if(temp==NULL) {
                temp = korzen;
                korzen = NULL;
            }
            else
			*korzen=*temp;
            free(temp);
        }
        else {
            drzewo* temp=nastepnik(korzen->prawo);
            korzen->wartosc=temp->wartosc;
            korzen->prawo=remAVL(korzen->prawo, temp->wartosc);
        }
    }
    if(korzen==NULL)
		return korzen;
    int balans=bfAVL(korzen);
    // LL
    if(balans>1 && x<korzen->lewo->wartosc)
        return RRotate(korzen);
    // RR
    if(balans<-1 && x>korzen->prawo->wartosc)
        return LRotate(korzen);
    // LR
    if(balans>1 && x>korzen->lewo->wartosc) {
        korzen->lewo=LRotate(korzen->lewo);
        return RRotate(korzen);
    }
    // RL
    if(balans<-1 && x<korzen->prawo->wartosc) {
        korzen->prawo=RRotate(korzen->prawo);
        return LRotate(korzen);
    }
    return korzen;
}

drzewo* remALL(drzewo* korzen) {
	if(korzen->lewo) remALL(korzen->lewo);
	if(korzen->prawo) remALL(korzen->prawo);
	free(korzen);
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
						korzen=insertAVL(korzen, x);
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
				//gen(bst), bal(bst) <-> bst->avl
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 4:
				printf("Podaj wartosc do usuniecia: ");
				scanf("%d", &x);
				if(bylo(x, wylosowane, ile_wyl)) {
					for(i=bylo(x, wylosowane, ile_wyl)-1;i<ile_wyl;i++)
						wylosowane[i]=wylosowane[i+1];
					ile_wyl--;
					korzen=remAVL(korzen, x);
					printf("Pomyslnie usunieto wartosc.\n");
				} else
					printf("Takiej wartosci nie ma w drzewie.\n\n");
				printf("\nKliknij aby kontynuowac.");
				getch();
				break;
			case 5:
				if(korzen) remALL(korzen);
				korzen=NULL;
				printf("Usunieto wszystkie elementy drzewa\nKliknij aby kontynuowac.");
				getch();
				break;
		}
	} while(polecenie);
	if(korzen) remALL(korzen);
	free(korzen);
	return 0;
}
