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

int hashIndex(int);
int getSide(int);
struct list *newhashmap(int,double,int,char);

struct list *findH(int);

int getQuantityH(int);

int getPriceH(double);

void changeQuantityH(int,int);

void changePriceH(int,double);

int deleteH(int);

void changePrcieAndQuantityH(int, int,double);

void printHashmap(FILE *);
