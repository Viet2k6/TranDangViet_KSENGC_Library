#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    struct Book books[100];
    int count = 0;

    loadBooksFromFile(books, &count);
     
    char username[20];
    char password[10];
    char storedUsername[20];
    char storedPassword[10];
    
    readAccountFromFile(username, password);

    if (login(storedUsername, storedPassword)) {
        displaySystemName();
        
        int choice;
        while (1) {
            displayMenu();
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                addBook(books, &count);
                saveBooksToFile(books, count);
                break;
            case 2:
                displayBooks(books, count);
                break;
            case 3:
                searchBook(books, count);
                break;
            case 4:
                editBook(books, count);
                saveBooksToFile(books, count);
                break;
            case 5:
                deleteBook(books, &count);
                saveBooksToFile(books, count);
                break;
            case 6:
                sortBooksByPrice(books, count);
                break;
            case 0:
                printf("\n========= Thank you =========\n");
                printf("======== See you soon =======");
                return 0;
            default:
                printf("Invalid choice.\n");
            }
        }
    } else {
        printf("Login failed!\n");
    }

    return 0;
}
