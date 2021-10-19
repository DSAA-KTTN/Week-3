#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct{
  void *key;
  void *value;
}Entry;

typedef struct{
  Entry* entries;
  int total;
  int size;
  Entry (*makeNode)(void*,void*);
  int (*compare)(void*, void*);
}SymbolTable;

SymbolTable createSymbolTable(
  Entry (*makeNode)(void*,void*),
  int (*compare)(void*, void*)
);
void dropSymbolTable(SymbolTable* tab);
void addEntry(void* key, void* value, SymbolTable* tab);
Entry* getEntry(void* key, SymbolTable tab);
void printAllEntries(SymbolTable *tab);

Entry makeNode(void* name, void* phone){
  Entry res;
  res.key = strdup((char*)name);
  res.value=malloc(sizeof(long));
  memcpy(res.value,phone,sizeof(long));
  return res;
}

int comparePhone(void* key1, void* key2){
  return strcmp((char*)key1,(char*)key2);
}

SymbolTable createSymbolTable( Entry (*makeNode)(void*,void*), int (*compare)(void*, void*)){
  SymbolTable p;
  p.entries=(Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
  p.total=0;
  p.size=INITIAL_SIZE;
  p.makeNode=makeNode;
  p.compare=compare;
  return p;
}
void dropSymbolTable(SymbolTable* tab){
free(tab->entries);
 tab->total=0;
 tab->size=0;
}
void addEntry(void* key,void* value, SymbolTable* tab){
  tab->entries[tab->total]=tab->makeNode(key,value);
  tab->total++;
  if(tab->total > tab->size){
    tab->entries=(Entry*)realloc(tab->entries,sizeof(Entry)*INCREMENTAL_SIZE);
    tab->size+=INCREMENTAL_SIZE;
  }
}
Entry* getEntry(void* key,SymbolTable tab){
  int i;
  for(i=0;i<tab.total;i++){
    if(tab.compare(tab.entries[i].key,key)==0)
      return &tab.entries[i];
  }
  return NULL;
}
void printAllEntries(SymbolTable *tab){
  int i;
  for(i=0;i<tab->total;i++){
    printf("%d   %50s   %ld\n",i+1,(char*)(tab->entries[i]).key,*(long*)((tab->entries[i]).value));
  }
}
int main(){
  int choice;
  SymbolTable book=createSymbolTable(makeNode,comparePhone);
  Entry *item;
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
      addEntry(name,&number,&book);
      break;
    case 2:
      printAllEntries(&book);
      break;
    case 3:
      printf("Enter name of user: ");
      gets(name);
      item=getEntry(name,book);
      if(item!=NULL) printf("- Phonenumber: %ld\n",*((long*)(item->value)));
      else printf("Cant find phonenumber by this name!\n");
      break;
    case 4:
      dropSymbolTable(&book);
      break;
    default:
      break;
    }
  }while(choice!=5);
  return 0;
}


