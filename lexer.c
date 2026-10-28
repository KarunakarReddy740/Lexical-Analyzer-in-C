#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
char reserved_keywords[35][20] = {"auto", "break", "case", "char", "const", "continue",
                                 "default", "do", "double", "else", "enum", "extern",
                                 "float", "for", "goto", "if", "int", "long", "register",
                                 "return", "short", "signed", "sizeof", "static", "struct",
                                 "switch", "typedef", "union", "unsigned", "void", "volatile",
                                 "while"};//array of strings to store the reserved keywords

struct operator
{
    char symbol[3];//array to store the operator symbol
    char name[50];//array to store the operator name
};
struct operator operators[40] =
{
    {"+","ARITHMETIC OPERATOR: PLUS"},
    {"-","ARITHMETIC OPERATOR: MINUS"},
    {"*","ARITHMETIC OPERATOR: MULTIPLY"},
    {"/","ARITHMETIC OPERATOR: DIVIDE"},
    {"%","ARITHMETIC OPERATOR: MODULUS"},
    {"++","ARITHMETIC OPERATOR: INCREMENT"},
    {"--","ARITHMETIC OPERATOR: DECREMENT"},
    {"==","RELATIONAL OPERATOR: EQUAL TO"},
    {"!=","RELATIONAL OPERATOR: NOT EQUAL TO"},
    {">","RELATIONAL OPERATOR: GREATER THAN"},
    {"<","RELATIONAL OPERATOR: LESS THAN"},
    {">=","RELATIONAL OPERATOR: GREATER THAN OR EQUAL TO"},
    {"<=","RELATIONAL OPERATOR: LESS THAN OR EQUAL TO"},
    {"&&","LOGICAL OPERATOR: AND"},
    {"||","LOGICAL OPERATOR: OR"},
    {"!","LOGICAL OPERATOR: NOT"},
    {"&","BITWISE OPERATOR: AND"},
    {"|","BITWISE OPERATOR: OR"},
    {"^","BITWISE OPERATOR: XOR"},
    {"~","BITWISE OPERATOR: NOT"},
    {"<<","BITWISE OPERATOR: LEFT SHIFT"},
    {">>","BITWISE OPERATOR: RIGHT SHIFT"},
    {"=","ASSIGNMENT OPERATOR: ASSIGN"},
    {"+=","ASSIGNMENT OPERATOR: ADD AND ASSIGN"},
    {"-=","ASSIGNMENT OPERATOR: SUBTRACT AND ASSIGN"},
    {"*=","ASSIGNMENT OPERATOR: MULTIPLY AND ASSIGN"},
    {"/=","ASSIGNMENT OPERATOR: DIVIDE AND ASSIGN"},
    {"%=","ASSIGNMENT OPERATOR: MODULUS AND ASSIGN"},
    {"&=","ASSIGNMENT OPERATOR: BITWISE AND AND ASSIGN"},
    {"|=","ASSIGNMENT OPERATOR: BITWISE OR AND ASSIGN"},
    {"^=","ASSIGNMENT OPERATOR: BITWISE XOR AND ASSIGN"},
    {"->","MEMBER ACCESS OPERATOR: POINTER TO STRUCTURE"},
    {".","MEMBER ACCESS OPERATOR: DOT"},
};
/*
    description : This function recognizes a character enclosed in single quotes and prints it. It also checks for invalid characters and handles errors accordingly.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/
void recognize_character(FILE *fptr, int ch)
{
    char character[100];//array to store the character
    int i = 0;
    int count = 0;

    if(ch == '\'')//checking if the char is a single quote
    {
        character[i] = ch;//storing the opening quote
        i++;

        ch = fgetc(fptr);//getting the first character

       while(ch != '\'' && ch != ';' && ch != '\n' && ch != EOF)
        {
            character[i] = ch;//storing characters inside single quotes
            i++;
            count++;//counting characters inside single quotes

            ch = fgetc(fptr);//getting next character
        }

        if(ch == '\'')//checking if closing quote is found
        {
            character[i] = ch;//storing the closing quote
            i++;

            character[i] = '\0';//null-terminating the character

            if(count == 1)//checking if exactly one character is present
            {
                printf("CHARACTER: %s\n", character);
            }
            else
            {
                printf("ERROR: INVALID CHARACTER: %s\n", character);//if count is more than 1, then invalid
            }
        }
        else
        {
            character[i] = '\0';//null-terminating the invalid character

            printf("ERROR: INVALID CHARACTER: %s\n", character);//if closing quote is missing, then invalid

            if(ch != EOF)//checking if character is not EOF
            {
                ungetc(ch, fptr);//putting the character back into the file stream
            }
        }
    }
}
/*
    description : This function recognizes keywords and identifiers in the input file. It reads characters from the file until it encounters a non-alphanumeric character or an underscore. It then checks if the recognized word is a reserved keyword or an identifier and prints the appropriate message.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/

void recognize_keyword_or_identifier(FILE *fptr, int ch)
{
    char word[100];//array to store the word
    int i = 0;
    int j;

    while(isalnum(ch) || ch == '_')//checking if the char is alphanumeric or underscore
    {
        word[i] = ch;//storing every char of identifier in the string
        i++;
        ch = fgetc(fptr);//reading the next char
    }

    word[i] = '\0';//Add null character to terminate the string
    ungetc(ch, fptr);//putting the character back into the file stream

    for(j = 0; j < 35; j++)//loop to check if word is a reserved keyword or not
    {
        if(strcmp(word, reserved_keywords[j]) == 0)//checking word with reserved keywords
        {
            printf("RESERVED KEYWORD: %s\n", word);//printing reserved keyword
            break;//breaking the loop if reserved keyword is found
        }
    }

    if(j == 35)
    {
        printf("IDENTIFIER: %s\n", word);//printing the identifier
    }
}
/*
    description : This function recognizes comments in the input file. It checks for single-line comments starting with '//' and multi-line comments enclosed between '/*' and '*\/'. It prints the recognized comment and handles errors accordingly.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/


int recognize_comment(FILE *fptr, int ch)
{
    if(ch == '/')//checking if the char is a slash
    {
        ch = fgetc(fptr);//getting the next char after slash

        if(ch == '/')//checking if the next char also a slash
        {
            printf("COMMENT: //");//printing the comment type

            ch = fgetc(fptr);//getting next char after slash

            while(ch != '\n' && ch != EOF)//checking if the char is not newline or EOF
            {
                printf("%c", ch);//printing char by char of the comment
                ch = fgetc(fptr);//getting next char everytime till newline or EOF
            }

            printf("\n");
            return 1;//returning 1 if comment is found
        }
        else if(ch == '*')//checking next cahr after / is *
        {
            printf("MULTI LINE COMMENT: /*");

            ch=fgetc(fptr);//getting next char

            while(ch != '*')
            {
                printf("%c",ch);// printing the char in multi line comment
                ch=fgetc(fptr);
            }

            ch=fgetc(fptr);//getting next char

            if(ch == '/')//checking next  cahr after * is / or not
            {
                printf("*/");//printing slash
                printf("\n");
            }

            return 1;//returning 1 if comment is found
        }
        else
        {
            ungetc(ch,fptr);//placing char back into file
            return 0;//returning 0 if comment is not found
        }
    }

    return 0;//if char is not slash
}

