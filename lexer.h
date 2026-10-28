#include <stdio.h>

#ifndef LEXER_H

#define LEXER_H

void lexical_analyzer(const char *filename);
void recognize_keyword_or_identifier(FILE *fptr, int ch);
int recognize_comment(FILE *fptr, int ch);
void recognize_string(FILE *fptr, int ch);
void recognize_number(FILE *fptr, int ch);
void recognize_character(FILE *fptr, int ch);
void recognize_special_symbol(int ch);
void recognize_operator(FILE *fptr,int ch);
void recognize_preprocessor_directive(FILE *fptr,int ch);
int check_invalid_identifier(FILE *fptr, int ch, char number[100]);
int check_invalid_number(FILE *fptr, int ch,char number[100], int i);
void recognize_escape_sequence(FILE *fptr, int ch);

#endif