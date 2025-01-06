#include <stdio.h>
#include <string.h>
#include "functions.h"

//Tieu de he thong quan ly thu vien
void displaySystemName() {
	clearScreen();
	printf("***Library Management System Using C***\n");
}

void clearScreen() {
    printf("\033[H\033[J");	
}

//Menu chinh cua chuong trinh
void displayMenu() {
	printf("\n          MENU:\n");
	printf("============================\n");
	printf("[1] Add a new book\n");
	printf("[2] Show all books\n");
	printf("[3] Search a book\n");
	printf("[4] Edit a book\n");
	printf("[5] Delete a book\n");
	printf("[6] Sort books by price\n");
	printf("[0] Exit the program\n");
	printf("============================\n");
	printf("Enter your choice: ");
}

//Tai thong tin sach tu file
void loadBooksFromFile(struct Book books[], int* count) {
    const char* filename = "C:\\Users\\ADMIN\\Desktop\\Project C\\LibraryData.dat"; 

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing data found. Starting with an empty library.\n");
        *count = 0;
        return;
    }

    fread(count, sizeof(int), 1, file);
    fread(books, sizeof(struct Book), *count, file);
    fclose(file);

    printf("Books loaded successfully from %s.\n", filename);
}

//Luu thong tin sach vao file
void saveBooksToFile(struct Book books[], int count) {
    const char* filename = "C:\\Users\\ADMIN\\Desktop\\Project C\\LibraryData.dat"; 

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not save books to file %s.\n", filename);
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(books, sizeof(struct Book), count, file);
    fclose(file);

    printf("Books saved successfully to %s.\n", filename);
}

//Hien thi danh sach sach
void displayBooks(struct Book books[], int count) {
	clearScreen();
	printf("            ***LIBRARY***\n");
	if (count == 0) {
		printf("\nNo books available in the library.\n");
	    printf("\nGo back(9)? or Exit(0)? : ");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9'){
			clearScreen(); 
			return;
			}else if (choice == '0') {
				printf("\n========= Thank you =========\n");
				printf("======== See you soon =======\n");
				exit(0); 
			}
		} while (1);
		return;
	}
	printf("|=======|======================|===========================|=================|\n");
	printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
	printf("|=======|======================|===========================|=================|\n");
	int i;
	for (i = 0; i < count; i++) {
		printf("| %-5d | %-20s | %-25s | %-15d |\n",
			books[i].id,
			books[i].title,
			books[i].author,
			books[i].price);
		printf("|-------|----------------------|---------------------------|-----------------|\n");
	}
	printf("\nGo back(9)? or Exit(0)? : ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9'){
		clearScreen();  
		return;
		}else if (choice == '0') {
			printf("\n========= Thank you =========\n");
			printf("======== See you soon =======\n");
			exit(0); 
		}   
	} while (1);
}

// Tim kiem sach
void searchBook(const struct Book books[], int count) {
	clearScreen();
	printf("            ***Search A Book***\n");

	if (count == 0) {
		printf("\nNo books available to search.\n");
		printf("\nGo back(9)? or Exit(0)? : ");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9'){ 
			clearScreen();  
			return;
			}else if (choice == '0') {
				printf("\n========= Thank you =========\n");
				printf("======== See you soon =======\n");
				exit(0); 
			}
		} while (1);
		return;
	}
	char keyword[50];
	printf("Enter title or author to search: ");
	getchar();
	fgets(keyword, sizeof(keyword), stdin);
	keyword[strcspn(keyword, "\n")] = 0; 
	int found = 0;
	printf("\nSearch Results:\n");
	printf("|=======|======================|===========================|=================|\n");
	printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
	printf("|=======|======================|===========================|=================|\n");
    int i;
	for (i = 0; i < count; i++) {
		if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
			printf("| %-5d | %-20s | %-25s | %-15d |\n",
				books[i].id,
				books[i].title,
				books[i].author,
				books[i].price);
			printf("|-------|----------------------|---------------------------|-----------------|\n");
			found = 1;
		}
	}
	if (!found) {
		printf("\nNo matching books found.\n", keyword);
	}
	printf("\nGo back(9)? or Exit(0)? : ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9'){
		clearScreen();  
		return;
		}else if (choice == '0') {
			printf("\n========= Thank you =========\n");
			printf("======== See you soon =======\n");
			exit(0); 
		}
	} while (1);
}

