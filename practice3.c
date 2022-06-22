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
typedef struct class{
    char classcode[11];
    char coursecode[11];
    char location[50];
    struct class *next;
}class;

class *first, *last;

void init(){
    first = NULL; last = NULL;
}
int isEmpty(){
    return first == NULL && last == NULL;
}

class *makenode(char *clcode, char *cocode, char *loc){
    class *newnode = (class*)malloc(sizeof(class));
    strcpy(newnode->classcode, clcode);
    strcpy(newnode->coursecode, cocode);
    strcpy(newnode->location, loc);
    newnode->next = NULL;
    return newnode;
}

void insertnode(char *clcode, char *cocode, char *loc){
    class *p = makenode(clcode, cocode, loc);
    if(isEmpty()){
        first = last = p;
    } else{
        last->next = p;
        last = p;
    }
}

void load(char *filename){
    char clcode[11], cocode[11], loc[50];
    FILE *f = fopen(filename, "r");
    if(f == NULL){
		printf("File couldn't be opened\n");
		return;
	  } else{
        while(!feof(f)){
            fscanf(f, "%s\n", &clcode);
            fgets(cocode, 50, f);
            cocode[strcspn(cocode, "\n")] = 0;
            fgets(loc, 50, f);
            loc[strcspn(loc, "\n")] = 0;
            insertnode(clcode, cocode, loc);
        }
    }
    fclose(f);
}
void processLoad(){
    char filename[20];
    scanf("%s", &filename);
    load(filename);
}

void print(){
    class *p = first;
    if(p == NULL){
        printf("List is empty\n");
        return;
    } else{
        printf("%-25s%-25s%-25s\n", 
            "class code", "course code", "location");
        printf("----------------------------------------------------------------------------------\n");
        for(p = first; p != NULL; p = p->next)
            printf("%-25s%-25s%-25s\n", 
                p->classcode, p->coursecode, p->location);
        printf("----------------------------------------------------------------------------------\n");
    }
}

class *delete(class *p, char *clcode){
    if(isEmpty()) return NULL;
    if(strcmp(clcode, p->classcode) == 0){
        class *temp = p->next;
        free(p);
        if(temp == NULL) last = NULL;
        return temp;
    } else{
        p->next = delete(p->next, clcode);
        return p;
    }
}
void processDelete(){
    char clcode[11];
    scanf("%s", &clcode);
    first = delete(first, clcode);
    print();
}

void find(){
    char cocode[256];
    scanf("%s", &cocode);
    int found = 0;
    class *p = first;
    printf("%-25s%-25s%-25s\n", "class code", "course code", "location");
    printf("----------------------------------------------------------------------------------\n");
    for(; p != NULL; p = p->next){
        if(strcmp(p->coursecode, cocode) == 0){
            found = 1;
            printf("%-25s%-25s%-25s\n", p->classcode, p->coursecode, p->location);
        }
    }
    printf("----------------------------------------------------------------------------------\n");
}

class *merge(class *a, class *b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    class *c;
    if(strcmp(a->classcode, b->classcode) < 0){
        c = a;
        c->next = merge(a->next, b);
    } else{
        c = b;
        c->next = merge(a, b->next);
    }
    return c;
}
class *mid_point(class *head){  
    if(head == NULL || head->next == NULL) return head;
    class *fast = head;
    class *slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next;
        if(fast->next == NULL) break;
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
class* merge_sort(class *head){
    if(head == NULL || head->next == NULL) return head;
    class *mid = mid_point(head);
    class *a = head;
    class *b = mid->next;
    mid->next = NULL;
    a = merge_sort(a);
    b = merge_sort(b);
    class *c = merge(a, b);
    return c;
}
void mergesort(){
    first = merge_sort(first);
    print();
}

void countclass(){
    class *p = first;
    int cnt[100] = {0};
    int dem=0;
    char list[100][100];
    for(; p != NULL; p = p->next){
        int check = 0;
        for(int i=0; i< dem; i++){
            if(strcmp(list[i], p->coursecode) == 0){
                check = 1;
                cnt[i]++;
                break;
            }
        }
        if(check == 0){
            strcpy(list[dem], p->coursecode);
            cnt[dem]++;
            dem++;
        }
    }
    for(int i=0; i<dem; i++)
        printf("%s %d\n", list[i], cnt[i]);
}

int main(){
    init();
	  while(1){
        printf("Enter command: ");
        char cmd[256];
        scanf("%s",cmd);
        if(strcmp(cmd,"***")==0) break;
        else if(strcmp(cmd,"Load")==0) processLoad();
        else if(strcmp(cmd,"Print")==0) print();
        else if(strcmp(cmd,"Delete")==0) processDelete();
        else if(strcmp(cmd,"Find")==0) find();
        else if(strcmp(cmd,"Sort")==0) mergesort();
        else if(strcmp(cmd,"Count")==0) countclass(); 
    }
    return 0;
}
