#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Book {
    char *id;
    char *name;
    char *author;
    char *possession;
    char *checkedOutAt;
    char *dueDate;
} Book;

#define EMPTY_BOOK(X) Book X = { .id = "0", .name = "none", .author = "none", .possession = "none", .checkedOutAt = "none", .dueDate = "none" };

/**
*
* Opens library.csv (included with the repo) and parses each row
* into a Book struct. 
*
* @param booksCountArg - A pointer to an integer whose value will
* 						 be changed to the number of books in the 
* 						 array. This is mostly convenience so that 
*						 no extra work will be required to call
*						 saveBooks.
*
* @return Book* (pointer to array of books) 
*
**/
Book* getBooks(int *booksCountArg) {
    FILE *inputfile;
	inputfile = fopen("library.csv", "r");

    Book *allBooks = malloc(sizeof(Book));
    int bookIterator = 1;
	char buffer[256];
	
    while (fgets(buffer, 256, inputfile)) {
		int index = 0;
		char *token;
		EMPTY_BOOK(book);
		char *copy = strdup(buffer);
		
		while((token = strsep(&copy, ","))) {
			switch (index) {
			case 0:
				book.id = token;
				break;
			case 1:
				book.name = token;
				break;
			case 2:
				book.author = token;
				break;
			case 3:
				book.possession = token;
				break;
			case 4:
				book.checkedOutAt = token;
				break;
			case 5:
				book.dueDate = token;
				break;
			}

			index++;
		}
		
		allBooks = realloc(allBooks, sizeof(Book) * bookIterator);
		allBooks[bookIterator - 1] = book;
		bookIterator++;
    }
	
	fclose(inputfile);

	*booksCountArg = bookCount;
	return allBooks;
}


/**
*
* Overwrites library.csv and writes each book struct into its 
* own line. Intended to be used with getBooks where you call
* getBooks first, manipulate the array, and then call this method.
* 
* @param Book * - A pointer to the array of books, ideally gotten
* 				  from the getBooks function.
*
* @param booksArraySize - The size of the books array from the
*						  previous argument. The getBooks function
*						  provides a way to get this - any additions
*						  or subtractions to the array must be
*						  accounted for manually.
*
* @return void
*
**/
void saveBooks(Book *books, int booksArraySize) {
	FILE *inputfile;
	inputfile = fopen("library.csv", "w+");
	int i;
	for (i = 0; i < booksArraySize; i++){
		fprintf(inputfile, "%s,%s,%s,%s,%s,%s\n", 
			books[i].id,
			books[i].name,
			books[i].author,
			books[i].possession,
			books[i].checkedOutAt,
			books[i].dueDate);
	}

	fclose(inputfile);
}

void addBook() {
	printf("add a book");
}

void deleteBook() {
    printf("delete book");
}

void checkoutBook() {
    printf("checkout  book");
}

void returnBook() {
    printf("return book");
}

void viewBookStatus() {
    printf("view book status");
}

void viewBooksByAuthor() {
    printf("view books by author");
}

void viewCheckedOutBooksByUser() {
    printf("view checked out books by user");
}

void executeAction(char input) {
    switch(input) {
	case 'a':
	    addBook();
	    break;

	case 'd':
	    deleteBook();
	    break;

	case 'o':
	    checkoutBook();
	    break;

	case 'r':
	    returnBook();
	    break;

	case 's':
	    viewBookStatus();
	    break;

	case 'q':
	    viewBooksByAuthor();
	    break;

	case 'u':
	    viewCheckedOutBooksByUser();
	    break;
    }
}

int main(void) {
    printf("Welcome to the library!");
    char allowedCharacters[] = {'a','d','o','r','s','q','u'};
    char input;

    while(1) {
		printf("\n\nWhat would you like to do?\n");
		printf("(a) add a book \n(d) delete a book \n(o) check out a book\n(r) return a book\n(s) check the status of a book\n(q) view books written by an author\n(u) view books checked out by a given user.\n(x) quit\n\n");
		
		while ((input = getchar()) != '\n' && input != EOF) { 
			if (input == 'x') {
				goto end;
			}

			int i;
			for (i = 0; i < sizeof(allowedCharacters) / sizeof(allowedCharacters[0]); i++){
				if (allowedCharacters[i] == input) {
					executeAction(input);
					break;
				}
			}		
		}
    };
    
    end:
    printf("\n\nThanks for visiting the library!\n");
    return 0;
}

