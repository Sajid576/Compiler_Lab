#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


struct table
{
    char num[10];
    char identifiers[20];
    char idType[20];
    
};
struct table myTable[100];
int tableSize=0;

void readSymbolTable()
{
    FILE *p1;
    char word[10000];
     p1 = fopen("symbolTable.txt", "r");
    int ln=1;

    while(fscanf(p1, "%s", word)!=EOF)
    {
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(word, snum)==0)
        {
            ln++;
            strcpy(myTable[tableSize].num,word);
            fscanf(p1, "%s", word);
            strcpy(myTable[tableSize].identifiers,word);
            fscanf(p1, "%s", word);
            strcpy(myTable[tableSize].idType,word);
            
            tableSize++;
           
        }

        
    }

}

void readTokens()
{
     FILE *p1,*p2;
    char word[10000];
     p1 = fopen("tokens.txt", "r");
      p2 = fopen("output.txt", "w");
    int ln=1;

    while(fscanf(p1, "%s", word)!=EOF)
    {
        if(word)
    }
}

void display(){
    int org=1;
    printf("SI No.\t\tName\tIdType\n");
    int i;
    for (i=1;i<tableSize ; i++){
        
        printf("%8d   |",org);
        printf("%8s   |",myTable[i].identifiers);
       
        printf("%8s   |",myTable[i].idType);
        
        printf("\n");
        
        org++;
    }

}

int main(void)
{
        readSymbolTable();
        display();



}