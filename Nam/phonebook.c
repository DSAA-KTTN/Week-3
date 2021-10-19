#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct{
  char name[80];
  long number;
}PhoneEntry;

typedef struct{
  PhoneEntry* entries;
  int total;
  int size;
}PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char* name, long number, PhoneBook* book);
PhoneEntry* getPhoneNumer(char* name, PhoneBook book);
void printPhoneBook(PhoneBook *book);

PhoneBook createPhoneBook(){
  PhoneBook p;
  p.entries=(PhoneEntry*)malloc(INITIAL_SIZE*sizeof(PhoneEntry));
  p.total=0;
  p.size=INITIAL_SIZE;
  return p;
}
void dropPhoneBook(PhoneBook* book){
free(book->entries);
book->size=0;
 book->total=0;
}
void addPhoneNumber(char* name, long number, PhoneBook* book){
  strcpy((book->entries[book->total]).name,name);
  (book->entries[book->total]).number=number;
  book->total++;
  if(book->total>book->size){
    book->entries=(PhoneEntry*)realloc(book->entries,sizeof(PhoneEntry)*INCREMENTAL_SIZE);
    book->size+=INCREMENTAL_SIZE;
  }
}
PhoneEntry* getPhoneNumer(char* name,PhoneBook book){
  int i;
  for(i=0;i<book.total;i++){
    if(strcmp((book.entries[i]).name,name)==0)
      return &book.entries[i];
  }
  return NULL;
}
void printPhoneBook(PhoneBook *book){
  int i;
  for(i=0;i<book->total;i++){
    printf("%d   %50s   %ld\n",i+1,(book->entries[i]).name,(book->entries[i]).number);
  }
}
int main(){
  int choice;
  PhoneBook book=createPhoneBook();
  PhoneEntry *item;
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
    scanf("%d%*c",&choice);
    switch(choice){
    case 1:
      printf("Enter name of user: ");
      gets(name);
      printf("Enter the Phonenumber: ");
      scanf("%ld%*c",&number);
      addPhoneNumber(name,number,&book);
      break;
    case 2:
      printPhoneBook(&book);
      break;
    case 3:
      printf("Enter name of user: ");
      gets(name);
      item=getPhoneNumer(name,book);
      if(item!=NULL) printf("- Phonenumber: %ld\n",item->number);
      else printf("Cant find phonenumber by this name!\n");
      break;
    case 4:
      dropPhoneBook(&book);
      break;
    default:
      break;
    }
  }while(choice!=5);
  return 0;
}


