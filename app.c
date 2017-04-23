#include <stdio.h>

/****
 * 
 * function for basic file handing. Everyone should use this if they need to access the file
 *
 ****/









/****
 *
 * function(s) that search file for row or rows
 *
****/








/****
 *
 * function(s) to make additional rows or delete rows
 *
****/







/****
 *
 * function(s) to edit rows
 *
 ****/ 


void executeAction(char input) {
    switch(input) {
	case 'a':
	    printf("add book");
	    break;

	case 'd':
	    printf("delete book");
	    break;

	case 'o':
	    printf("check out a  book");
	    break;

	case 'r':
	    printf("return book");
	    break;

	case 's':
	    printf("status of book");
	    break;

	case 'q':
	    printf("books from author");
	    break;

	case 'u':
	    printf("view books from user");
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
		break;
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

    printf("\n\nThanks for visiting the library!\n");
    return 0;
}
