#ifndef _PARSER_H_IS_INCLUDED_
#define _PARSER_H_IS_INCLUDED_

void analizatorSkladni(char *inpname);

void store_add_def(char *funame, int line_nr, char *inpname);

void store_add_proto(char *funame, int line_nr, char *inpname);

void store_add_call(char *funame, int line_nr, char *inpname);

#endif