/*
    description : This function recognizes strings in the input file. It checks for strings enclosed in double quotes and prints the recognized string. It also handles invalid strings and escape sequences.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/

void recognize_string(FILE *fptr, int ch)
{
    char string[100];//array to store the string
    int i = 0;

    if(ch == '"')//checking if the char is a double quote
    {
        string[i] = ch;//storing the opening quote
        i++;

        ch = fgetc(fptr);//getting the first char after opening quote

        while(ch != '"' && ch != '\\' && ch != ')' && ch != ';' && ch != '\n' && ch != EOF)
        {
            string[i] = ch;//storing each character of the string
            i++;

            ch = fgetc(fptr);//getting next character
        }

        if(ch == '"')//checking if closing quote is found
        {
            string[i] = ch;//storing the closing quote
            i++;

            string[i] = '\0';//null-terminating the string

            printf("STRING: %s\n", string);//printing the string
        }
        else if(ch == '\\')//checking if escape sequence is found
        {
            string[i] = '"';
            string[i + 1] = '\0';

            printf("STRING: %s\n", string);//printing the string

            recognize_escape_sequence(fptr, ch);//recognizing escape sequence

            ch = fgetc(fptr);//getting the character after escape sequence

            if(ch == '"')//checking if closing quote is found
            {
                return;//returning after closing quote is found
            }
        }
        else
        {
            string[i] = '\0';//null-terminating the invalid string

            printf("ERROR: INVALID STRING: %s\n", string);//printing invalid string

            if(ch != EOF)//checking if character is not EOF
            {
                ungetc(ch, fptr);//putting the character back into the file stream
            }
        }
    }
}

/*
    description : This function recognizes numbers in the input file. It checks for integers and floating-point numbers, and prints the recognized number. It also handles invalid numbers and identifiers that start with a digit.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed

*/

