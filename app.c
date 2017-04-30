#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
* This is a compact representation of the data
* that should be written and read into library.csv.
* Use this whenever you want to represent that data
* in the code.
**/
typedef struct Book {
    char *id;
    char *name;
    char *author;
    char *possession;
    char *checkedOutAt;
    int dueDate;
} Book;

/**
* Use this if you don't have all of the information
* to create a Book struct yet but want to build up
* the data structure. 
*
* USAGE:
* EMPTY_BOOK(book)
* book.name = "book name"; // the book variable now exists
**/
#define EMPTY_BOOK(X) Book X = { .id = "0", .name = "none", .author = "none", .possession = "none", .checkedOutAt = "none", .dueDate = 0 };

/**
*
* Opens library.csv (included with the repo) and parses each row
* into a Book struct. 
*
* @param booksCountArg int* - A pointer to an integer whose value will
* 			      be changed to the number of books in the 
* 		  	      array. This is mostly convenience so that 
*			      no extra work will be required to call
*			      saveBooks.
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
				book.dueDate = (int) strtol(token, NULL, 10);
				break;
		    }

		    index++;
		}
	
	allBooks = realloc(allBooks, sizeof(Book) * bookIterator);
	allBooks[bookIterator - 1] = book;
	bookIterator++;
    }

    fclose(inputfile);

    *booksCountArg = bookIterator;
    return allBooks;
}


/**
*
* Overwrites library.csv and writes each book struct into its 
* own line. Intended to be used with getBooks where you call
* getBooks first, manipulate the array, and then call this method.
* 
* Note that that this will release the books away from memory
*
* @param books Book* - A pointer to the array of books, ideally gotten
* 		       from the getBooks function.
*
* @param booksArraySize int - The size of the books array from the
*			      previous argument. The getBooks function
*			      provides a way to get this - any additions
*			      or subtractions to the array must be
*			      accounted for manually.
*
* @return void
*
**/
void saveBooks(Book *books, int booksArraySize) {
    FILE *inputfile;
    inputfile = fopen("library.csv", "w+");
    int i;
    for (i = 0; i < booksArraySize; i++){
	fprintf(inputfile, "%s,%s,%s,%s,%s,%d\n", 
	    books[i].id,
	    books[i].name,
	    books[i].author,
	    books[i].possession,
	    books[i].checkedOutAt,
	    books[i].dueDate);
    }

    fclose(inputfile);
    free(books);
}

/**
*
* Prompts the user for input and returns what they entered. 
* You can pass in whether a list of characters that the user
* is allowed to enter and will keep re-prompting them until
* they choose an option. 
*
* @param prompt char* - The string that should be printed to 
* 			the user before input is accepted.
* 
* @param allowedChars char* - A pointer to an array of characters.
* 			      If the user can enter anything, pass
* 			      in NULL.
*
* @param allowedCharSize int - The number of characters in allowedChars. 
* 			       This won't be used if allowedChars is NULL.
*
* @return char* - The character or string the user passed in.
*
**/
char* propmtUser(char *prompt, char *allowedChars, int allowedCharsSize) {
    while(1){
	if (allowedChars == NULL) {
	    printf("%s", prompt);
            char input[75];
            scanf("%s", input);
	    int i;
	    for(i = 0; i < strlen(input);i++){
		if (input[i] == '\n') {
		    input[i] = ' ';
		    break;
		}
	    }
	   
	    return strdup(input);
	} else {
	    char input[2] = {'\0','\0'};
	    printf("%s\n", prompt);
	    while ((input[0] = getchar()) != '\n' && input[0] != EOF) { 
		int i;
		for(i = 0; i < allowedCharsSize; i++) {
		    if (allowedChars[i] == input[0]) {
			input[1] = '\0';
			return strdup(input);
		    }
		}
	    }
	}
    }
}
//fieldIndex: pass an int to return the associated value. Check below or the struct for the associated value
//To return all of that index specified, pass "" (empty string) for query
//booksToSearch: Pass in a Book array to search. If searching all books, pass getBooks(&size) as param

