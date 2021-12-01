#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int verification(char bracket, char code[]){
    int j, count;
    for (j=0, count=0; code[j]; j++)
        count += (code[j] == bracket);
    return count;
}

unsigned char tableau[30000] = {0};
unsigned char* pointer = tableau;

int bfinterpreter(char* bf) {
    //Initialisation
    char current_char;
    int i, loop;

    int open = verification('[', bf);
    int close = verification(']', bf);
    if (open > close) {
        printf("Missing %i right square bracket (']') or %i many left square bracket (']')", abs(open-close), abs(open-close));
        return 1;
    }else if (open > close) {
        printf("Missing %i left square bracket (']') or %i many right square bracket (']')", abs(open-close), abs(open-close));
        return 1;
    }

    //Interpreter
    for (i = 0; bf[i] != 0; i++) {
        current_char = bf[i];
        if (current_char == '>') {
            ++pointer;
        } else if (current_char == '<') {
            --pointer;
        } else if (current_char == '+') {
            ++*pointer;
        } else if (current_char == '-') {
            --*pointer;
        } else if (current_char == '.' ) {
            putchar(*pointer);
        } else if (current_char == ',') {
            *pointer = getchar();
        } else if (current_char == '[') {
            continue;
        } else if (current_char == ']' && *pointer) {
            loop = 1;
            while (loop > 0) {
                current_char = bf[--i];
                if (current_char == '[') {
                    loop--;
                } else if (current_char == ']') {
                    loop++;
                }
            }
        }
    }
    return 0;
}

void concatChar(char *strInit, char newChar)
{
    int i = 0;
     
    while(strInit[i] != '\0')
    {
       ++i;
    }
     
    strInit[i] = newChar;
    strInit[i+1] = '\0'; 
}


int main(int argc, char *argv[])
{
    FILE *fptr;
    char c;
    char ptf[100];
    
    if (argc != 2)
    {
        printf("Invalid number of argument, you only need to give the path of file to execute\n");
        return 1;
    }
    
    else
    {
        strcpy(ptf, argv[1]);
        printf("Result of %s : \n", ptf);
        
        fptr = fopen(ptf, "r");
        if (fptr == NULL)
        {
            printf("Cannot open file \"%s\" \n", ptf);
            return 1;
        }

        char str[100000] = "";

        printf("%s", str);
        
        c = fgetc(fptr);
        while (!feof(fptr))
        {
            concatChar(str, c);
            c = fgetc(fptr);
        }
        
        fclose(fptr);
        bfinterpreter(str);
    }
    return 0;
}