#include<stdio.h>
#include<stdlib.h>
#include<string.h>


FILE *p1, *p2,*p3;
char c;
int line_no=1;
struct table
{
    char num[10];
    char identifiers[20];
    char idType[20];
    char dtype[10];
    char scope[20]; 
};
struct table myTable[100];
int tableSize=0;

void addLineNumberRemoveComment()
{
        p1 = fopen("input.txt", "r");
        p2 = fopen("line_no_add.txt", "w");
        if(!p1)
        {
            printf("\nFile can't be opened!");
        }
        else
        {
        fprintf(p2, "%d ", line_no);
        while((c = fgetc(p1)) != EOF)
        {
            if(c == '\n')
            {
                fputc(c, p2);
                line_no = line_no + 1;
                fprintf(p2, "%d ", line_no);
                c = fgetc(p1);
                if(c=='\n')
                {
                    fputc(c, p2);
                    line_no = line_no + 1;
                    fprintf(p2, "%d ", line_no);
                    while((c = fgetc(p1)) == '\n')
                    {
                        fputc(c, p2);
                        line_no = line_no + 1;
                        fprintf(p2, "%d ", line_no);
                    }
                }
            }
            fputc(c, p2);
          }
        }
        fclose(p1);
        fclose(p2);
        p2 = fopen("line_no_add.txt", "r");
        p3 = fopen("Remove_comment.txt", "w");
        if(!p2)
        {
            printf("\nFile can't be opened!");
        }
        else
        {
            while((c = fgetc(p2)) != EOF)
            {
                if(c == '/')
                {      
                    c = fgetc(p2);
                    if(c == '/')
                    {
                        while (c != '\n')
                        {
                            c = fgetc(p2);
                        }
                    }
                    else if(c == '*'){
                    while(1)
                    {
                        if(((c = fgetc(p2))=='*'))
                        {
                            c = fgetc(p2);
                            if(c=='/')
                            {
                                break;
                            }
                        }
                    }
                    c = fgetc(p2);
                    }
                }
                fputc(c, p3);
        }
    }

        fclose(p2);
        fclose(p3);

}




void separateLexim()
{
    p1 = fopen("Remove_comment.txt", "r");
    p2 = fopen("lexim.txt", "w");

    int b = 0;

    while((c = fgetc(p1)) != EOF)
    {
        if (c == ' ')
            b=1;

        if(c==',' || c==';' || c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c=='`' || c=='\"' || c=='(' || c==')' || c=='{' || c=='}')
        {
            if(b == 0)
                fputc(' ', p2);
            fputc(c, p2);
            b=0;

            fputc(' ', p2);
            b=1;

            if((c = fgetc(p1)) != ' ')
            {
                fputc(c, p2);
                b=0;
            }
        }
        else if(c=='<' || c=='>' || c=='=' || c=='!')
        {
            if(b == 0)
                fputc(' ', p2);
            fputc(c, p2);

            char t = fgetc(p1);
            if(t == '=')
            {
                fputc(t, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                b=1;

                if(t==',' || t==';' || t=='+' || t=='-' || t=='*' || t=='/' || t=='%' || (int)t==39 || t=='\"' || t=='(' || t==')')
                {
                    fputc(t, p2);
                    fputc(' ', p2);

                    if((t = fgetc(p1)) != ' ')
                        fputc(t, p2);
                }
                else
                    fputc(t, p2);
            }
        }
        else
        {
            fputc(c, p2);
            if(c != ' ')
                b=0;
        }
    }
    fclose(p1);
    fclose(p2);
}

void unbalancedBracketsElse()
{
    
    char str[10000];
    p1 = fopen("lexim.txt", "r");
    int cntB = 0, cntE = 0, ln = 1;

    while(fscanf(p1, "%s", str)!=EOF)
    {
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(str, snum)==0)
            ln++;


        if(strcmp(str, "(")==0 ||  strcmp(str, "{")==0)
            cntB++;

        else if (strcmp(str, ")")==0 || strcmp(str, "}")==0)
            cntB--;

        if(strcmp(str, "if")==0)
            cntE++;

        else if (strcmp(str, "else")==0)
        {
            cntE--;
            if(cntE>-1)
                cntE = 0;
        }

        if(cntB<0)
        {
            printf("\nUnbalanced Bracket found in line %d", ln-1);
            cntB = 0;
        }

        if(cntE<0)
        {
            printf("\nUnbalanced Else found in line %d", ln-1);
            cntE = 0;
        }
    }
    if(cntB>0)
    {
        printf("\nUnbalanced Bracket found in line %d", ln-1);
        cntB = 0;
    }

    fclose(p1);
}


void consequentDupKey()
{
    char str1[10000];
    char str2[10000];
    p1 = fopen("lexim.txt", "r");
    fscanf(p1, "%s", str1);

    int ln = 1;

    while(fscanf(p1, "%s", str2)!=EOF)
    {
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(str1, snum)==0)
            ln++;

        if( (strcmp(str1, str2) == 0) && (strcmp(str1, "=")!=0 && strcmp(str1, "}")!=0 && strcmp(str1, ")")!=0 && strcmp(str1, "{")!=0 && strcmp(str1, "(")!=0) )
        {
            printf("\nDuplicate lexim found [%s] at line %d", str1, ln-1);
        }


        strcpy(str1,str2);
    }
    fclose(p1);
}

