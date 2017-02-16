#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>
#include <pthread.h> 
#include "readBinary.h"
#include "hashmap.h"
#include "market.h"
#include "internalstorage.h"
#include "SSO.h"
 int tFlag=0;
char symbol[5];
int totalMessageCounter=0;
double high=0;
double low=0;

static int Tcounter=0;

 int N=14;
 int M=3;
static double C=0;
static double L=0;
static double H=0;
static double FSO=0;
static double SSO=0;
static double SL=0;
static int SSOcounter=0;
static int FSOcounter=0;




static double *t;
static double *FSOArray;
static double *SSOArray;




unsigned int byteread=0;
int counter=0;
char *buffer;
void sigintHandler(int signal){
  printf("Program killed after processing %d messages for symbol %s.\n",totalMessageCounter,symbol);
  exit(0);
}
void segfaultHandler(int signal){
  printf("Program died from a segmentation fault after processing %d messages for symbol %s.",totalMessageCounter,symbol);
  exit(0);
}
static struct prediction p;

struct prediction get_prediction(){
  if(tFlag==0){
    p.SSO=SSO;
    p.signal_line=SL;

    if((SSOArray[M-2]>80)&&(SSOArray[M-1]<80)&&(SL<SSOArray[M-1])){
    p.alert=SELL;
    }else if((SSOArray[M-2]<20)&&(SSOArray[M-1]>20)&&(SL>SSOArray[M-1])){
    p.alert=BUY;
  }else{
    p.alert=NO_ACTION;
  }

  }
  if(tFlag==1){
  p.SSO=low;
  p.signal_line=high;
  p.alert=NO_ACTION;
  }
  return p;
}

