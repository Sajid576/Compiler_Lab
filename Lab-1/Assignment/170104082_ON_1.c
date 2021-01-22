#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


int provideOneSpace=0;


void writeOutputFile(char c,FILE *p2)
{
         
        fputc(c, p2);

}
int checkSlash(FILE *p1)
{
    char check = fgetc(p1);

    //single line comment
    if(check == '/')
    {

        return 1;
    }
    //multi line comment
    else if(check == '*')
    {

        return 2;
    }
    // other character
    else
    {
        return 3;
    }
}
void removeMultiLineComment(FILE *p1)
{
    char c;
    while((c = fgetc(p1)) != EOF)
    {
        if(c == '*')
        {
            if((c = fgetc(p1)) == '/')
            {
                return;
            }
        }
    }
}
void removeSingleLineComment(FILE *p1)
{
    char c;
    while((c = fgetc(p1))!='\n')
    {
        continue;
    }
}
void removeExtraSpacesNewlines(FILE *p2)
{
    if(provideOneSpace == 0)
    {
        writeOutputFile(' ',p2);
        provideOneSpace = 1;
    }
}



void readInputFile()
{
        FILE *p1 = fopen("input.txt","r");
        char c;

        if(!p1 )
        {
            printf("File cannot be opened");
        }
        else
        {
            while((c = fgetc(p1)) != EOF)
            {
                printf("%c",c);
            }
        
        }
        fclose(p1);
}
void readOutputFile()
{
        FILE *p1 = fopen("output.txt","r");
        char c;

        if(!p1 )
        {
            printf("File cannot be opened");
        }
        else
        {
            while((c = fgetc(p1)) != EOF)
            {
                printf("%c",c);
            }
        
        }
        fclose(p1);
}

int main(void)
{
    FILE *p1, *p2;
    char c;

    p1 = fopen("input.txt","r");
    p2 = fopen("output.txt", "w");

    if(!p1 || !p2)
    {
        printf("File cannot be opened");
    }
    else
    {
        
        while((c = fgetc(p1)) != EOF)
        {

            //printf("%c",c);
            if(c != ' ' && c!='\n')
            {

                if(c == '/')
                {

                    int check = checkSlash(p1);
                    if(check == 1)
                    {
                        removeSingleLineComment(p1);
                    }
                    else if(check == 2)
                    {
                        removeMultiLineComment(p1);
                    }
                    else
                    {
                        provideOneSpace = 0;
                        writeOutputFile(c,p2);
                    }
                }
                else
                {
                    provideOneSpace = 0;
                    writeOutputFile(c,p2);
                }
            }
            else if(c == ' ' || c =='\n')
            {
                removeExtraSpacesNewlines(p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);
    readInputFile();
    readOutputFile();

   


}