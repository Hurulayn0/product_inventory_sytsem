#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ProductKind {
    MUSIC = 1,
    BOOK,
    MAGAZINE
};

struct Music {
    char musician[30];
    char album[30];
};

struct Book {
    char author[30];
    char title[100];
};

struct Magazine {
    char name[30];
};

union Item {
    struct Music music;
    struct Book book;
    struct Magazine magazine;
};

struct Product {
    char barcode[10];
    int stock_amount;
    enum ProductKind kind;
    union Item item;
    struct Product* next;
};

struct Product* findProduct(struct Product* list, char* barcode) {
    struct Product* current = list;
    while (current != NULL) {
        if (strcmp(current->barcode, barcode) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateStock(struct Product* list) {
    int change;
    char barcode[10];

    while (1) {
        printf("Enter barcode to update: ");
        scanf("%s", barcode);
        if (strcmp(barcode, "0") == 0) {
            break;
        }
        struct Product* product = findProduct(list, barcode);
        if (product == NULL) {
            printf("Product not found.\n");
            continue;
        }
        printf("Enter change in stock amount: ");
        scanf("%d", &change);
        product->stock_amount += change;
        printf("New stock amount for ");
        switch (product->kind) {
        case MUSIC:
            printf("%s album is %d.\n", product->item.music.album, product->stock_amount);
            break;
        case BOOK:
            printf("%s book in %d.\n", product->item.book.title, product->stock_amount);
            break;
        case MAGAZINE:
            printf("%s magazine is %d.\n", product->item.magazine.name, product->stock_amount);
            break;
        }
    }
}

int main() {
    struct Product products[] = {
        {"10221", 5, MUSIC, .item.music = {"Jennifer Lopez", "A.K.A."}, NULL},
        {"10222", 10, MUSIC, .item.music = {"Shakira", "Shakira"}, NULL},
        {"10223", 7, BOOK, .item.book = {"K. N. King", "C Programming: A Modern Approach"}, NULL},
        {"10224", 12, MAGAZINE, .item.magazine = {"Time"}, NULL}
    };

    for (int i = 0; i < sizeof(products) / sizeof(products[0]) - 1; i++) {
        products[i].next = &products[i + 1];
    }

    updateStock(&products[0]);

    return 0;
}