//Them sach
void addBook(struct Book books[], int* count) {
    clearScreen();
    printf("            ***Add a New Book***\n");

    if (*count >= 100) {
        printf("\nLibrary is full. Cannot add more books.\n");
        printf("\nGo back(9)? or Exit(0)? : ");
        char choice;
        do {
            scanf(" %c", &choice);
            if (choice == '9'){ 
            clearScreen();  
			return;
            }else if (choice == '0') {
                printf("\n========= Thank you =========\n");
                printf("======== See you soon =======\n");
                exit(0); 
            }
        } while (1);
        return;
    }

    struct Book newBook;

    int validId = 0;
    do {
        printf("\nEnter Book ID: ");
        int input = scanf("%d", &newBook.id);  
        while(getchar() != '\n');  

        if (input != 1||newBook.id <= 0) {  
            printf("\nError: Book ID must be a positive number.\n");
        } else {
            int i;
            int exists = 0;
            for (i = 0; i < *count; i++) {
                if (books[i].id == newBook.id) {
                    exists = 1;
                    break;
                }
            }
            if (exists) {
                printf("\nError: Book ID %d already exists.\n", newBook.id);
            } else {
                validId = 1;  
            }
        }
    } while (!validId);

    do {
    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; 
    if (strlen(newBook.title) == 0) {
        printf("\nError: Book Title cannot be empty.\n");
    } else {
        int exists = 0;
        int i;
		for (i = 0; i < *count; i++) {
            if (strcmp(books[i].title, newBook.title) == 0) { 
                exists = 1;
                break;
            }
        }
        if (exists) {
            printf("\nError: Book Title \"%s\" already exists.\n", newBook.title);
        } else {
            break;
        }
    }
} while (1);

    do {
        printf("Enter Book Author: ");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = 0; 

        if (strlen(newBook.author) == 0) {
            printf("\nError: Book Author cannot be empty.\n");
        }
    } while (strlen(newBook.author) == 0); 

    do {
        printf("Enter Book Price: ");
        scanf("%d", &newBook.price);
        if (newBook.price < 0) {
            printf("\nError: Price cannot be negative.\n");
        }
    } while (newBook.price < 0); 

    books[*count] = newBook;
    (*count)++;
    printf("\nBook added successfully!\n");
    printf("\nGo back(9)? or Exit(0)? : ");
    char choice;
    do {
        scanf(" %c", &choice);
        if (choice == '9'){ 
        clearScreen();  
		return; 
        }else if (choice == '0') {
            printf("\n========= Thank you =========\n");
            printf("======== See you soon =======\n");
            exit(0); 
        }
    } while (1);
}
//Sua sach
void editBook(struct Book books[], int count) {
    clearScreen();
    printf("            ***Edit A book***\n");
    if (count == 0) {
        printf("\nNo books available to edit.\n");
        printf("\nGo back(9)? or Exit(0)? : ");
        char choice;
        do {
            scanf(" %c", &choice);
            if (choice == '9'){ 
            clearScreen();  
            return;
            }else if (choice == '0') {
                printf("\n========= Thank you =========\n");
                printf("======== See you soon =======\n");
                exit(0); 
            }
        } while (1);
        return;
    }

    int id;
    printf("\nEnter the ID of the book to edit: ");
    scanf("%d", &id);
    
    int i,j;
    for (i = 0; i < count; i++) {
        if (books[i].id == id) {
            char newTitle[50];
            int isExists;
            do {
                printf("Enter new Book Title: ");
                getchar(); 
                fgets(newTitle, sizeof(newTitle), stdin);
                newTitle[strcspn(newTitle, "\n")] = 0; 
                
                if (strlen(newTitle) == 0) {
                    printf("\nError: Book Title cannot be empty.\n");
                    isExists = 1; 
                } else {
                    isExists = 0;
                    for (j = 0; j < count; j++) {
                        if (i != j && strcmp(books[j].title, newTitle) == 0) {
                            isExists = 1;
                            printf("\nError: A book with this title already exists. Please enter a different title.\n");
                            break;
                        }
                    }
                }
            } while (isExists); 

            strcpy(books[i].title, newTitle);

            do {
                printf("Enter new Book Author: ");
                fgets(books[i].author, sizeof(books[i].author), stdin);
                books[i].author[strcspn(books[i].author, "\n")] = 0; 

                if (strlen(books[i].author) == 0) {
                    printf("\nError: Book Author cannot be empty.\n");
                }
            } while (strlen(books[i].author) == 0); 

            do {
                printf("Enter new Book Price: ");
                scanf("%d", &books[i].price);
                if (books[i].price < 0) {
                    printf("\nError: Price cannot be negative.\n");
                }
            } while (books[i].price < 0);

            printf("\nBook updated successfully!\n");
            printf("\nGo back(9)? or Exit(0)? : ");
            char choice;
            do {
                scanf(" %c", &choice);
                if (choice == '9'){ 
                clearScreen();  
                return; 
                }else if (choice == '0') {
                    printf("\n========= Thank you =========\n");
                    printf("======== See you soon =======\n");
                    exit(0); 
                }
            } while (1);
            return;
        }
    }
    printf("\nNo book found with ID %d.\n", id);
}

