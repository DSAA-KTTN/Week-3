#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"QuickSort3Way_Generic.h"
// --------------------------------------------------------------------------------
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10
// --------------------------------------------------------------------------------
typedef struct Entry{
    void *key;
    void *value;
} entry;
// 
typedef struct SymbolTable{
    entry *entries;
    int size, total;
    entry (*makeNode)(void*, void*);
    int (*compare)(void*, void*);
} symbolTable;
// --------------------------------------------------------------------------------
symbolTable symbolTableCreate(entry (*makeNode)(void*, void*), int (*compare)(void*, void*))
{
    symbolTable new_ST;
    new_ST.entries = (entry*)malloc(sizeof(entry)*INITIAL_SIZE);
    new_ST.size = INITIAL_SIZE;
    new_ST.total = 0;
    new_ST.makeNode = makeNode;
    new_ST.compare = compare;

    printf("Create a new Symbol Table: Completed!\n");
    return new_ST;
}
// --------------------------------------------------------------------------------
void symbolTableDrop(symbolTable *tab)
{
    free(tab->entries);
    free(tab);
    printf("Free the Symbol Table: Completed!\n");
}
// --------------------------------------------------------------------------------
int search(symbolTable *book, void *key)
{
    for (size_t i = 0; i < book->total; i++)
    {
        if(book->compare(book->entries[i].key, key) == 0)
        {
            return i;
        }
    }
    return -1;
}  
// --------------------------------------------------------------------------------
void entryAdd(void *key, void *value, symbolTable *book)
{
    entry new_entry = book->makeNode(key, value);

    int result = search(book, key);
    if (result == -1)
    {
        if (book->total == book->size)
        {
            book->size = book->size + INCREMENTAL_SIZE;
            book->entries = (entry*)realloc(book->entries, sizeof(entry)*book->size);
        }

        memcpy(&book->entries[book->total], &new_entry, sizeof(entry));
        book->total++;
    }

    else memcpy(&book->entries[result], &new_entry, sizeof(entry));
    printf("Add a new Entry: Completed!\n");
}
// --------------------------------------------------------------------------------
entry *entryGet(void *key, symbolTable book)
{
    int result = search(&book, key);
    if (result != -1)
        return &book.entries[result];
    return NULL;
}
// --------------------------------------------------------------------------------
// Hàm ví dụ
// --------------------------------------------------------------------------------
void *print(symbolTable *book)
{
    for (size_t i = 0; i < book->total; i++)
    {
        printf("%s\t%lu\n", book->entries[i].key, book->entries[i].value);
    }
}
entry makePhone(void* name, void* phone) {
    entry res;
    res.key = strdup( (char*)name );
    res.value = malloc(sizeof(long));
    memcpy( res.value, phone, sizeof(long) );
    return res;
}
// 
int comparePhone(void * key1, void* key2) {
    return strcmp((char*)key1, (char*)key2);
}
// --------------------------------------------------------------------------------
int main()
{
    symbolTable phoneBook = symbolTableCreate(makePhone, comparePhone);

    printf("\n");
    long number1 = 983984775;
    char name1[] = "Trinh";
    entryAdd(name1, &number1, &phoneBook);

    long number2 = 23445666;
    char name2[] = "Vy";
    entryAdd(name2, &number2, &phoneBook);

    long number3 = 2453453456;
    char name3[] = "Thanh";
    entryAdd(name3, &number3, &phoneBook);

    long number4 = 2346666;
    char name4[] = "Dang";
    entryAdd(name4, &number4, &phoneBook);

    long number5 = 2466466;
    char name5[] = "Khue";
    entryAdd(name5, &number5, &phoneBook);

    long number6 = 54777;
    char name6[] = "Duke";
    entryAdd(name6, &number6, &phoneBook);

    long number7 = 23475478;
    char name7[] = "Trinh";
    // entryAdd(name7, &number7, &phoneBook);
    
    printf("\nGet an Entry: Completed\n");
    entry *getEntry = entryGet("Trinh", phoneBook);
    printf("Entry: %s\t%lu\n", getEntry->key, getEntry->value);

    printf("\nBook created:\n");
    print(&phoneBook);

    printf("\n");
    symbolTableDrop(&phoneBook);
}
// --------------------------------------------------------------------------------
