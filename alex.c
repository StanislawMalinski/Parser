#include "alex.h"

#include <string.h>
#include <ctype.h>

static int  ln= 1;
static char ident[256];
static FILE *ci= NULL;

void alex_init4file( FILE *in ) {
   ln= 1;
   ci= in;
}

int isKeyword(char *word){  //Przetestuj
    char *keywords[32] = {"auto", "double", "int", "struct","break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "continue", "for", "signed", "void", "do", "if", "static", "while", "default", "goto", "sizeof", "volatile", "const", "float", "short", "unsigned"};
    for (int i = 0; i < 32; i++){
	if(strcmp(word, keywords[i]) == 0)
		return 1;
    }
    return 0;
}

lexem_t alex_nextLexem( void ) {
  char c;
  while( (c= fgetc(ci)) != EOF ) {
    while( c  == '\n' ){
        ln++;
	c = fgetc(ci);
    }
     if( isspace( c ) )
        continue;
    else if( c == '(' )
        return OPEPAR;
    else if( c == ')' )
        return CLOPAR;
    else if( c == '{' )
        return OPEBRA;
    else if( c == '}' )
        return CLOBRA;
    else if( isalpha( c ) ) {
        int i= 1;
        ident[0] = c;
        while( isalnum( c = fgetc(ci) ) != 0 )
            ident[i++] = c;
        ident[i] = '\0';
	ungetc(c, ci);
	printf("%s\n", ident);
        return isKeyword(ident) ? OTHER : IDENT;
    }else if( c == '"' ) {
      /* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
         i \\ w napisie 
      */
        int cp = c;
        while( (c= fgetc(ci)) != EOF && c != '"' && cp == '\\' ) {
            cp = c;
       	    if( c == '\n' )
        	ln++;
	    }
        return c==EOF ? EOFILE : OTHER; 
    }else if( c == '/' ) { 						// obsułga komentarzy
	c = fgetc(ci);

	if (c == '*'){    						// długi komentarz
	    int znaleziono_komentarz = 0;
	    while(znaleziono_komentarz == 0){
		while ((c = fgetc(ci)) != '*'){
		    if(c =='\n')
			ln++;
		}
		c = fgetc(ci);
		if(c == '/'){
		    znaleziono_komentarz = 1;
		}else if ( c == '*'){
		    ;
		}
	    }
	} else if (c == '/'){ 						// komentarz kończy się w tej linije
	    while(fgetc(ci) != '\n'){
		;
	    }
	    ln++;
	}
	continue;
    } if( isdigit( c ) || c == '.' ) {
      		/* liczba */
    } else {
        return OTHER;
    }
  }       
  return EOFILE;
}

char *  alex_ident( void ) {
   return ident;
}

int     alex_getLN() {
        return ln;
}

