/* ID 2015112525        - REPLACE WITH YOUR ID
 * NAME Lee Joon Byeong       - REPLACE WITH YOUR NAME */

 // LINKED_LIST SOURCE: https://dojang.io/mod/page/view.php?id=645
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

//LINKED_LIST NODE STRUCT
struct NODE{
    char s[30];
    int snum;
    struct NODE *next;
    struct NODE *prev;
};

// ADD NEWNODE AFTER HEAD NODE
void addNODE(struct NODE *A, char data[]){
    struct NODE *newNODE = malloc(sizeof(struct NODE));

    newNODE->next = A->next;
    if(newNODE->next!=NULL){
        newNODE->next->prev=newNODE;
    }
    newNODE->prev = A;
    strcpy(newNODE->s,data);
    newNODE->snum = 1;
    A->next = newNODE;
}

// DELETE NODE A
void deleteNODE(struct NODE *A){
    struct NODE *delNODE = A;

    if( A -> next != NULL){
        A->next->prev = A->prev;
    }
    if(A->prev != NULL){
        A->prev->next = A->next;
    }
    free(delNODE);
}

// SWAP DATA BETWEEN TWO NODE
void swapNODE(struct NODE *A, struct NODE *B){
    char stmp[30];
    int ntmp;

    strcpy(stmp,A->s);
    strcpy(A->s,B->s);
    strcpy(B->s,stmp);

    ntmp=A->snum;
    A->snum=B->snum;
    B->snum=ntmp;
}

// MAIN FUNCTION
 int main(){
    struct NODE *head = malloc(sizeof(struct NODE));
    head->next=NULL;

    char tmp[30];

    // FILE OPEN
    FILE *fp =fopen("input4a.txt","r");
    FILE *fp2 =fopen("out4a.txt","w");

    // MAKE LINKED_LIST
    while(1){
        fscanf(fp, "%s", tmp);
        if(strcmp(tmp,"Joonbyeong")==0){
            break;
        }
        else {
            addNODE(head,tmp);
            strcpy(tmp,"Joonbyeong");
        }
    }

    struct NODE *Mcurr = head -> next;
    struct NODE *Scurr = head -> next;

    // DELETE REPEATED NODE
    while(Mcurr != NULL){
        strcpy(tmp, Mcurr->s);
        Scurr = Mcurr -> next;
        while(Scurr != NULL){
            if(strcmp(tmp,Scurr->s)==0){
                deleteNODE(Scurr);
                Mcurr->snum++;
            }
            Scurr = Scurr->next;
        }
        Mcurr=Mcurr->next;
    }

    // SORT LIST
    Mcurr = head->next;
    while(Mcurr != NULL){
        Scurr=Mcurr->next;
        while(Scurr != NULL){
            if(Mcurr->snum < Scurr->snum){
                swapNODE(Mcurr,Scurr);
            }
            Scurr = Scurr->next;
        }
        Mcurr=Mcurr->next;
    }

    //PRINT DATA & FREE NODE
    Mcurr = head->next;
    while( Mcurr != NULL ){
        fprintf(fp2, "%s %d\n",Mcurr->s, Mcurr->snum);
        free(Mcurr);
        Mcurr = Mcurr->next;
    }

    free(Scurr);
    free(head);
    fclose(fp);
    fclose(fp2);
    return 0;
 }