int checkKeyWords(char s[])
{
    if(strcmp(s, "char")==0 || strcmp(s, "double")==0 || strcmp(s, "void")==0 || strcmp(s, "return")==0 || strcmp(s, "int")==0 || strcmp(s, "float")==0 || strcmp(s, "string")==0 || strcmp(s, "if")==0 || strcmp(s, "else")==0)
    {
        int len = strlen(s), n=0;
        while(n<len)
        {
            fputc(s[n], p2);
            n++;
        }
        fputc(' ', p2);
        return 1;
    }
    else
        return 0;
}


int checkIdentifier(char s[])
{
    int len = strlen(s);
    int n = 1;
    int ret = 1;

    if( isalpha(s[0]) || s[0]=='_') {

    }
    else
        return 0;

    while(n<len)
    {
        if( isalpha(s[n]) || isdigit(s[n]) || s[n]=='_') {}
        else
            return 0;
        n++;
    }
   
}

void addIdentifier()
{
    char str[10000];
    p1 = fopen("lexim.txt", "r");
    p2 = fopen("final.txt", "w");
    int ln=1;

    while(fscanf(p1, "%s", str)!=EOF)
    {
        int i = atoi(str);
        if(i==ln)
        {
            if(i != 1)
                fputc('\n', p2);
            int len = strlen(str), n=0;
            while(n<len)
            {
                fputc(str[n], p2);
                n++;
            }
            fputc(' ', p2);
            ln++;
        }
        else if(checkKeyWords(str)) {}
        else if(checkIdentifier(str)) {}
        else
        {
            int len = strlen(str), n=0;
            while(n<len)
            {
                fputc(str[n], p2);
                n++;
            }
            fputc(' ', p2);
        }
    }
}

int checkDeclared(char identifier[],char currentScope[])
{
    int i;
    for( i=tableSize-1;i>=0;i--)
    {
        if(strcmp(identifier,myTable[i].identifiers )==0)
        {

           
            
            if(strcmp(currentScope,myTable[i].scope )==0)
            {
               
                //already declared
                return 1;
            }
            else if(strcmp("global",myTable[i].scope )==0)
            {
               
                //already declared globally
                return 1;
            }
            else
            {
                
                return 0;
            }
        }
        
    }
    return 0;
}

int checkTable(char identifier[],char currentScope[])
{
    int i;
    for( i=0;i<tableSize;i++)
    {
        if(strcmp(identifier,myTable[i].identifiers )==0)
        {
            if(strcmp(currentScope,myTable[i].scope )==0)
            {
                //already declared
                return 1;
            }
            else
            {
                return 0;
            }
        }
        
    }
    return 0;
}

void generateSymbolTable()
{
    char word[10000];
    p1 = fopen("lexim.txt", "r");
    int ln=1;
    
    char currentScope[20]="global";


    while(fscanf(p1, "%s", word)!=EOF)
    {
        
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(word, snum)==0)
        {
            ln++;
           
        }
        //check for data type
        if(strcmp(word, "char")==0 || strcmp(word, "double")==0 || strcmp(word, "float")==0 ||  strcmp(word, "int")==0  )
        {
                char str[20],temp_id[20];
                fscanf(p1, "%s", temp_id);
                if(checkTable(temp_id,currentScope)==0)
                {
                    fscanf(p1, "%s", str);
                    if(strcmp(str,"(")==0)
                    {
                        //func
                        strcpy(myTable[tableSize].idType,"func");
                        strcpy(myTable[tableSize].identifiers,temp_id);
                        strcpy(myTable[tableSize].dtype,word);
                        strcpy(myTable[tableSize].scope,"global");
                        strcpy(currentScope,temp_id);
                        tableSize++;
                    }
                    else
                    {
                        //var
                        strcpy(myTable[tableSize].idType,"var");
                        strcpy(myTable[tableSize].identifiers,temp_id);
                        strcpy(myTable[tableSize].dtype,word);
                        strcpy(myTable[tableSize].scope,currentScope);
                        tableSize++;

                    }
                }
                
            
        }
        else if(( isalpha(word[0]) || word[0]=='_' )&& strcmp(word, "void")!=0 && strcmp(word, "return")!=0 && strcmp(word, "struct")!=0 && strcmp(word, "typedef")!=0 && strcmp(word, "string")!=0 && strcmp(word, "if")!=0 && strcmp(word, "else")!=0 ){
        {
               char str[20];
               
                 if(checkDeclared(word,currentScope)==0)
                 {
                        fscanf(p1, "%s", str);
                        if(strcmp(str,"(")!=0)
                        {
                                printf("Undeclared varaible [%s]  at line %d\n",word,ln-1);
                        }
                        
                 }
                
            }
        }
           
    }
    

   

}
void display(){
    int org=1;
    printf("SI No.\t\tName\tDatatype\tIdType\tScope\n");
    int i;
    for (i=1;i<tableSize ; i++){
        
        printf("%8d   |",org);
        printf("%8s   |",myTable[i].identifiers);
        printf("%8s   |",myTable[i].dtype);
        printf("%8s   |",myTable[i].idType);
        printf("%8s   |",myTable[i].scope);
        printf("\n");
        
        org++;
    }

}

int main(void)
{
    addLineNumberRemoveComment();

    separateLexim();

    printf("Report:");
    

    unbalancedBracketsElse();

    consequentDupKey();
    printf("\n");

    addIdentifier();
    
    generateSymbolTable();
    display();
    
    return 0;
}
