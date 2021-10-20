#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  char name[80];
  long number;
}PhoneEntry;
typedef struct Node{
  PhoneEntry key;
  struct Node* left;
  struct Node* right;
} NodeType;
typedef NodeType* PhoneBook;
int Empty(PhoneBook root){ return root==NULL; }
//
void createPhoneBook(PhoneBook *book);
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char* name, long number, PhoneBook* book);
PhoneBook getPhoneNumer(char* name, PhoneBook book);
void printPhoneBook(PhoneBook book,int *i);

void createPhoneBook(PhoneBook *book){
  (*book)=NULL;
}
struct Node *create_node(char* name, long number){
  struct Node *N;
  N=(struct Node*)malloc(sizeof(struct Node));
  if (N != NULL){
    N->left = NULL;
    N->right = NULL;
    strcpy((N->key).name,name);
    (N->key).number=number;
  }
  return N;
}
void dropPhoneBook(PhoneBook* book){
  if((*book)!=NULL){
    dropPhoneBook(&((*book)->left));
    dropPhoneBook(&((*book)->right));
    free((*book));
  }
}
PhoneBook getPhoneNumer(char* name,PhoneBook book){
  if (book == NULL) return NULL;
  if (strcmp((book->key).name,name)==0) return book;
  else if (strcmp((book->key).name,name)<0)
    return getPhoneNumer(name,book->right);
  else {
    return getPhoneNumer(name,book->left);
  }
}
void addPhoneNumber(char* name, long number, PhoneBook* book){
  if(book==NULL){ *book=create_node(name, number);
  }else if (strcmp(((*book)->key).name,name)>0) addPhoneNumber(name,number, &(*book)->left);
  else addPhoneNumber(name,number, &(*book)->right);
}
void printPhoneEntry(PhoneBook book,int i){
    printf("%3d   %30s   %ld\n",i,(book->key).name,(book->key).number);
}
void printPhoneBook(PhoneBook book,int *i){
  if(book!=NULL){
    printPhoneBook(book->left,i);
    (*i)++;
    printPhoneEntry(book,*i);
    printPhoneBook(book->right,i);
  }
}
int main(){
  int choice,i;
  PhoneBook book;
  createPhoneBook(&book);
  PhoneBook item;
  long number;
  char name[80];
  do{
    printf("MENU\n");
    printf("1. Add a Phone number\n");
    printf("2. Print the Phonebook\n");
    printf("3. Get a Phone number\n");
    printf("4. Drop the PhoneBook\n");
    printf("5. Exit\n");
    printf("-> Your choice: ");
    scanf("%d",&choice);
    while(getchar()!='\n');
    switch(choice){
    case 1:
      printf("Enter name of user: ");
      gets(name);
      printf("Enter the Phonenumber: ");
      scanf("%ld%*c",&number);
      addPhoneNumber(name,number,&book);
      break;
    case 2:
      i=0;
      printPhoneBook(book,&i);
      break;
    case 3:
      printf("Enter name of user: ");
      gets(name);
      item=getPhoneNumer(name,book);
      if(item!=NULL) printf("- Phonenumber: %ld\n",(item->key).number);
      else printf("Cant find phonenumber by this name!\n");
      break;
    case 4:
      dropPhoneBook(&book);
      createPhoneBook(&book);
      break;
    default:
      break;
    }
  }while(choice!=5);
  return 0;
}