int main(int argc,char* argv[]){
  int abc=0;
 
  symbol[4]='\0';
  FILE *fpread=stdin,*fpwrite=stdout,*IQwriter;
  static unsigned int i;
  fpread=stdin;
  fpwrite=stdout;
  int bFlag=0;
  int sFlag=0;
  int cc=0;
  int messageCount=1000;
  int tempPrice=0;
  int iFlag=0;
  int c=0;
 
  signal(SIGINT,sigintHandler);
  signal(SIGSEGV,segfaultHandler);
  while ((cc=(getopt (argc, argv, "i:s:n:tm:"))) != -1){
    switch(cc)
      {
      case'i':
	iFlag=1;
	fpread=fopen(optarg,"r");
	break;
      case's':
	sFlag=1;
	strncpy(symbol,optarg,4);
	break;
      case't':
	tFlag=1;
	break;
      case'n':
	N=atoi(optarg);
	//	t=(double*)malloc((N+1)*sizeof(double));
	break;
      case'm':
	M=atoi(optarg);
	//	FSOArray=(double*)malloc(M*sizeof (double));
	//	SSOArray=(double*)malloc(M*sizeof(double));

	break;
      case'?':
	printf("please enter corrct command\n");
      }
  }
	t=(double*)malloc((N+1)*sizeof(double));
	FSOArray=(double*)malloc(M*sizeof (double));
	SSOArray=(double*)malloc(M*sizeof(double));
  for(abc=0;abc<N+1;abc++){
    t[abc]=0;
  }
  for(abc=0;abc<M;abc++){
    FSOArray[abc]=0;
    SSOArray[abc]=0;
  }

  struct AStruct Abuffer;
  struct XStruct Xbuffer;
  struct RStruct Rbuffer;
  struct CStruct Cbuffer;
  struct TStruct Tbuffer;
  struct readType type;
  struct list *headBuy=NULL,*tailBuy=NULL,*headSell=NULL,*tailSell=NULL;
  i=0;
  init_market(fpread,symbol);
  pthread_t thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
  pthread_create(&thread,NULL,market,NULL);

  buffer=get_inputs(&byteread);
  unsigned int id=0;
  char side='\0';
  unsigned int Quantity=0;
  double Price=0;

 
  while(byteread!=0){
   
    if(*buffer=='A'){	
      buffer+=sizeof(char);
      id = *((unsigned int *)buffer); 
      buffer+=sizeof(unsigned int);
      side=*((char*)buffer);
      buffer+=sizeof(char);
      buffer+=sizeof(char)*4;
      Quantity=*((unsigned int*)buffer);
      buffer+=sizeof(unsigned int);
      Price=*((double*)buffer);

      buffer+=sizeof(double);
      byteread=byteread-sizeof(struct AStruct);
      newhashmap(id,Price,Quantity,side);	
      i++;	 
      totalMessageCounter++;
      if(side=='B'){
	insert(&headBuy,&tailBuy,id);
      }else if(side=='S'){
	insert(&headSell,&tailSell,id);	
      }
    }else if(*buffer=='T'){
      buffer+=sizeof(char);
      id = *((unsigned int *)buffer); 
	C=findH(id)->price;
      buffer=buffer+sizeof(unsigned int);
      buffer+=sizeof(char)*4;
      Quantity=*((unsigned int*)buffer);
      buffer+=sizeof(unsigned int);
      i++;
      totalMessageCounter++;
      if(findH(id)->quantity==Quantity&&findH(id)->side=='B'){
	deleteP(&headBuy,&tailBuy,id);
      }else if(findH(id)->quantity==Quantity&&findH(id)->side=='S'){
	deleteP(&headSell,&tailSell,id);	    
      }
      changeQuantityH(id,Quantity); 
      if(tFlag==0){

	Tcounter=insertTrade(t,N,C,Tcounter);
	L=findLow(t,N);
	H=findHigh(t,N);
	FSO=calculateFSO(C,L,H);
	FSOcounter=insertFSO(FSOArray,M,FSOcounter,FSO);
	SSO=calculateSSO(FSOArray,M);
	SSOcounter=insertSSO(SSOArray,M,SSOcounter,SSO);
	SL=calculateSL(M,SSOArray);
	// 	printf("C:%lf SL:%lf SSO:%lf FSO:%lf L:%lf, H:%lf\n",C,SL,SSO,FSO,L,H);

      }
      byteread=byteread-sizeof(struct TStruct);
      if(headSell!=NULL){
	low=headSell->price; 
      }
      if(tailBuy!=NULL){
	high=tailBuy->price;
      }
 
	buffer=get_inputs(&byteread);
      
    }else if(*buffer=='C'){
      buffer+=sizeof(char);
      id = *((unsigned int *)buffer); 
      buffer+=+sizeof(unsigned int);
      buffer+=sizeof(char)*4;
      Quantity=*((unsigned int*)buffer);
      buffer+=sizeof(unsigned int);
      i++;
      totalMessageCounter++;
      if(findH(id)->quantity==Quantity&&findH(id)->side=='B'){
	deleteP(&headBuy,&tailBuy,id);
      }else if(findH(id)->quantity==Quantity&&findH(id)->side=='S'){
	deleteP(&headSell,&tailSell,id);	    
      }
      changeQuantityH(id,Quantity); 



 


      byteread=byteread-sizeof(struct CStruct);
    }else if(*buffer=='X'){
      buffer+=sizeof(char);
      id = *((unsigned int *)buffer);
      buffer+=sizeof(unsigned int); 
      buffer+=sizeof(char)*4;
      byteread=byteread-sizeof(struct XStruct);
 
      i++;	    
      totalMessageCounter++;


      if(findH(id)->side=='S'){
	deleteP(&headSell,&tailSell,id); 
      }else{
	deleteP(&headBuy,&tailBuy,id);
      }
      deleteH(id);	 	
    }else if(*buffer=='R'){	
      buffer+=sizeof(char);
      id=*(unsigned int*)buffer;
      buffer+=sizeof(unsigned int);
      buffer+=sizeof(char)*4;
      Quantity=*(unsigned int*)buffer;
      buffer+=sizeof(unsigned int);
      Price=*(double*)buffer;
      buffer+=sizeof(double);
      byteread=byteread-sizeof(struct RStruct);
      c=0;
      i++;
      totalMessageCounter++;
      if(findH(id)->side=='B'){  
	c=1;
	deleteP(&headBuy,&tailBuy,id);
      }else if(findH(id)->side=='S'){
	c=2;	    
	deleteP(&headSell,&tailSell,id);	  
      }	  
      changePriceAndQuantityH(id,Quantity,Price);
      if(c==1)
	insert(&headBuy,&tailBuy,id);
      else if(c==2)     
	insert(&headSell,&tailSell,id);	
    }    
 
  }
  if(byteread!=0){
    if(headSell!=NULL){
      low=headSell->price;
    }
    if(tailBuy!=NULL){
      high=tailBuy->price;
    }
    buffer=get_inputs(&byteread);
  }
  
  fclose(fpread);  
}
