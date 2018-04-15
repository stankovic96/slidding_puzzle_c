//
//  main.c
//  asp1_dz2_z1
//
//  Created by Marko Stankovic on 4/7/18.
//  Copyright © 2018 Marko Stankovic. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>


typedef struct Tree{
    int data;
    struct Tree **sons;
}Tree;

typedef struct s_queue{
    Tree* data;
    struct s_queue* next;
}S_queue;

typedef struct s_stack{
    Tree* data;
    struct s_stack* next;
}S_stack;


S_stack** stack1;

S_queue** h_queue1;
S_queue** t_queue1;

S_queue** h_queue2;
S_queue** t_queue2;

int m;
int c_sons=0;
int heigh=0;

void push_stack(Tree* d,S_stack** stack){
    S_stack *pom;
    pom=(S_stack*)calloc(1,sizeof(S_stack));
    pom->data=d;
    pom->next=NULL;
    if(*stack==NULL){
        *stack=pom;
    }
    else{
        pom->next=*stack;
        *stack=pom;
    }
    
}

Tree* pop_stack(S_stack **stack){
    S_stack* pom;
    Tree* pom1=NULL;
    if(*stack!=NULL){
    pom=*stack;
    pom1=pom->data;
    pom->data=NULL;
    *stack=(*stack)->next;
    free(pom);
    }
    else{
        printf("Error stack is empty to pop \n");
    }
    return pom1;
}

void empty_stack(S_stack **stack){
    S_stack *pom;
    while(*stack){
        pom=(*stack)->next;
        (*stack)->data=NULL;
        free(*stack);
        *stack=pom;
    }
}

void push_q(Tree* d, S_queue** h_queue, S_queue** t_queue){
    S_queue* pom;
    pom=(S_queue*)calloc(1,sizeof(S_queue));
    if(pom==NULL){
        printf("Queue allocation mem error\n");
        exit(-1);
    }
    pom->data=d;
    pom->next=NULL;
    if((*h_queue)==NULL){
        (*h_queue)=pom;
        (*t_queue)=(*h_queue);
    }
    else{
        (*t_queue)->next=pom;
        (*t_queue)=pom;
    }
}

Tree* pop_q( S_queue** h_queue, S_queue** t_queue){
    Tree* pom=NULL;
    S_queue* pom1;
    if(h_queue!=NULL){
    pom1=(*h_queue);
    pom=(*h_queue)->data;
    *h_queue=(*h_queue)->next;
    pom1->data=NULL;
    free(pom1);
    }
    else{
        printf("Error:pop_q a head je null\n");
    }
    
    return pom;
    
}

int empty_q(S_queue** h_queue, S_queue** t_queue){
    if((*h_queue==NULL)&&(*t_queue==NULL)){
        return 1;
    }
    return 0;
}

Tree* create_tree(int m){
    Tree *pom;
    pom=(Tree*)calloc(1,sizeof(Tree));
    if(pom==NULL){
        printf("Nemoguce alociranje prostora za koren\n");
        return NULL;
    }
    
    return pom;
}

void insert_tree(Tree* root){
    int d;
    
    printf("Unesite podatak d\n");
    scanf("%d",&d);
    
    if(*h_queue1==NULL){
         root->data=d;
        push_q(root,h_queue1,t_queue1);
    }
    else{
        if((*h_queue1)->data->sons==NULL){
            (*h_queue1)->data->sons=(Tree**)calloc(m,sizeof(Tree*));
            c_sons=0;
            (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
            (*h_queue1)->data->sons[c_sons]->data=d;
            c_sons++;
        }
        else{
            if(c_sons<3){
                (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
                (*h_queue1)->data->sons[c_sons]->data=d;
                c_sons++;
            }
            else{
                Tree* pom;
                pom=pop_q(h_queue1,t_queue1);
                for(int i=0;i<3;i++){
                    push_q(pom->sons[i],h_queue1,t_queue1);
                }
                (*h_queue1)->data->sons=(Tree**)calloc(m,sizeof(Tree*));
                c_sons=0;
                (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
                (*h_queue1)->data->sons[c_sons]->data=d;
                c_sons++;
            }
        }
    }
  
}

void print_tree(Tree* root){
    Tree* pom;
    
    push_stack(root,stack1);
    while(*stack1){
        pom=pop_stack(stack1);
        
        while(pom!=NULL){
            printf("%d,",pom->data);
            if(pom->sons!=NULL){
            for(int i=m-1;i>0;i--){
                if(pom->sons[i]!=NULL){
                    push_stack(pom->sons[i],stack1);
                }
            }
                pom=pom->sons[0];
            }
            else{
                pom=NULL;
            }
        }
    }
    printf("\n");
    empty_stack(stack1);
}

void heigh_tree(Tree* root){
    Tree* i;
    for(i=root;i!=NULL;i=i->sons[0])heigh++;
    printf("Visina stabla je %d \n",heigh);
}

void delete_tree(Tree* root){
    int i;
    Tree* pom;
    
    push_q(root,h_queue2,t_queue2);
    pom=root;
    while(!empty_q(h_queue2, t_queue2)){
        for(i=0;i<m;i++){
            if(pom->sons[i]!=NULL){
            push_q(pom->sons[i], h_queue2, t_queue2);
            }
        }
        free(pom);
        pom=pop_q(h_queue2, t_queue2);
    }
    printf("Uspesno zavrseno brisanje\n");
}

int main(int argc, const char * argv[]) {
    
    int option;
    Tree *root=NULL;
    stack1=(S_stack**)calloc(1,sizeof(S_stack*));
    h_queue1=(S_queue**)calloc(1,sizeof(S_queue*));
    t_queue1=(S_queue**)calloc(1, sizeof(S_queue*));
    
    h_queue2=(S_queue**)calloc(1,sizeof(S_queue*));
    t_queue2=(S_queue**)calloc(1, sizeof(S_queue*));
    
    while(1){
   
    printf("1.Stvaranje stabla zadatog stepena \n");
    printf("2.Umetanje novog elementa \n");
    printf("3.Ispis stabla \n");
    printf("4.Brisanje stabla \n");
    printf("5.Odredjivanje visine stabla \n");
    
    scanf("%d",&option);
    
    switch(option){
        case 1:{
            
            printf("Unesite m \n");
            scanf("%d",&m);
            
            root=create_tree(m);
            if(root==NULL) return -1;
            
        }break;
        case 2:{
            insert_tree(root);
        }break;
        case 3:{
            print_tree(root);
        }break;
        case 4:{
            delete_tree(root);
        }break;
        case 5:{
            heigh_tree(root);
        }break;
        default:{
            return 0;
        }break;
    }
    
}
}
