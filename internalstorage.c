#include<stdio.h>
#include"hashmap.h"
double zero=0.0;
int priceChange(int id,double price){
  if(findH(id)->price!=price){
    return 1;
  }else 
    return 0;
}


void printIQ(FILE *IQwriter,struct list **headSell,struct list **tailBuy){

	if(*headSell==NULL&&*tailBuy==NULL){
	  
	  fprintf(IQwriter,"%lf %lf\n",zero,zero);
	}else if(*headSell==NULL){
	  fprintf(IQwriter,"%lf %lf\n",zero,(*tailBuy)->price);
	}else if(*tailBuy==NULL){
	  fprintf(IQwriter,"%lf %lf\n",(*headSell)->price,zero);
	}else{
	  fprintf(IQwriter,"%lf %lf\n",(*headSell)->price,(*tailBuy)->price);
	}
}


int deleteP(struct list** head,struct list** tail,int id){
  struct list *temp=findH(id);
  if(temp->prevP!=NULL&&temp->nextP!=NULL){
    temp->prevP->nextP=temp->nextP;
    temp->nextP->prevP=temp->prevP;
    temp->prevP=NULL;
    temp->nextP=NULL;
  }else if(temp->prevP==NULL&&temp->nextP==NULL){
    *head=NULL;
    *tail=NULL;
 }else if(temp->prevP==NULL){
    temp->nextP->prevP=NULL;
    *head=temp->nextP;
    temp->nextP=NULL;
  }else if(temp->nextP==NULL){
    temp->prevP->nextP=NULL;
    *tail=temp->prevP;
    temp->prevP=NULL;
  }
  return 0;
}

int insert(struct list **head,struct list**tail,int id){
  double price;
  struct list *temp;
  price=findH(id)->price;
  temp=*head;
  if(temp!=NULL){
    if(price<=temp->price){
      temp->prevP=findH(id);
      findH(id)->nextP=temp;
      *head=findH(id);
       findH(id)->prevP=NULL;
      (*head)->prevP=NULL;
      return 0;
    }
    if(price>=(*tail)->price){
      (*tail)->nextP=findH(id);
      findH(id)->prevP=(*tail);
      (*tail)=findH(id);
       findH(id)->nextP=NULL;
       (*tail)->nextP=NULL;
      return 0;
    }   
    
    while(temp->price<price){   
      temp=temp->nextP;
    } 
    temp->prevP->nextP=findH(id);
    findH(id)->prevP=temp->prevP;
    temp->prevP=findH(id);
    findH(id)->nextP=temp;
    return 0;
  }else if(temp==NULL&&(*tail)==NULL){
    *head=findH(id);
    *tail=findH(id);
    (*head)->prevP=NULL;
    (*tail)->nextP=NULL;
    (*head)->nextP=NULL;
    (*tail)->prevP=NULL;
    return 0;
  } 
}
