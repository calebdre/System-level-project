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
    int checkedOutAt;
    int dueDate;
} Book;

/**
* Define boolean type
**/
typedef int bool;
#define true 1
#define false 0


/**
* Use this if you don't have all of the information
* to create a Book struct yet but want to build up
* the data structure. 
*
* USAGE:
* EMPTY_BOOK(book)
* book.name = "book name"; // the book variable now exists
**/
#define EMPTY_BOOK(X) Book X = { .id = "0", .name = "none", .author = "none", .possession = "none", .checkedOutAt = 0, .dueDate = 0 };

int calculateDueDate() {
    return ((int) time(NULL)) + (604800 * 2); // 604800 = number of seconds in a week
}

char* convertToString(int timestamp) {
   char time[11];
   char charStamp[20];

   sprintf(charStamp, "%d", timestamp);
   time_t t = (time_t) atoi(charStamp);
   struct tm *p = localtime(&t);

  strftime(time, sizeof(time) -1, "%m/%d/%Y", p);
  return strdup(time);
}

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
				book.checkedOutAt = (int) strtol(token, NULL, 10);
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
    for (i = 0; i < (booksArraySize-1); i++){
		if (books[i].id == NULL) continue;
	    fprintf(inputfile, "%s,%s,%s,%s,%d,%d\n", 
	    books[i].id,
	    books[i].name,
	    books[i].author,
	    books[i].possession,
	    books[i].checkedOutAt,
	    books[i].dueDate);
    }

    fclose(inputfile);
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
	   
	    char *copy = malloc(strlen(input) + 1);
	    strcpy(copy, input);
	    return copy;
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
Book* search(int fieldIndex, char *query, Book *booksToSearch, int *booksArraySize_pntr, int *foundIndex) {
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
			default:
				addBook = 0;
	    } 
	    if (addBook != 0){
	    	count++;
    		searchedBooks = realloc(searchedBooks, sizeof(Book) * count);
    		searchedBooks[count - 1] = booksToSearch[i];
		if (foundIndex != NULL) {
		    *foundIndex = i;
		}
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
    char title[30];
    char author[30];
    char id[10];

    int numOfBooks;
    Book *books = getBooks(&numOfBooks);
    int willContinue = 1;

    while (willContinue) {
	    int latestId = (int) strtol(books[numOfBooks -2].id, NULL, 10);
	    int newBookId = latestId + 1;
	    sprintf(id, "%d", newBookId);

	    int c;
	    while ( (c = getchar()) != EOF && c != '\n') { }

	    printf("\nWhat is the title of the book?\n");
	    fgets(title, 30, stdin);
	    int i;
	    for (i = 0; i <30;i++){
		if (title[i] == '\n') title[i] = '\0';
	    }

	    printf("\nWho is the author of %s?\n", title);
	    fgets(author, 30, stdin);
	    
	    for (i = 0; i <30;i++){
		if (author[i] == '\n') author[i] = '\0';
	    }

	    Book newBook = {.id = id, .name = title, .author = author, .possession = "Library", .checkedOutAt = 0, .dueDate = 0 };

	    books = realloc(books, sizeof(Book) * (numOfBooks + 1));
	    books[numOfBooks - 1] = newBook;
	    numOfBooks += 1;

	    saveBooks(books, numOfBooks);
	    printf("\n%s was added successfully!\n\n", title);

	    char response;
	    printf("(t) Try again\n(b) Back to main menu\n");
	    scanf("%c", &response);
	    if (response == 'b'){
		willContinue = 0;
	    }
    }
}

void removeBookFromArray(Book *books, int index, int arrSize) {
    int i;
    for (i = index; i < arrSize - 1; i++) {	    
	books[i] = books[i + 1];
    }
    books = realloc(books, (arrSize - 1) * sizeof(Book));
}