//Xoa sach
void deleteBook(struct Book books[], int* count) {
	clearScreen();
	printf("            ***Delete A book***\n");

	if (*count == 0) {
		printf("\nNo books available to delete.\n");
		printf("\nGo back(9)? or Exit(0)? : ");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9'){ 
			clearScreen();  
            displayMenu();
            return;
			}else if (choice == '0') {
				printf("\n========= Thank you =========\n");
				printf("======== See you soon =======\n");
				exit(0); 
			}
		} while (1);
		return;
	}
	int id;
	printf("\nEnter the ID of the book to delete: ");
	scanf("%d", &id);
	int i,j;
	int found = 0;
	for (i = 0; i < *count; i++) {
		if (books[i].id == id) {
			for (j = i; j < *count - 1; j++) {
				books[j] = books[j + 1]; 
			}
			(*count)--; 
			printf("\nBook with ID %d deleted successfully!\n", id);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("\nNo book found with ID %d.\n", id);
	}
	printf("\nGo back(9)? or Exit(0)? : ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9'){ 
		clearScreen();  
		return; 
		}else if (choice == '0') {
			printf("\n========= Thank you =========\n");
			printf("======== See you soon =======\n");
			exit(0);
		}
	} while (1);
}

//Sap xep sach theo gia
void sortBooksByPrice(struct Book books[], int count) {
	clearScreen();
	printf("            ***Sort Books by Price***\n");

	if (count == 0) {
		printf("\nNo books available to sort.\n");
		printf("\nGo back(9)? or Exit(0)? : ");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9') 
			return;
			else if (choice == '0') {
				printf("\n========= Thank you =========\n");
				printf("======== See you soon =======\n");
				exit(0); 
			}
		} while (1);
		return;
	}
    int order;
    printf("\nChoose sorting order:\n");
    printf("1. Increase Price\n");
    printf("2. Decrease Price\n");
    printf("Enter your choice: ");
    scanf("%d", &order);

    if (order != 1 && order != 2) {
        printf("Invalid choice. Returning to main menu.\n");
        return;
    }
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if ((order == 1 && books[j].price > books[j + 1].price) || 
                (order == 2 && books[j].price < books[j + 1].price)) {
                struct Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    printf("\nBooks sorted successfully.\n");
    printf("\nSorted Book List:\n");
    printf("|=======|======================|===========================|=================|\n");
    printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
    printf("|=======|======================|===========================|=================|\n");
    
    for (i = 0; i < count; i++) {
        printf("| %-5d | %-20s | %-25s | %-15d |\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].price);
        printf("|-------|----------------------|---------------------------|-----------------|\n");
    }
    printf("\nGo back(9)? or Exit(0)? : ");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9'){
			clearScreen();  
			return;
			}else if (choice == '0') {
				printf("\n========= Thank you =========\n");
				printf("======== See you soon =======\n");
				exit(0); 
			}
		} while (1);
		return;
	}

// Ham doc thong tin tai khoan tu file
void readAccountFromFile(char *username, char *password) {
    FILE *file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("Error opening account file.\n");
        exit(1);  
    }

    fgets(username, 20, file);  
    username[strcspn(username, "\n")] = 0;  

    fgets(password, 10, file); 
    password[strcspn(password, "\n")] = 0;  

    fclose(file);
}

// Ham xu ly mat khau 
void getPassword(char* password, int maxLen) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();  
        if (ch == 13) {  // Neu nhan Enter (13 la ky tu Enter)
            password[i] = '\0'; 
            break;
        } else if (ch == 8 && i > 0) {  // Neu nhan Backspace (8 la ky tu Backspace)
            i--;
            printf("\b \b");  
        } else if (i < maxLen - 1) {
            password[i] = ch;
            i++;
            printf("*");  
        }
    }
    printf("\n");
}

//Ham dang nhap
int login(const char* storedUsername, const char* storedPassword) {
	clearScreen();
    char username[20];
    char password[10];
    printf("          LOGIN:\n");
    printf("============================\n");
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;  

    printf("Enter Password: ");
    getPassword(password, 10);
    printf("============================\n");

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Login successful!\n");
    }
}

       



