#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
    void * key;
    void * value;
} Entry;

typedef struct {
    Entry * entries;
    int size, total;
    Entry (*makeNode)(void*, void*);
    int (*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*, void*));
void dropSymbolTable(SymbolTable* tab);
void addEntry(void* key, void* value, SymbolTable* book);
Entry* getEntry(void* key, SymbolTable book);

//// makeNode
Entry makeNode(void* name, void* phone){
  Entry res;
  res.key = strdup((char*)name);
  res.value=malloc(sizeof(int));
  memcpy(res.value,phone,sizeof(int));
  return res;
}

//// compare
int compare(void* a, void* b){
  return strcmp((char*)a,(char*)b);
}

//// createSymbolTable
SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*, void*)){
    SymbolTable new_PB;	
	new_PB.entries=(Entry*)malloc(INITIAL_SIZE*sizeof(Entry*));
	new_PB.total=0;
	new_PB.size=INITIAL_SIZE;
    new_PB.makeNode=makeNode;
    new_PB.compare=compare;
	return new_PB;
}

//// dropSymbolTable
void dropSymbolTable(SymbolTable* tab){
    free(tab->entries);
    free(tab);
}

//// addEntry
void addEntry(void* key, void* value, SymbolTable* book){
	int i;
	for (i=0;i<book->total;i++){
		if(strcmp((char*)key,(char*)book->entries[i].key)==0) {
			memcpy(&book->entries[book->total].value,&value,sizeof(Entry));
			return;
		}		
	}

	if(book->total>book->size){
		book->entries=(Entry*)realloc(book,INCREMENTAL_SIZE*sizeof(Entry*));
		book->size+=INCREMENTAL_SIZE;
	}
		memcpy(&book->entries[book->total].value,&value,sizeof(Entry));
        memcpy(&book->entries[book->total].key,&key,sizeof(Entry));
		book->total++;	    
}

//// getEntry
Entry* getEntry(void* key, SymbolTable book){
    int i;
	for (i=0;i<book.total;i++){
		if(strcmp((char*)key,(char*)book.entries[i].key)==0) return book.entries;
			
	}
}

//// main
int main(){
	SymbolTable book;

	book = createSymbolTable(makeNode,compare);

	addEntry("Do Lam",909090,&book);
	addEntry("Tuan Dung",929292,&book);
	addEntry("Anh Thang",919191,&book);
	addEntry("Ngo Phong",949494,&book);
	
	int i;
	for (i=0;i<book.total;i++) printf("%s %d\n",book.entries[i].key,book.entries[i].value);
    
    Entry *y;
    y=getEntry("Do Lam",book);
    printf("%d",book.entries->value);
    dropSymbolTable(&book);
}
