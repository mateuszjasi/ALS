#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct list {
	int x, key, val;
	struct list *next;
} list;

list *head[4];
int tab[]={0,0,0,0};

addQuel(int q, int x, int key) {
	int i;
	list *tail;
	tail=(list*)malloc(sizeof(list));
	tail->x=x;
	tail->key=key;
	tail->val=1;
	if(head[q]->val==0) {
		head[q]=tail;
		tab[q]++;
	} else {
		list *add=head[q];
		for(i=0;i<tab[q]-1;i++)
			add=(add)->next;
		(add)->next=tail;
		tab[q]++;
	}
}

extractQuel(int q) {
	if(tab[q]>1) {
		list *rem=head[q];
		head[q]=head[q]->next;
		free(rem);
		tab[q]--;
	} else {
		free(head[q]);
		head[q]=(list*)malloc(sizeof(list));
		head[q]->val=0;
		tab[q]--;
	}
}

printQuel(int q, int n) {
	list *x;
	int i;
	printf("Lista %d - ilosc elementow %d:\n", q+1, tab[q]);
	if(tab[q]==n) {
		printf("UWAGA lista jest pelna!\n");
		if(head[q]->key<n)
			head[q]->key++;
	}
	if(tab[q]==0)
		printf("Kolejka jest pusta.\n");
	x=head[q];
	for(i=0;i<tab[q];i++, x=x->next)
		printf("%d(%d)\t", x->x, x->key);
	printf("\n");
}

screen(int n, int added) {
	int i;
	switch(added) {
		case -2:
			printf("Nie udalo sie wykonac cyklu usuwania.\n\n"); break;
		case -1:
			printf("Pomyslnie zainicjalizowano listy.\n\n"); break;
		case 0:
			printf("Nie udalo sie wykonac cyklu dodawania.\n\n"); break;
		case 1:
			printf("Pomyslnie wykonano cykl dodawania.\n\n"); break;
		case 2:
			printf("Pomyslnie wykonano cykl usuwania.\n\n"); break;
	}
	for(i=0;i<4;i++)
		printQuel(i, n);
}

int sum() {
	int sum=0, i;
	for(i=0;i<4;i++)
		sum+=tab[i];
	return sum;
}

int min(int n) {
	int i,min=n,j;
	for(i=3;i>=0;i--)
		if(tab[i]<=min) {
			min=tab[i];
			j=i;
		}
	return j;
}

maxKey(int *m1, int *m2) {
	int i,j;
	*m1=-1;
	*m2=-1;
	for(i=0;i<4;i++) {
		if(*m1==-1 && tab[i]>0) {
			*m1=head[i]->key;
			j=i;
		} else if(*m1!=-1 && *m1<head[i]->key && tab[i]>0){
			*m1=head[i]->key;
			j=i;
		}
	}
	for(i=0;i<4;i++) {
		if(*m2==-1 && i!=j && tab[i]>0)
			*m2=head[i]->key;
		else if(*m1!=-1 && *m2<head[i]->key && i!=j && tab[i]>0)
			*m2=head[i]->key;
	}
}

remKey1(int m1, int *j) {
	int i;
	for(i=0;i<4;i++)
		if(m1==head[i]->key && tab[i]>0) {
			extractQuel(i);
			*j=i;
			break;
		}
}

remKey2(int m2, int j) {
	int i;
	for(i=0;i<4;i++)
		if(m2==head[i]->key && i!=j && tab[i]>0) {
			extractQuel(i);
			break;
		}
}

int main() {
	int m1, m2, n, x, i, j, added=-1;
	srand(time(0));
	printf("Podaj wielkosc bufora list: ");
	scanf("%d",&n);
	x=rand()%(4*n+1);
	for(i=0;i<4;i++) {
		head[i]=(list*)malloc(sizeof(list));
		head[i]->val=0;
	}
	for(i=0, j=0;j<x;i++,j++) {
		addQuel(i, rand()%1000+1, rand()%n+1);
		if(i==3)
			i=-1;
	}
	while(1) {
		//system("cls");
		screen(n,added);
		printf("\n\nKliknij dowolny klawisz, aby kontynuowac lub nacisnij 'x', aby zakonczyc.\n\n");
		fflush(stdin);
		if(getch()=='x')
			break;
		if(4*n-sum()>=4) {
			for(i=0;i<4;i++)
				addQuel(min(n), rand()%1000+1, rand()%n+1);
			added=1;
		} else
			added=0;
		screen(n,added);
		printf("\n\nKliknij dowolny klawisz, aby kontynuowac lub nacisnij 'x', aby zakonczyc.\n\n");
		fflush(stdin);
		if(getch()=='x')
			break;
		if(sum()>=2) {
			maxKey(&m1,&m2);
			remKey1(m1,&j);
			remKey2(m2,j);
			added=2;
		} else
			added=-2;
	}
	for(i=0;i<4;i++) {
		for(j=0;j<tab[i];j++)
			extractQuel(i);
		free(head[i]);
	}
	return 0;
}
