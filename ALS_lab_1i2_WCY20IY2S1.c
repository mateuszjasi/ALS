#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct list {
	int val;
	int valid;
	struct list *prev;
	struct list *next;
	struct list *bridge;
} list;

int gui() {
	system("cls");
	printf("Listy\n"
	"----------------------------------------------\n"
	"[0] Wyjscie z programu\n"
	"[1] Wyswietl wpisane wartosci\n"
	"[2] Wyswietl powiazania\n"
	"[3] Wylosuj i dodaj n liczb\n"
	"[4] Dodaj dowolne n liczb\n"
	"[5] Usun element z listy\n"
	"[6] Wyczysc pamiec (usuwa liste)\n"
	"----------------------------------------------\n\n"
	"Wybierz komende: ");
}

add(int x, list **start, list **ptr, int *bridge) {
	if(*bridge==0) {
		*bridge=1;
		(*start)->valid=1;
		(*start)->val=x;
		(*start)->prev=*start;
		(*start)->next=*start;
		(*start)->bridge=*start;
	} else if(*bridge==1 && (*start)->val%2!=x%2) {
		*bridge=2;
		list *ad;
		ad=(list*)malloc(sizeof(list));
		ad->val=x;
		ad->valid=0;
		ad->prev=ad;
		ad->next=ad;
		ad->bridge=*start;
		(*start)->bridge=ad;
	} else {
		if(x%2==(*start)->val%2)
			*ptr=*start;
		else
			*ptr=(*start)->bridge;
		while(!(x>=(*ptr)->val && x<=(*ptr)->next->val) && (*ptr)->next->bridge==NULL)
			*ptr=(*ptr)->next;
		list *ad;
		ad=(list*)malloc(sizeof(list));
		ad->bridge=NULL;
		ad->val=x;
		ad->valid=0;
		ad->prev=*ptr;
		ad->next=(*ptr)->next;
		(*ptr)->next->prev=ad;
		(*ptr)->next=ad;
		if(x%2==(*start)->val%2 && (*start)->val>=(*start)->prev->val) {
			(*start)->bridge->bridge=(*start)->prev;
			(*start)->valid=0;
			*start=(*start)->prev;
			(*start)->bridge=(*start)->next->bridge;
			(*start)->next->bridge=NULL;
			(*start)->valid=1;
		} else if(x%2!=(*start)->val%2 && (*start)->bridge->val>=(*start)->bridge->prev->val) {
			(*start)->bridge=(*start)->bridge->prev;
			(*start)->bridge->bridge=(*start)->bridge->next;
			(*start)->bridge->next->bridge=NULL;
		}
	}
}

print(list *ptr, int n) {
	int i=1;
	if(ptr->val%2==0)
		printf("\nParzyste\n");
	else
		printf("\nNieparzyste\n");
	printf(
	"-----------------\n"
	"| Lp. | Wartosc |\n");
	if(n==1) {
		do {
			printf("| %*i | %*d |\n", 3, i++, 7, ptr->val);
			ptr=ptr->next;
		} while(ptr->bridge==NULL);
	} else {
		do {
			ptr=ptr->prev;
			printf("| %*i | %*d |\n", 3, i++, 7, ptr->val);
		} while(ptr->bridge==NULL);
	}
	printf("-----------------");
	if(ptr!=ptr->bridge) {
		ptr=ptr->bridge;
		if(ptr->val%2==0)
			printf("\n\nParzyste\n");
		else
			printf("\n\nNieparzyste\n");
		printf(
		"-----------------\n"
		"| Lp. | Wartosc |\n");
		if(n==1) {
			do {
				printf("| %*i | %*d |\n", 3, i++, 7, ptr->val);
				ptr=ptr->next;
			} while(ptr->bridge==NULL);
		} else {
			do {
				ptr=ptr->prev;
				printf("| %*i | %*d |\n", 3, i++, 7, ptr->val);
			} while(ptr->bridge==NULL);
		}
		printf("-----------------\n");
	} else {
		if(ptr->val%2==0)
			printf("\nBrak nieparzystych.\n");
		else
			printf("\nBrak parzystych.\n");
	}
}

print_all(list *ptr) {
	int lp=1;
	char bridge[3];
	if(ptr->val%2==0)
		printf("Parzyste:\n");
	else
		printf("Nieparzyste:\n");
	printf(
	"---------------------------------------------------------------\n"
	"| Nr. elementu | Wartosc | Sasiad lewy | Sasiad prawy | Wezel |\n");
	do {
		if(ptr->bridge==NULL)
			strcpy(bridge,"NIE");
		else
			strcpy(bridge,"TAK");
		printf("| %*d | %*d | %*d | %*d |  %s  |\n", 12, lp++, 7, ptr->val, 11, ptr->prev->val, 12, ptr->next->val, bridge);
		ptr=ptr->next;
	} while(ptr->bridge==NULL);
	printf("---------------------------------------------------------------\n");
	if(ptr!=ptr->bridge) {
		ptr=ptr->bridge;
		if(ptr->val%2==0)
			printf("\n\nParzyste:\n");
		else
			printf("\n\nNieparzyste:\n");
		printf(
		"---------------------------------------------------------------\n"
		"| Nr. elementu | Wartosc | Sasiad lewy | Sasiad prawy | Wezel |\n");
		do {
			if(ptr->bridge==NULL)
				strcpy(bridge,"NIE");
			else
				strcpy(bridge,"TAK");
			printf("| %*d | %*d | %*d | %*d |  %s  |\n", 12, lp++, 7, ptr->val, 11, ptr->prev->val, 12, ptr->next->val, bridge);
			ptr=ptr->next;
		} while(ptr->bridge==NULL);
		printf("---------------------------------------------------------------\n");
	}
}