void recognize_number(FILE *fptr, int ch)
{
    char number[100];//array to store the number
    int i = 0;
    int is_float = 0; // flag to check if the number is a float

    if(isdigit(ch)) // checking if char is digit
    {
        while(isdigit(ch) || (ch == '.' && is_float == 0))//checking if the char is digit or first decimal point
        {
            if(ch == '.')//checking if the char is a dot
            {
                is_float = 1;//setting the flag to 1 if the char is a dot
            }

            number[i] = ch;//storing every char of number in the string
            i++;

            ch = fgetc(fptr);//getting next char
        }

        number[i] = '\0';//Null-terminate the number string

        if(check_invalid_identifier(fptr, ch, number) == 1)//checking if letter or underscore comes after number
        {
            return;//returning if invalid variable name is found
        }

        if(check_invalid_number(fptr, ch,number,i) == 1)//checking if another decimal point comes after number
        {
            return;//returning if invalid number is found
        }

        if(ch != EOF)//checking if character is not EOF
        {
            ungetc(ch, fptr);//putting the character back into the file stream
        }

        if(is_float == 1)
        {
            printf("FLOAT: %s\n", number);//printing the float number
        }
        else
        {
            printf("INTEGER: %s\n", number);//printing the integer number
        }
    }
}
/*
    description : This function recognizes special symbols in the input file. It checks for various special symbols such as brackets, braces, semicolons, and commas, and prints the recognized symbol along with its name.
    parameters : int ch - the current character being processed
*/


void recognize_special_symbol(int ch)
{
    if(ch == '(')
    {
        printf("OPEN BRACKET: %c\n", ch);
    }
    else if(ch == ')')
    {
        printf("CLOSE BRACKET: %c\n", ch);
    }
    else if(ch == '{')
    {
        printf("OPEN FLOWER BRACKET: %c\n", ch);
    }
    else if(ch == '}')
    {
        printf("CLOSE FLOWER BRACKET: %c\n", ch);
    }
    else if(ch == '[')
    {
        printf("OPEN SQUARE BRACKET: %c\n",ch);
    }
    else if(ch == ']')
    {
        printf("CLOSED SQUARE BRACKET: %c\n",ch);
    }
    else if(ch == ';')
    {
        printf("SEMICOLON: %c\n",ch);
    }
    else if(ch == ',')
    {
        printf("COMMA: %c\n",ch);

    }

}

/*
    description : This function recognizes operators in the input file. It checks for various operators such as assignment, arithmetic, and logical operators, and prints the recognized operator along with its name.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/
void recognize_operator(FILE *fptr,int ch)
{
    int i;
    char operator[3];//array to store the operator symbol
    int found = 0;//flag to check if the operator is found or not

    operator[0] = ch;//storing the first char of operator in the string

    ch=fgetc(fptr);//getting the next char after the operator

    operator[1] = ch;//storing the second char of operator in the string
    operator[2] = '\0';//null terminating the string

    for(i=0;i<40;i++)//loop to check if the operator is a valid operator or not
    {
        if(strcmp(operator,operators[i].symbol)==0)//comparing the operator with the valid operators
        {
            printf("%s %s\n", operators[i].name, operator);
            found = 1;//setting the flag to 1 if the operator is found
            break;
        }
    }

    if(found==0)//checking if the operator is not found
    {
        ungetc(ch,fptr);//again putting the character back into the file stream

        operator[1]='\0';//null terminating the string

        for(i=0;i<40;i++)
        {
            if(strcmp(operator,operators[i].symbol)==0)//comparing the operator with the valid operators
            {
                printf("%s %s\n", operators[i].name,operator);
                break;
            }
        }
    }
}
/*
    description : This function recognizes preprocessor directives in the input file. It checks for lines starting with the '#' character and prints the recognized directive along with its content.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
*/

void recognize_preprocessor_directive(FILE *fptr,int ch)
{
    if(ch == '#')//checking if the char is a #
    {
        printf("PREPROCESSOR DIRECTIVE: %c", ch);
        ch=getc(fptr);//getting the next char after the #

        while(ch != '\n' && ch != EOF)//checking if the char is not newline or EOF
        {
            printf("%c",ch);//printing char by char of the preprocessor directive
            ch=getc(fptr);//getting next char everytime till newline or EOF
        }
        printf("\n");

    }
}

/*
    description : This function checks for invalid identifiers in the input file. It checks if a letter or underscore comes after a number, which is not allowed in C. If an invalid identifier is found, it prints an error message along with the invalid identifier.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
                 char number[100] - the string containing the number that was read before the invalid identifier
*/
int check_invalid_identifier(FILE *fptr, int ch, char number[100])
{
    if(isalpha(ch) || ch == '_')//checking if letter or underscore comes after number
    {
        printf("ERROR: INVALID VARIABLE NAME: %s%c", number, ch);//printing invalid variable name

        ch = fgetc(fptr);//getting next character

        while(isalnum(ch) || ch == '_')//checking remaining characters
        {
            printf("%c", ch);//printing remaining characters
            ch = fgetc(fptr);//getting next character
        }

        printf("\n");//printing new line

        if(ch != EOF)//checking if character is not EOF
        {
            ungetc(ch, fptr);//putting the character back into the file stream
        }

        return 1;//returning 1 if invalid identifier is found
    }

    return 0;//returning 0 if invalid identifier is not found
}