//If no results are found, returns a single book with name "empty"
Book* search(int fieldIndex, char *query, Book *booksToSearch, int *booksArraySize_pntr) {
	Book *searchedBooks = malloc(sizeof(Book));
	int booksArraySize = *booksArraySize_pntr;
	int count = 0;
	for (int i=0; i<booksArraySize-1; i++){
		int addBook = 0;
		if (strcmp(query, "") == 0){
	    	addBook = 1;
	    }
	    switch(fieldIndex){
	    	case 0:
	    		if (strcmp(booksToSearch[i].id, query) == 0){
	    			addBook = 1;
	    		}
				break;
			case 1:
				if (strcmp(booksToSearch[i].name, query) == 0){
					printf("Adding %s\n", booksToSearch[i].name);
					addBook = 1;
				}
				break;
			case 2:
				if (strcmp(booksToSearch[i].author, query) == 0){
					addBook = 1;
				}
				break;
			case 3:
				if (strcmp(booksToSearch[i].possession, query) == 0){
					addBook = 1;
				}
				break;
			case 4:
				if (strcmp(booksToSearch[i].checkedOutAt, query) == 0){
					addBook = 1;
				}
				break;
			default:
				addBook = 0;
	    } 
	    if (addBook != 0){
	    	count++;
    		searchedBooks = realloc(searchedBooks, sizeof(Book) * count);
    		searchedBooks[count - 1] = booksToSearch[i];
    	}
	}
	if(count==0){
		EMPTY_BOOK(empty);
		empty.name = "empty";
		searchedBooks[0] = empty;
	} else {
		*booksArraySize_pntr = count;
	}
	return searchedBooks;
}


void addBook() {
    printf("add a book");
}

 void deleteBook() {
     int numOfbooks;
     Book *books = getBooks(&numOfbooks);
     while(1) {
        char *bookId = propmtUser("Please enter the book ID:\n", NULL, 0);
 	int *bookIndex;
        Book *searchResult = NULL; //search(0, bookId, books, *numOfbooks); // todo: integrate search
        if (searchResult != NULL) {
 	    books[*bookIndex] = books[numOfbooks - 1];
  	    books = realloc(books, sizeof(Book) * (numOfbooks - 1));
 	} else {
    	    printf("No such book!\n");
 	}
	
 	char allowedChars[] = {'t','b'};
 	char *response = propmtUser("(t) Try again\n(b) Back to main menu\n", allowedChars, 2);
 	if (response[0] == 't') {
 	    continue;
 	} else {
 	    break;
 	}
     }
 }

void checkoutBook() {
    printf("checkout a book");
}

 void returnBook() {
     int numOfBooks;
     Book *books = getBooks(&numOfBooks);
     while(1) {
 	char *bookId = propmtUser("Please enter the book ID:\n", NULL, 0);
 	Book *searchResult = NULL; // todo: integrate search
 	if (searchResult == NULL) {
	    int currentTimestamp = (int) time(NULL);
	    if (currentTimestamp >= searchResult->dueDate) {
		printf("Your fine is $9000000\n");
	    }
	    searchResult->possession = "Library";
	    printf("%s return successful!", searchResult->name);
	}

 	char allowedChars[] = {'t','b'};
 	char *response = propmtUser("(t) Try again\n(b) Back to main menu\n", allowedChars, 2);
 	if (response[0] == 't') {
 	    continue;
 	} else {
 	    break;
	}
     }
}

void viewBookStatus() {
    int size;
    Book *Books = search(1, propmtUser("View book status of (enter book name): ", NULL, 0), getBooks(&size), &size);
    if (strcmp(Books[0].name, "empty") != 0){
    	int count = 0;
    	for (int i=0; i<size-1; i++){
	    	if (strcmp(Books[i].possession, "Library") == 0){
	    		printf("%s, %s, STATUS: IN\n", Books[i].name, Books[i].author);
	    	} else {
	    		printf("%s, %s, STATUS: IN, POSSESSION: %s\n", Books[i].name, Books[i].author, Books[i].possession);
	    	}
    	}
    } else {
    	printf("No Results\n");
    }
}

void viewBooksByAuthor() {
    int size;
    Book *Books = search(2, propmtUser("View book by author (enter author name): ", NULL, 0), getBooks(&size), &size);
    if (strcmp(Books[0].name, "empty") != 0){
		int count = 0;
	    for (int i=0; i<size; i++){
	    	printf("%s, %s\n", Books[i].id, Books[i].name);
	    }
	} else {
		printf("No Results\n");
	}
	
}

Book* viewCheckedOutBooksByUser(const char *searchUser) {
    int size;
    Book *Books = search(3, propmtUser("View books checked out by user (enter username): ", NULL, 0), getBooks(&size), &size);
    if (strcmp(Books[0].name, "empty") != 0){
    	int count = 0;
    	for (int i=0; i<size-1; i++){
	    	printf("%s, %s\n", Books[i].name, Books[i].author);
    	}
    } else {
    	printf("No Results\n");
    }
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
	    viewBooksByAuthor("ask_user");
	    break;

	case 'u':
	    viewCheckedOutBooksByUser("ask_user");
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

