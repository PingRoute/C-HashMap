#include<stdio.h>
int insertTrade(double t[],int n,double c,int Tcounter){
  int i;
  if(Tcounter<n+1){
    t[Tcounter]=c;
    Tcounter++;
  }else if(Tcounter==n+1){
    for(i=0;i<n;i++){
      t[i]=t[i+1];
    }
    t[n]=c;
  }
  return Tcounter;
}
double findLow(double t[],int n){
  double L=1000000;
  int i=0;
  for (i=0;i<n+1;i++){
    if(t[i]<L){
      L=t[i];
    }
  }
  return L;
}

double findHigh(double t[], int n){
  double H=-10000;
  int i=0;
  for(i=0;i<n+1;i++){
    if(t[i]>H){
      H=t[i];
    }
  }
  return H;
}

double calculateFSO(double c,double l,double h){
  double FSO=0;
  FSO=((c-l)/(h-l))*100;
  /* printf("c-l:%lf!!!!!!!\n",c-l);
  printf("h-l:%lf!!!!!!\n",h-l);
  printf("FSO: %lf!!!!!!!!!!!!!!!!\n",FSO);*/
  return FSO;
}

int insertFSO(double FSOArray[],int m,int FSOcounter,double FSO){
  int i=0;
  if(FSOcounter<m){
    // printf("FSO:%d\n",FSOcounter);
    FSOArray[FSOcounter]=FSO;
    //  printf("counter:%d FSO:%lf\n",FSOcounter,FSOArray[FSOcounter]);
    FSOcounter++;
    // printf("FSO:%d\n",FSOcounter);
  }else if(FSOcounter==m){
    for(i=0;i<m-1;i++){
      FSOArray[i]=FSOArray[i+1];
    }
    FSOArray[m-1]=FSO;
  }
  return FSOcounter;
}

double calculateSSO(double FSOArray[],int m){
  int counter=0;
  double sum=0;
  double SSO=0;
  while (counter<m){
    sum+=FSOArray[counter];
    counter++;
  }
  SSO=sum/m;
  return SSO;
}

int insertSSO(double SSOArray[],int m,int SSOcounter,double SSO){
  int i=0;
  if(SSOcounter<m){
    SSOArray[SSOcounter]=SSO;
    SSOcounter++;
  }else if(SSOcounter==m){
    for(i=0;i<m-1;i++){
      SSOArray[i]=SSOArray[i+1];
    }
    SSOArray[m-1]=SSO;
  }
  return SSOcounter;
}
double calculateSL(int m,double SSOArray[]){
  double sum=0;
  double SL=0;
  int i=0;
  for(i=0;i<m;i++){
    sum+=SSOArray[i];
  }
  SL=sum/m;
  return SL;
}


