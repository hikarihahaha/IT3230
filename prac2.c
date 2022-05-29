#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#define ll long long
#define max(a,b) a>b ? a : b
#define min(a,b) a<b ? a : b
#define N 256
typedef struct Studentnode{
    char id[10], name[50];
	double toan, ly, hoa;
	struct Studentnode *next;
}Studentnode;

Studentnode *first, *last;
void init(){
    first = NULL; last = NULL;
}

int isEmpty(){
    return first == NULL && last == NULL;
}

Studentnode *makenode(char *Id, char *Name, double Toan, double Ly, double Hoa){
    Studentnode *p = (Studentnode*)malloc(sizeof(Studentnode));
    strcpy(p->id, Id);
    strcpy(p->name, Name);
    p->toan = Toan;
    p->ly = Ly;
    p->hoa = Hoa;
    p->next = NULL;
    return p;
}

void insertnode(char *Id, char *Name, double Toan, double Ly, double Hoa){
    Studentnode *p = makenode(Id, Name, Toan, Ly, Hoa);
    if(isEmpty()){
        first = last = p;
    }
    else{
        last->next = p;
        last = p;
    }
}
void insert(){
    char Id[10], Name[50];
	double Toan, Ly, Hoa;
    printf("Enter Id: ");
    scanf("%s", &Id);
    fflush(stdin);
    printf("Enter name: ");
    gets(Name);
    fflush(stdin);
    printf("Enter scores: ");
    scanf("%lf%lf%lf", &Toan, &Ly, &Hoa);
    for(Studentnode *p = first; p!= NULL; p=p->next){
        if(strcmp(Id, p->id) == 0){
            printf("Id exists, please re-enter\n");
            printf("Enter Id: ");
            scanf("%s", &Id);
            fflush(stdin);
            printf("Enter name: ");
            gets(Name);
            fflush(stdin);
            printf("Enter scores: ");
            scanf("%lf%lf%lf", &Toan, &Ly, &Hoa);
        }
    }
    insertnode(Id, Name, Toan, Ly, Hoa);
}

void printList(){
    Studentnode *p = first;
    if(p == NULL){
        printf("List is empty\n");
        return;
    } else{
        printf("%-10s%-20s%-10s%-10s%-10s\n", 
        "ID", "Name", "Math", "Physics", "Chemistry");
        printf("----------------------------------------------------------------\n");
        for(p = first; p != NULL; p = p->next)
            printf("%-10s%-20s%-10.2f%-10.2f%-10.2f\n", 
                p->id, p->name, p->toan, p->ly, p->hoa);
        printf("----------------------------------------------------------------\n");
    }
}

Studentnode *delete(Studentnode *p, char *Id){
    if(isEmpty()) return NULL;
    if(strcmp(Id, p->id) == 0){
        Studentnode *temp = p->next;
        free(p);
        if(temp == NULL) last = NULL;
        return temp;
    } else{
        p->next = delete(p->next, Id);
        return p;
    }
}
void removeNode(){
    char Id[10];
    scanf("%s", &Id);
    first = delete(first, Id);
}

void findbigger(){
    int n; scanf("%d", &n);
    printf("%-10s%-20s%-10s%-10s%-10s\n", 
            "ID", "Name", "Math", "Physics", "Chemistry");
    printf("----------------------------------------------------------------\n");
    for(Studentnode *p = first; p!= NULL; p=p->next){
        if(p->toan + p->ly + p->hoa > n){
            printf("%-10s%-20s%-10.2f%-10.2f%-10.2f\n", 
                    p->id, p->name, p->toan, p->ly, p->hoa);
        }
    }
    printf("----------------------------------------------------------------\n");
}

void load(char *filename){
    char Id[10], Name[50];
	double Toan, Ly, Hoa;
    FILE *f = fopen(filename, "r");
    if(f == NULL){
		printf("File couldn't be opened\n");
		return;
	} else{
        int n;
        fscanf(f, "%d", &n);
        while(!feof(f)){
            fscanf(f, "%s\n", &Id);
            fgets(Name, 50, f);
            Name[strcspn(Name, "\n")] = 0;
            fscanf(f, "%lf %lf %lf\n", &Toan, &Ly, &Hoa);
            insertnode(Id, Name, Toan, Ly, Hoa);
        }
    }
    fclose(f);
}
void processLoad(){
    char filename[20];
    scanf("%s", &filename);
    load(filename);
}

void swap(Studentnode *a, Studentnode *b){
    Studentnode *temp = a;
    a = b;
    b = temp;
}
void swapNodes(){ // swap the pos of two node
    char id1[10], id2[10];
    scanf("%s %s", &id1, &id2);
    if(id1==id2) return;
    Studentnode *prevp1 = NULL, *currp1 = first;
    //Studentnode *p =first;
    while(currp1 && currp1->next != id1){
        prevp1 = currp1;
        currp1 = currp1->next;
    }
    Studentnode *prevp2 = NULL, *currp2 = first;
    while(currp2 && currp2->next != id2){
        prevp2 = currp2;
        currp2 = currp2->next;
    }
    if(currp1 == NULL || currp2 == NULL) return;

    if(prevp1 != NULL) prevp1->next = currp2;
    else first = currp2;

    if(prevp2 != NULL) prevp2->next = currp1;
    else first=currp1;

    Studentnode *temp = currp2->next;
    currp2->next = currp1->next;
    currp1->next = temp;
}

void save(char *filename){
	FILE *f = fopen(filename, "w+");
	if(f == NULL){
		perror("File not found\n");
	}else{
		Studentnode *p;
		for(p = first; p!=NULL; p=p->next){
			fprintf(f,"%s\n%s\n%.2f %.2f %.2f\n",p->id, p->name,p->toan, p->ly, p->hoa);
			if(p->next == NULL)	fprintf(f,"\n");
		}
	}
	fclose(f);
}
void processSave(){
    char filename[20];
    scanf("%s", &filename);
    save(filename);
}

int main(){
    init();
	while(1){
        printf("Enter command: ");
        char cmd[256];
        scanf("%s",cmd);
        if(strcmp(cmd,"***")==0) break;
        else if(strcmp(cmd,"Load")==0){
            processLoad();
            printList();
        }
        else if(strcmp(cmd,"Add")==0){
            insert();
            printList();
        }
        else if(strcmp(cmd,"Delete")==0){
            removeNode();
            printList();
        } 
        else if(strcmp(cmd,"Swap")==0) {
            swapNodes();
            printList();
        }
        else if(strcmp(cmd,"FindBigger")==0) findbigger();
        else if(strcmp(cmd,"Save")==0) processSave();
    }
    return 0;
}