/*
    description : This function checks for invalid numbers in the input file. It checks if another decimal point comes after a number, which is not allowed in C. If an invalid number is found, it prints an error message along with the invalid number.
    parameters : FILE *fptr - pointer to the input file
                 int ch - the current character being processed
                 char number[100] - the string containing the number that was read before the invalid number
                 int i - the index of the last character in the number string
*/

int check_invalid_number(FILE *fptr, int ch, char number[100], int i)
{
    if(ch == '.')//checking if another decimal point comes after the number
    {
        number[i] = ch;//storing the extra decimal point
        i++;

        ch = fgetc(fptr);//getting next character

        while(isdigit(ch) || ch == '.')//checking remaining digits and decimal points
        {
            number[i] = ch;//storing remaining characters
            i++;

            ch = fgetc(fptr);//getting next character
        }

        number[i] = '\0';//Null-terminate the invalid number

        printf("ERROR: INVALID NUMBER: %s\n", number);//printing the complete invalid number

        if(ch != EOF)//checking if character is not EOF
        {
            ungetc(ch, fptr);//putting the character back into the file stream
        }

        return 1;//returning 1 if invalid number is found
    }

    return 0;//returning 0 if invalid number is not found
}

void recognize_escape_sequence(FILE *fptr, int ch)
{
    if(ch == '\\')//checking if backslash is found
    {
        ch = fgetc(fptr);//getting the character after backslash

        if(ch == 'n')//checking for new line escape sequence
        {
            printf("ESCAPE SEQUENCE: \\n\n");
        }
        else if(ch == 't')//checking for tab escape sequence
        {
            printf("ESCAPE SEQUENCE: \\t\n");
        }
        else if(ch == '\\')//checking for backslash escape sequence
        {
            printf("ESCAPE SEQUENCE: \\\\\n");
        }
    }
}

/*
    description : This function performs lexical analysis on the input file. It reads the file character by character and calls appropriate functions to recognize keywords, identifiers, numbers, strings, characters, comments, operators, special symbols, and preprocessor directives. It also handles invalid symbols and prints error messages accordingly.
    parameters : const char *filename - the name of the input file to be analyzed
*/


void lexical_analyzer(const char *filename)
{
    FILE *fptr;//file pointer

    fptr = fopen(filename, "r");//opening the file in read mode

    if(fptr == NULL)//checking if the file is opened successfully or not
    {
        printf("Error opening file!");
        return;
    }

    int ch;

    while((ch = fgetc(fptr)) != EOF)//reading the file char by char until end of file
    {
        if(isalpha(ch) || ch == '_')//checking if first char of identifier is alpha or underscore
        {
            recognize_keyword_or_identifier(fptr, ch);
        }

        if(ch == '"')//checking if the char is a double quote
        {
            recognize_string(fptr, ch);
        }

        if(isdigit(ch))
        {
            recognize_number(fptr, ch);
        }
        if(ch == '\'')//checking if the char is a single quote
        {
            recognize_character(fptr, ch);
        }
        if(ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == ';' || ch == ',')//checking if the char is a special symbol
        {
            recognize_special_symbol(ch);
        }
        if(ch == '/')//checking if the char is a slash
        {
        if(recognize_comment(fptr, ch) == 0)//checking if it is a comment
        {
        recognize_operator(fptr, ch);//recognizing slash as an operator
        }
        }

        if(ch == '+' || ch == '-' || ch == '*' || ch == '%' ||
           ch == '=' || ch == '!' || ch == '<' || ch == '>' ||
           ch == '&' || ch == '|' || ch == '^' || ch == '~')//checking if the char is an operator
        {
            recognize_operator(fptr, ch);
        }
        if(ch == '#')//checking if the char is a preprocessor directive
        {
            recognize_preprocessor_directive(fptr, ch);
        }
        if(!isspace(ch) && 
            !(isalpha(ch) || ch == '_') &&
            !isdigit(ch) &&
            ch != '#' && ch != '/' && ch != '"' && ch != '\'' &&
            ch != '(' && ch != ')' && ch != '{' && ch != '}' &&
            ch != '[' && ch != ']' && ch != ';' && ch != ',' &&
            ch != '+' && ch != '-' && ch != '*' && ch != '%' &&
            ch != '=' && ch != '!' && ch != '<' && ch != '>' &&
            ch != '&' && ch != '|' && ch != '^' && ch != '~')
        {
            printf("ERROR: INVALID SYMBOL: %c\n", ch);
        }
    }

    fclose(fptr);//closing the file
}