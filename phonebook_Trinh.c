#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
// --------------------------------------------------------------------------------
typedef struct
{
    char name[80];
    char number[20];
} phoneEntry;
// 
typedef struct {
    phoneEntry* entries;
    int total;
    int size;
} phoneBook;
// --------------------------------------------------------------------------------
phoneBook *phoneBookCreate();
void dropPhoneBook(phoneBook *book);
int binarySearch(phoneBook *book, int low, int high, char *name);
void addPhoneNumber(phoneBook *book, char *name, char *number);
phoneEntry *getPhoneNum(phoneBook *book, char *name);
void print(phoneBook *book);
// --------------------------------------------------------------------------------
phoneBook *phoneBookCreate()
{
    phoneBook *new_phoneBook = (phoneBook*)malloc(sizeof(phoneBook));
    new_phoneBook->entries = (phoneEntry*)malloc(sizeof(phoneEntry)*INITIAL_SIZE);
    new_phoneBook->size = INITIAL_SIZE;
    new_phoneBook->total = 0;

    return new_phoneBook;
}
// --------------------------------------------------------------------------------
void dropPhoneBook(phoneBook *book)
{
    free(book->entries);
    free(book);
}
// --------------------------------------------------------------------------------
int binarySearch(phoneBook *book, int low, int high, char *name)
{
    for(int i = low; i <= high; i++)
    {
        if (strcmp(book->entries[i].name, name) == 0)
            return i;
    }
    return -1;
}
// --------------------------------------------------------------------------------
void addPhoneNumber(phoneBook *book, char *name, char *number)
{
    int position = binarySearch(book, 0, book->total-1, name);
    if (position == -1)
    {
        if (book->total == book->size)
        {
            book->size = book->size + INCREMENTAL_SIZE;
            book->entries = (phoneEntry*)realloc(book->entries, sizeof(phoneBook)*book->size);
        }

        strcpy(book->entries[book->total].name, name);
        strcpy(book->entries[book->total].number, number);
        book->total++;
    }
    
    else strcpy(book->entries[position].number, number);
}
// --------------------------------------------------------------------------------
phoneEntry *getPhoneNum(phoneBook *book, char *name)
{
    int position = binarySearch(book, 0, book->total-1, name);
    if (position != -1)
        return &book->entries[position];
    return NULL;
}
// --------------------------------------------------------------------------------
void print(phoneBook *book)
{
    for(int i = 0; i < book->total; i++)
    {
        printf("%s\t%s\t\n", book->entries[i].name, book->entries[i].number);
    }
}
// --------------------------------------------------------------------------------
int main()
{
    phoneBook *book = NULL;
    book = phoneBookCreate();

    addPhoneNumber(book, "Trinh", "314");
    addPhoneNumber(book, "Trinh", "456");
    addPhoneNumber(book, "Vy", "32432");
    addPhoneNumber(book, "Thanh", "235");
    addPhoneNumber(book, "Duc", "325");
    addPhoneNumber(book, "Dang", "325");
    addPhoneNumber(book, "Khue", "235");

    printf("Sau khi duoc them:\n");
    print(book);

    printf("\nSau khi duoc lay:\n");
    phoneEntry *entry;
    entry = getPhoneNum(book, "Trinh");
    printf("%s\t%s\t\n", entry->name, entry->number);

    entry = getPhoneNum(book, "Vy");
    printf("%s\t%s\t\n", entry->name, entry->number);
    
    entry = getPhoneNum(book, "Thanh");
    printf("%s\t%s\t\n", entry->name, entry->number);
    
    entry = getPhoneNum(book, "Khue");
    printf("%s\t%s\t\n", entry->name, entry->number);

    dropPhoneBook(book);
    printf("\nXoa danh sach: Done!\n");
}
// --------------------------------------------------------------------------------