void deleteBook() {
     int numOfbooks;
     Book *books = getBooks(&numOfbooks);
     int willContinue = 1;
     while(willContinue) {
        char *bookId = propmtUser("Please enter the book ID:\n", NULL, 0);
	int searchedItems = numOfbooks;
	int bookIndex; 
        Book *searchResult = search(0, bookId, books, &searchedItems, &bookIndex);

        if (searchResult != NULL && strcmp(searchResult->name, "empty") != 0) {
	    removeBookFromArray(books, bookIndex, numOfbooks);
	    numOfbooks -= 1;
	    saveBooks(books, numOfbooks);
	    printf("\n%s was deleted!\n\n", searchResult->name);
 	} else {
    	    printf("\nNo such book!\n\n");
 	}

	char response;
	printf("(t) Try again\n(b) Back to main menu\n");
	scanf("%c", &response);
	scanf("%c", &response);
	if (response == 'b') {
            willContinue = 0;
	}
     }
 }

void checkoutBook() {
	int numofchekout = 0;
	int *numOfBooks = malloc(sizeof(int));
	Book *allBooks = getBooks(numOfBooks);
	bool tryAgain = true;

	do{
		bool found = false;
		char *userName = propmtUser("Enter the user name:\n", NULL, 0);

		for (int i = 0; i < *numOfBooks - 1; i++) {
			if (strcmp(allBooks[i].possession, userName) == 0) {
				numofchekout++;
			}
		}

		if (numofchekout < 3) {
			char *bookId = propmtUser("Please enter the book ID:\n", NULL, 0);
			for (int i = 0; i < *numOfBooks - 1; i++) {
				if (strcmp(allBooks[i].id, bookId) == 0) {
					if(strcmp(allBooks[i].possession, "Library") != 0) {
					    printf("\nThat book is already checked out - please try again on %s\n\n", convertToString(allBooks[i].dueDate));
					    found = true;
					    break;
					}
					allBooks[i].possession = userName;
					allBooks[i].checkedOutAt = (int) time(NULL);

					int dueDate = calculateDueDate();
					printf("\nYour due date is: %s\n", convertToString(dueDate));
					allBooks[i].dueDate = dueDate;
					printf("Book checked out successfully!\n\n");
					break;
				}
			}

			if (found == false)	{
				printf("No such book!\n");
			}else {
				saveBooks(allBooks, *numOfBooks);
			}
		}
		
		char response;
		printf("(t) Try again\n(b) Back to main menu\n");
		scanf("%s", &response);
		if (response != 't') {
			tryAgain = false;
		}
		
	} while (tryAgain == true);
}

 void returnBook() {
     int willContinue = 1;
     int numOfBooks;
     Book *books = getBooks(&numOfBooks);
     while(willContinue) {
 	char *bookId = propmtUser("Please enter the book ID:\n", NULL, 0);
	int searchedItems = numOfBooks;
 	int bookIndex;
	Book *searchResult = search(0, bookId, books, &searchedItems, &bookIndex);
	
 	if (searchResult != NULL && strcmp(searchResult->name, "empty") != 0) {
	    if (strcmp(searchResult->possession, "Library") == 0) {
		printf("\nThis book has not been lent out.\n\n");
	    } else {
		int currentTimestamp = (int) time(NULL);
	        if (currentTimestamp >= searchResult->dueDate) {
	   	   printf("\nThis book is late. Your fine is $9000000!");
	        }

	        searchResult->possession = "Library";
	        printf("\nThanks for your payment. %s return successful!\n\n", searchResult->name);
		books[bookIndex] = *searchResult;
		saveBooks(books, numOfBooks);
	    }
	 } else {
            printf("\nNo such book!\n\n");
	 }
 	char allowedChars[] = {'t','b'};
	char response;
 	printf("(t) Try again\n(b) Back to main menu\n");
	scanf("%c", &response);
	scanf("%c", &response);
	if (response == 'b') {
	    willContinue = 0;
	}
    }
}

void viewBookStatus() {
    int size;
    Book *Books = search(1, propmtUser("View book status of (enter book name): ", NULL, 0), getBooks(&size), &size, NULL);
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
    Book *Books = search(2, propmtUser("View book by author (enter author name): ", NULL, 0), getBooks(&size), &size, NULL);
    if (strcmp(Books[0].name, "empty") != 0){
		int count = 0;
	    for (int i=0; i<size; i++){
	    	printf("%s, %s\n", Books[i].id, Books[i].name);
	    }
	} else {
		printf("No Results\n");
	}
	
}

void viewCheckedOutBooksByUser() {
    int size;
    Book *Books = search(3, propmtUser("View books checked out by user (enter username): ", NULL, 0), getBooks(&size), &size, NULL);
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

