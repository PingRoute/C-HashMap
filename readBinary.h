struct AStruct{ 
  char type;
  unsigned int id;
  char side;
  char symbol[4];
  unsigned int quantity;
  double price;
}__attribute__((__packed__));
struct XStruct{
 char type;
  unsigned int id;
  char symbol[4];
}__attribute__((__packed__));
struct TStruct{
 char type;
  unsigned int id;
  char symbol[4];
  unsigned int quantity;
}__attribute__((__packed__));

struct CStruct{
 char type;
  unsigned int id;
  char symbol[4];
  unsigned int quantity;
}__attribute__((__packed__));

struct RStruct{
 char type;
  unsigned int id;
  char symbol[4];
  unsigned int quantity;
  double price;
}__attribute__((__packed__));

struct readType{
  char messageType;
}__attribute__((__packed__));
