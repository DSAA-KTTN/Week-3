#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
	char name[80];
	long number;
} PhoneEntry;

typedef struct {
	PhoneEntry * entries;
	int total;
	int size;
} PhoneBook;
	
PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);	
void addPhoneNumber(char * name, long number, PhoneBook* book);
PhoneEntry * getPhoneNumber(char * name,PhoneBook * book);	

//// createPhoneBook
PhoneBook createPhoneBook(){
	PhoneBook new_PB;	
	new_PB.entries=(PhoneEntry*)malloc(INITIAL_SIZE*sizeof(PhoneEntry*));
	new_PB.total=0;
	new_PB.size=INITIAL_SIZE;
	return new_PB;
}

//// dropPhoneBook
void dropPhoneBook(PhoneBook* book){
	free(book->entries);
	free(book);
}

//// addPhoneNumber
void addPhoneNumber(char * name, long number, PhoneBook* book){
	int i;
	for (i=0;i<book->total;i++){
		if(strcmp(name,book->entries[i].name)==0) {
			book->entries[i].number=number;
			return;
		}		
	}

	if(book->total>book->size){
		book->entries=(PhoneEntry*)realloc(book,INCREMENTAL_SIZE*sizeof(PhoneEntry*));
		book->size+=INCREMENTAL_SIZE;
	}
		book->entries[book->total].number=number;
		strcpy(book->entries[book->total].name,name);
		book->total++;	
}

//// getPhoneNumber
PhoneEntry * getPhoneNumber(char * name,PhoneBook* book){
	int i;
 	for(i=0;i<book->total;i++)
    if(strcmp(book->entries[i].name,name)==0) return &book->entries[i];
    return NULL;
}
int main(){
	PhoneBook book;

	book = createPhoneBook();
	addPhoneNumber("Do Lam",909090,&book);
	addPhoneNumber("Tuan Dung",929292,&book);
	addPhoneNumber("Anh Thang",919191,&book);
	addPhoneNumber("Ngo Phong",949494,&book);
	
	int i;
	for (i=0;i<book.total;i++) printf("%s %d\n",book.entries[i].name,book.entries[i].number);
	
	PhoneEntry * y;
	y=getPhoneNumber("Do Lam",&book);
	printf("%d",y->number);
	dropPhoneBook(&book);
}
