
//
//  main.c
//  asp1_dz2_z1
//
//  Created by Marko Stankovic on 4/7/18.
//  Copyright © 2018 Marko Stankovic. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Tree{
    int id;
    int *data;
    struct Tree **sons;
    struct Tree* parent;
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
int *zavrsna;
Tree *root=NULL;
int m;
int tree_id=0;

int places_to_move[9][5]={{2,1,3},{3,0,2,4},{2,1,5},{3,0,4,6},{4,1,3,5,7},{3,2,4,8},{2,3,7},{3,4,6,8},{2,5,7}};


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

Tree* top_node;
int csons_max=0;
void insert_tree(Tree* root,int *mx,int m){
    
    
    if(*h_queue1==NULL){
        //root->data=mx;
        push_q(root,h_queue1,t_queue1);
        root->parent=NULL;
        top_node=root;
        (*h_queue1)->data->sons=(Tree**)calloc(m,sizeof(Tree*));
        c_sons=0;
        (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
        (*h_queue1)->data->sons[c_sons]->data=mx;
        (*h_queue1)->data->sons[c_sons]->id=tree_id++;
        (*h_queue1)->data->sons[c_sons]->parent=top_node;
        push_q((*h_queue1)->data->sons[c_sons],h_queue1,t_queue1);
        c_sons++;
        csons_max=m;
    }
    else{
        
            if(c_sons<csons_max){
                (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
                (*h_queue1)->data->sons[c_sons]->data=mx;
                (*h_queue1)->data->sons[c_sons]->id=tree_id++;
                (*h_queue1)->data->sons[c_sons]->parent=top_node;
                push_q((*h_queue1)->data->sons[c_sons],h_queue1,t_queue1);
                c_sons++;
            }
            else{
                pop_q(h_queue1,t_queue1);
                top_node=(*h_queue1)->data;
                (*h_queue1)->data->sons=(Tree**)calloc(m,sizeof(Tree*));
                c_sons=0;
                (*h_queue1)->data->sons[c_sons]=(Tree*)calloc(1,sizeof(Tree));
                (*h_queue1)->data->sons[c_sons]->data=mx;
                (*h_queue1)->data->sons[c_sons]->id=tree_id++;
                (*h_queue1)->data->sons[c_sons]->parent=top_node;
                push_q((*h_queue1)->data->sons[c_sons],h_queue1,t_queue1);
                c_sons++;
                csons_max=m;
            }
        }
    
    
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

void unos_pozicija(){
    int i;
    
    root=(Tree*)calloc(1,sizeof(Tree));
    root->data=(int*)calloc(9,sizeof(int));
    root->parent=NULL;
    root->id=tree_id++;
    
    zavrsna=(int*)calloc(9,sizeof(int));
    
    printf("Unesite matricu pocetnu \n");
    for(i=0;i<9;i++)
        scanf("%d",&root->data[i]);
    
    printf("Unesite matricu krajnju \n");
    for(i=0;i<9;i++)scanf("%d",&zavrsna[i]);
}


void generisanje_rand(){
    
    time_t t;
    srand((unsigned)time(&t));
    
    int array[9];
    int random;
    int i;
    
    
    root=(Tree*)calloc(1, sizeof(Tree));
    root->data=(int*)calloc(9,sizeof(int));
    root->parent=NULL;
    root->id=tree_id++;
    
    zavrsna=(int*)calloc(9,sizeof(int));
    
    for(int i=0;i<9;i++)array[i]=0;
    
    
    for(i=0;i<9;i++){
        random=rand()%9;
        if(array[random]==1){
            while(array[random]==1){
                random=rand()%9;
            }
            
        }
        array[random]=1;
        root->data[i]=random;
        
    }
    
    for(int i=0;i<9;i++)array[i]=0;
    
    for(i=0;i<9;i++){
        random=rand()%9;
        if(array[random]==1){
            while(array[random]==1){
                random=rand()%9;
            }
            
        }
        array[random]=1;
        zavrsna[i]=random;
        
    }
    
}

int correct_comb0(int *try){
    
    int i,end_position=11,start_position=10;
    
    for(i=0;i<9;i++) zavrsna[i]==0 ? end_position=i : end_position;
    for(i=0;i<9;i++) try[i]==0 ? start_position=i : start_position;
    return end_position==start_position ? 1 :0;
}

int** get_new_comb(int *old_comb){
    int **new_comb;
    int i,pos0,j;
    int br_pomeraja,index_pomeraja;
    for(i=0;i<9;i++)old_comb[i]==0 ? pos0=i:pos0;
    
    m=br_pomeraja=places_to_move[pos0][0];
    
    new_comb=(int**)calloc(places_to_move[pos0][0],sizeof(int*));
    for(i=0;i<br_pomeraja;i++) new_comb[i]=(int*)calloc(9,sizeof(int));
    
    for(i=0;i<br_pomeraja;i++){
        index_pomeraja=places_to_move[pos0][i+1];
        for(j=0;j<9;j++) {
            if(j==index_pomeraja){
                new_comb[i][j]=0;
            }
            else if (j==pos0){
                new_comb[i][j]=old_comb[index_pomeraja];
            }
            else{
                new_comb[i][j]=old_comb[j];
            }
        }
    }
    return new_comb;
}

void correct_combA(int *try){
    int klasa=0;
    int i,j,temp;

    for(i=0;i<9;i++){
        if(try[i]!=zavrsna[i]){
            for(j=0;j<9&&zavrsna[j]!=try[i];j++);
            temp=try[i];
            try[i]=try[j];
            try[j]=temp;
            klasa++;
        }
    }
    if(klasa%2==0){
        printf("Moguce je resenje\n");
    }
    else{
        printf("Nije moguce resenje\n");
    }
}

int correct_comball(int *try){
    int i;
    for(i=0;i<9;i++){
        if(try[i]!=zavrsna[i]){
            return 0;
        }
    }
    return 1;
}

void check_solution(Tree* root){
    
    int **new_comb;
    int *try;
    
    try=root->data;
    while(!correct_comb0(try)){
        
        new_comb=get_new_comb(try);
        for(int i=0;i<m;i++)
        {
            Tree* t=(Tree*)calloc(1,sizeof(Tree));
            t->data=new_comb[i];
            push_q(t, h_queue2, t_queue2);
        }
        try=pop_q(h_queue2, t_queue2)->data;
        
    }
    
    correct_combA(try);
    
}

void print_all_matrix(){
    int i;
    
    for(i=0;i<9;i++){
        if(i%3==0)
            printf("\n");
        printf("%d,",root->data[i]);
        
    }
    printf("\n");
    for(i=0;i<9;i++){
        if(i%3==0)
            printf("\n");
        printf("%d,",zavrsna[i]);
    }
}

void print_matrix_tree(Tree* t){
    for(int p=0;p<9;p++){
        if(p%3==0)
            printf("\n");
        printf("%d,",t->data[p]);
        
    }
    printf("\n");
}

void simulate_game(Tree* root){
    int **new_comb;
    int *try;
    int cnt=0;
    int i;
    
    try=root->data;
    while(!correct_comball(try)){
        
        if(cnt==0){
            new_comb=get_new_comb(try);
            try=new_comb[cnt++];
            insert_tree(root,try,m);
        }
        else if(cnt<m){
            try=new_comb[cnt];
            insert_tree(root, try, m);
            cnt++;
        }
        else if(cnt==m){
            cnt=0;
            try=(*h_queue1)->next->data->data;
            new_comb=get_new_comb(try);
            try=new_comb[cnt++];
            insert_tree(root,try,m);
        }
        //debuging
        /*for(int p=0;p<9;p++){
            if(p%3==0)
                printf("\n");
            printf("%d,",try[p]);
            
        }
        printf("\n");*/
    }
    top_node=(*t_queue1)->data;
    
    for(Tree* i=top_node;i!=NULL;i=i->parent){
       
        /*printf("top_node id=%d\n",i->id);
        for(int p=0;p<9;p++){
            if(p%3==0)
                printf("\n");
            printf("%d,",i->data[p]);
            
        }
        printf("\n");*/
        push_stack(i, stack1);
        
    }
    Tree* pom=(*stack1)->data;
    printf("Koraci su:\n");
    while(*stack1){
        pom=pop_stack(stack1);
        for(int p=0;p<9;p++){
            if(p%3==0)
                printf("\n");
            printf("%d,",pom->data[p]);
            
        }
        printf("\n");
        
    }
}

int main(int argc, const char * argv[]) {
    
    int option;
    
    
    stack1=(S_stack**)calloc(1,sizeof(S_stack*));
    h_queue1=(S_queue**)calloc(1,sizeof(S_queue*));
    t_queue1=(S_queue**)calloc(1, sizeof(S_queue*));
    
    h_queue2=(S_queue**)calloc(1,sizeof(S_queue*));
    t_queue2=(S_queue**)calloc(1, sizeof(S_queue*));
    
    
    
    while(1){
        
        printf("1.Unosenje pocetne i krajne pozicije \n");
        printf("2.Generisanje pocetne i krajnje pozicije rand \n");
        printf("3.Provera mogucnosti resenja \n");
        printf("4.Simulacija igre \n");
        printf("5.THE END \n");
        
        scanf("%d",&option);
        
        switch(option){
            case 1:{
                unos_pozicija();
            }break;
            case 2:{
                generisanje_rand();
            }break;
            case 3:{
                check_solution(root);
            }break;
            case 4:{
                simulate_game(root);
            }break;
            case 5:{
                print_all_matrix();
            }break;
            default:{
                return 0;
            }break;
        }
        
    }
}
    