int free_one(list **start, list *ptr, int x, int *bridge) {
	int i=1;
	ptr=*start;
	if(x==i && *start==(*start)->next) {
		if(*bridge==1) {
			free(*start);
			*bridge=0;
			return 2;
		} else {
			*start=(*start)->bridge;
			(*start)->bridge=*start;
			free(ptr);
			(*start)->valid=1;
			*bridge=1;
			return 1;
		}
	}
	if(x==i) {
		(*start)->bridge->bridge=(*start)->next;
		(*start)->next->valid=1;
		*start=(*start)->next;
		(*start)->bridge=(*start)->prev->bridge;
		(*start)->prev->prev->next=*start;
		(*start)->prev=(*start)->prev->prev;
		free(ptr);
		return 1;
	}
	while(1) {
		ptr=ptr->next;
		i++;
		if(ptr->bridge!=NULL)
			break;
		if(i==x) {
			ptr->prev->next=ptr->next;
			ptr->next->prev=ptr->prev;
			free(ptr);
			return 1;
		}
	}
	ptr=ptr->bridge;
	if(x==i && ptr==ptr->next) {
		(*start)->bridge=*start;
		free(ptr);
		*bridge=1;
		return 1;
	}
	if(x==i) {
		ptr->next->bridge=ptr->bridge;
		ptr->next->prev=ptr->prev;
		ptr->prev->next=ptr->next;
		(*start)->bridge=ptr->next;
		free(ptr);
		return 1;
	} else {
		i++;
		do {
			ptr=ptr->next;
			if(i==x) {
				ptr->prev->next=ptr->next;
				ptr->next->prev=ptr->prev;
				free(ptr);
				return 1;
			}
			i++;
		} while(ptr->bridge==NULL);
		return 0;
	}
}

free_all(list **start, int *bridge) {
	list *ptr;
	ptr=(list*)malloc(sizeof(list));
	*start=(*start)->next;
	while((*start)->bridge==NULL) {
		ptr=*start;
		*start=(*start)->next;
		free(ptr);
	}
	if(*bridge==2) {
		ptr=*start;
		*start=(*start)->bridge;
		free(ptr);
		*start=(*start)->next;
		while((*start)->bridge==NULL) {
			ptr=*start;
			*start=(*start)->next;
			free(ptr);
		}
	}
	free(*start);
	*bridge=0;
}

int main() {
	srand(time(0));
	int n, i, bridge=0, polecenie, x;
	list *ptr, *start;
	ptr=(list*)malloc(sizeof(list));
	start=(list*)malloc(sizeof(list));
	start->valid=0;
	do {
		gui();
		fflush(stdin);
		scanf("%d",&polecenie);
		system("cls");
		switch(polecenie) {
			case 1:
				if(start->valid==1) {
					printf("Wypisz wartosci rosnaco(1) czy malejaco(2): ");
					fflush(stdin);
					scanf("%d",&n);
					if(n==1 || n==2)
						print(start, n);
					else
						printf("Nie ma takiego polecenia!");
				}
				else
					printf("Lista jest pusta");
				printf("\n\nKliknij aby kontynuowac.");
				fflush(stdin);
				getch();
				break;
			case 2:
				if(start->valid==1)
					print_all(start);
				else
					printf("Lista jest pusta");
				printf("\n\nKliknij aby kontynuowac.");
				fflush(stdin);
				getch();
				break;
			case 3:
				printf("Podaj liczbe elementow do wylosowania: ");
				fflush(stdin);
				scanf("%d",&n);
				for(i=0; i<n; i++)
					add(rand()%2000+1, &start, &ptr, &bridge);
				printf("\nPomyslnie dodano %d liczb.\n\nKliknij aby kontynuowac.", n);
				fflush(stdin);
				getch();
				break;
			case 4:
				printf("Podaj liczbe elementow do dodania: ");
				fflush(stdin);
				scanf("%d",&n);
				for(i=0; i<n; i++) {
					printf("Podaj wartosc %d: ",i+1);
					scanf("%d",&x);
					add(x, &start, &ptr, &bridge);
				}
				printf("\nPomyslnie dodano %d liczb.\n\nKliknij aby kontynuowac.", n);
				fflush(stdin);
				getch();
				break;
			case 5:
				if(start->valid==1) {
					printf("Podaj numer elementu do usuniecia (0 - anuluj): ");
					fflush(stdin);
					scanf("%d",&n);
					if(n>0) {
						i=free_one(&start, ptr, n, &bridge);
						if(i==2) {
							start=(list*)malloc(sizeof(list));
							start->valid=0;
						}
						if(i)
							printf("\nPomyslnie usunieto.");
						else
							printf("\nNie ma elementu o takim numerze.");
					} else
						printf("\nAnulowano usuwanie.");
				} else
					printf("Lista jest pusta.");
				printf("\n\nKliknij aby kontynuowac.");
				fflush(stdin);
				getch();
				break;
			case 6:
				if(start->valid==1) {
					printf("Jestes pewny ze chcesz wyczyscic pamiec? (1-tak, 0-nie): ");
					fflush(stdin);
					scanf("%d",&n);
					if(n) {
						free_all(&start, &bridge);
						start=(list*)malloc(sizeof(list));
						start->valid=0;
						printf("\nPomyslnie wyczyszczono pamiec.");
					} else
						printf("\nAnulowano czyszczenie.");
				} else
					printf("Lista juz jest pusta.");
				printf("\n\nKliknij aby kontynuowac.");
				fflush(stdin);
				getch();
				break;
		}
	} while(polecenie);
	if(start->valid==1)
		free_all(&start, &bridge);
	printf("Zakonczono dzialanie programu");
	return 0;
}
