#include<stdio.h>
#include<stdlib.h>

#include"readBinary.h"
//#include "internalstorage.h"
#define totalIndex 17500

struct list{
  int id;
  double price;
  int quantity;
  char side;
  struct list *next;
  struct list *prev;
  struct list *nextP;
  struct list *prevP;
};
static struct list *hashmap[totalIndex];


int hashIndex(int id){
  int index;
  index=id%totalIndex;
  return index;
}



struct list *newhashmap(int id,double price ,int quantity,char side){
  int index;
 
  struct list *newhashmap=(struct list*)malloc(sizeof(struct list));
  newhashmap->next=NULL;
  newhashmap->prev=NULL;
  index=hashIndex(id);
  newhashmap->id=id;
  newhashmap->price=price;
  newhashmap->quantity=quantity;
 
  newhashmap->side=side;
  newhashmap->nextP=NULL;
  newhashmap->prevP=NULL;
  
  if(hashmap[index]==NULL){ 
    hashmap[index]=newhashmap;
  }else{
    newhashmap->next=hashmap[index];
    hashmap[index]->prev=newhashmap;
    hashmap[index]=newhashmap;
  }
  return newhashmap;
}

struct list *findH(int id){
  int index;
  struct list *temp;
  index=id%totalIndex;
  temp=NULL;
  temp=hashmap[index];
  while(temp!=NULL){
    if(temp->id==id){
      return temp;
    }else
      temp=temp->next;
  }
  return temp;
}

int getQuantityH(int id){
  return findH(id)->quantity;
}

double getPriceH(int id){
  return findH(id)->price;
}

void changeQuantityH(int id,int quantity){
  (findH(id)->quantity)=(findH(id)->quantity)-quantity;
  if(findH(id)->quantity==0){

    deleteH(id);
  }
}
void changeQuantityR(int id,int quantity){
  findH(id)->quantity=quantity;
}
void changePriceH(int id,double price){
  (findH(id)->price)=price;
}

void changePriceAndQuantityH(int id,int quantity,double price){
 
 (findH(id)->quantity)=quantity;
  (findH(id)->price)=price;

}

int checkH(int id){
  int boo=1;
  if(findH(id)==NULL){
    boo=0;
  }else{
    boo=1;
  }
  return boo;

}

int deleteH(int id){
  int index;
   struct list *temp=NULL;
   struct list *temp2=NULL;
  index=id%totalIndex;
 
  temp=hashmap[index];
  if(temp!=NULL&&checkH(id)){
  if(temp->id==id){
    if(temp->next!=NULL){
    hashmap[index]=temp->next;
    free(temp);
    }else{
       free(temp);
    hashmap[index]=NULL;
    }
  }
  }
  
  while(temp!=NULL&&temp->id!=id){
    temp2=temp->next;
    if(temp2!=NULL){
    if(temp2->id==id){
      temp->next=temp2->next;

      free(temp2);
    }
    }
     temp=temp->next;
    
  }
  return 0;
}

void printHashmap(FILE *fileWriter){
  int i;
  struct list *temp;
  for(i=0;i<totalIndex;i++){
    temp=hashmap[i];
    while(temp!=NULL){
      fprintf(fileWriter,"%d %c %d %lf\n",temp->id,temp->side,temp->quantity,temp->price);
      temp=temp->next;
    }
  }
}


char getSide(int id){
  return findH(id)->side;
}
