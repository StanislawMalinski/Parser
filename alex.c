#include "alex.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IGN 256             // maksymalna ilość funkcji do ignorowania
static int li = 0;
static char *keywords[MAX_IGN];

static int  ln = 1;
static char ident[256];
static FILE *ci = NULL;

void dod_key(char *word)
{
    if(li > MAX_IGN)
    {
	    fprintf(stderr,"Zbyt wiele funkcji do ignorowania!\n");
    }
    keywords[li] = strdup(word);
    li++;
}

void alex_init4file(FILE *in)
{
   ln = 1;
   ci = in;
}

int isKeyword(char *word)
{ 
    for (int i = 0; i < li; i++)
	    if(strcmp(word, keywords[i]) == 0)
	        return 1;
    return 0;
}

lexem_t alex_nextLexem(void)
{
  char c;
  while((c= fgetc(ci)) != EOF)
  {
    while(c  == '\n')
    {
        ln++;
	    c = fgetc(ci);
    }
    if(isspace(c))
        continue;
    else if(c == '(')
        return OPEPAR;
    else if(c == ')')
        return CLOPAR;
    else if(c == '{')
        return OPEBRA;
    else if(c == '}')
        return CLOBRA;
    else if(isalpha(c) || c == '_')
    {
        int i = 1;
        ident[0] = c;
        while(isalnum(c = fgetc(ci)) != 0 || c == '_')
            ident[i++] = c;
        ident[i] = '\0';
	    ungetc(c, ci);
        return isKeyword(ident) ? OTHER : IDENT;
    }
    else if(c == '"')
    {
        int cp = c;
        while((c= fgetc(ci)) != EOF && c != '"' && cp == '\\')
        {
       	    while((c = fgetc(ci)) == '\n')
        	    ln++;
	    }
	    ungetc(c,ci);
        return c == EOF ? EOFILE : OTHER;
    }
    else if(c == '/')                                   // obsługa komentarzy
    {
	    c = fgetc(ci);

	    if(c == '*')                                    // długi komentarz
        {
	        int znaleziono_komentarz = 0;
	        while(znaleziono_komentarz == 0)
            {
		        while((c = fgetc(ci)) != '*')
                {
		            if(c =='\n')
			            ln++;
		        }
		        c = fgetc(ci);
		        if(c == '/')
                {
		            znaleziono_komentarz = 1;
		        }
	        }
        }
        else if(c == '/')                               // krótki komentarz
        {
	        while(fgetc(ci) != '\n')
            {
		        ;
	        }
	        ln++;
	    }
	    continue;
    }
    else
    {
        return OTHER;
    }
  }       
  return EOFILE;
}

char * alex_ident(void)
{
    return ident;
}

int alex_getLN()
{
    return ln;
}

