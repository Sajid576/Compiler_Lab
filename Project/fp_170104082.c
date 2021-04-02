/****************************************************************/
/* CSE 4130 : Spring 2020 Final Project ID:170104082 */
/****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char strLine[100];
char c;
FILE *p1,*p2,*p3;
int line_no=1;

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


void detectUnbalancedCurlyBraces()
{
    
    p3 = fopen("output.txt", "w");
    fputs("\n", p3);
    char str[10000];
    p1 = fopen("lexim.txt", "r");
    int paranthesisCnt=0,curlyBraceCnt=0, ln = 1;


    while(fscanf(p1, "%s", str)!=EOF)
    {
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(str, snum)==0)
            ln++;


        if(strcmp(str, "(")==0 )
        {
            paranthesisCnt++;
        }
        else if(strcmp(str, "{")==0)
        {
            curlyBraceCnt++;
        }
        else if (strcmp(str, ")")==0)
        {
            if(paranthesisCnt>0)
            {
                paranthesisCnt--;
            }
            else
            {
                printf("Imbalanced parathesis at line %d\n",ln-1);
               itoa(ln-1, strLine, 10);
               char temp[100];
               strcpy(temp,"Imbalanced parathesis at line ");
               strcat(temp,strLine);
               fputs(temp, p3);
               fputs("\n",p3);
            }
        }
        else if( strcmp(str, "}")==0)
        {
            if(curlyBraceCnt>0)
            {
                curlyBraceCnt--;
            }
            else
            {
                itoa(ln-1, strLine, 10);
                char temp[100];
                strcpy(temp,"Imbalanced curly braces at line ");
                strcat(temp,strLine);
                fputs(temp, p3);
                fputs("\n",p3);
                 printf("Imbalanced curly braces found at line %d\n",ln-1);
            }
        }


       
    }
    fclose(p1);
     fclose(p3);
}
void detectConsequentDuplicates()
{
     p3 = fopen("output.txt", "a");
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
           
            itoa(ln-1, strLine, 10);
            char er[100];
            strcpy(er,"Duplicate lexim found [ ");
            strcat(er,str1 );
            strcat(er,"] at line ");
            strcat(er,strLine );
            fputs(er, p3);
            fputs("\n",p3);
            printf("\nDuplicate lexim found [%s] at line %d", str1, ln-1);
        }


        strcpy(str1,str2);
    }
    fclose(p1);
     fclose(p3);
}

char headerStorage[100][30];
int headerStorageSize=0;

void detectHeaderFiles()
{
   
     p3 = fopen("output.txt", "a");
    p1=fopen("lexim.txt","r");
    
    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
        char str[100];
        printf("\nHeader Files: ");
        fputs("\nHeader Files: ",p3);
        
        while(fscanf(p1, "%s", str)!=EOF)
        {
             if(strstr(str, ".h")!=NULL)
             {
                strcpy( headerStorage[headerStorageSize++],str );
                 printf("%s ,", str);
                fputs(str, p3);
                fputs(",",p3);
             }

        }
    }
    fclose(p3);

}
// Used to detect if the passed string is a header or not
int isHeader(char *str){

    int i;
    int flag = 0;
    for(i=0;i<headerStorageSize;i++){
        if(strcmp(headerStorage[i],str)==0)
        {
            flag = 1;
            break;
        }
    }
    
    return flag;
}


void detectIdentifiers()
{
    char keyword[32][100]={
   "switch","case","enum","register","typedef","char",
    "goto","sizeof","voltile","do","if","static","while"
      "auto","double","int","struct","break","else","long",
       "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
     
   };

    
    p3 = fopen("output.txt", "a");
    p1=fopen("lexim.txt","r");
    
    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
        char str[100];
        printf("\nIdentifiers: ");
        fputs("\nIdentifiers: ",p3);
        while(fscanf(p1, "%s", str)!=EOF)
        {
            char ch=str[0];
            if(ch=='_' || (ch>='a' && ch<='z') )
            {
                int flag=0;
                int i;
                
                for( i = 0; i < 32; i++) {
                    if(strcmp(str,keyword[i])==0) {
                        //keyword
                        flag=1 ; 
                        break;
                    }
                }
                if(flag==0)
                {
                    
                    if(isHeader(str)==0)
                    {
                        //identifier
                        printf("%s ,",str);
                        fputs(str,p3);
                        fputs(",",p3);
                    }
                
                }

            }

        }

    }

    fclose(p3);
}

void detectKeywords()
{
    char keyword[32][100]={
   "switch","case","enum","register","typedef","char",
    "goto","sizeof","voltile","do","if","static","while"
      "auto","double","int","struct","break","else","long",
       "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
     
   };

    
    p3 = fopen("output.txt", "a");
    p1=fopen("lexim.txt","r");
    
    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
        char str[100];
        printf("\n Keywords: ");
        fputs("\n Keywords: ",p3);
        while(fscanf(p1, "%s", str)!=EOF)
        {
            char ch=str[0];
            if(ch=='_' || (ch>='a' || ch<='z') )
            {
                int flag=0;
                int i;
                
                for( i = 0; i < 32; i++) {
                    if(strcmp(str,keyword[i])==0) {
                        //keywords
                        flag=1 ; 
                    }
                }
                if(flag==1)
                {
                    printf("%s ,",str);
                   fputs(str, p3);
                   fputs(",",p3);
                }

            }

        }

    }
    fclose(p3);
}


char functionStorage[100][30];
int functionStorageSize=0;
// used to check if the detected function is already stored 
int checkDetectedFunc(char *str)
{
    int i;
    int ck=0;
    for(i=0;i<functionStorageSize;i++)
    {
        if(strcmp(str,functionStorage[i])==0)
        {//already stored
            ck=1;
            break;
        }
    }
    return ck;
}

void detectFunctions()
{
    char keyword[32][100]={
        "switch","case","enum","register","typedef","char",
        "goto","sizeof","voltile","do","if","static","while"
        "auto","double","int","struct","break","else","long",
        "extern","return","union","const","float","short",
        "unsigned","continue","for","signed","void","default",
     
   };

    
    p3 = fopen("output.txt", "a");
    p1=fopen("lexim.txt","r");
    
    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
       

        char str[100];
        printf("\nFunctions: ");
        fputs("\nFunctions: ",p3);
        while(fscanf(p1, "%s", str)!=EOF)
        {
            char ch=str[0];
            if(ch=='_' || (ch>='a' && ch<='z') )
            {
                int flag=0;
                int i;
            
                for( i = 0; i < 32; i++) {
                    if(strcmp(str,keyword[i])==0) {
                        //keyword
                        flag=1 ; 
                        break;
                    }
                }
                if(flag==0)
                {
                    
                    if(isHeader(str)==0)
                    {
                        //identifier
                        char next[30];
                        fscanf(p1, "%s", next);
                        if(strcmp(next,"(")==0 && checkDetectedFunc(str)==0)
                        {//function
                            strcpy(functionStorage[functionStorageSize++],str);
                            printf("%s ,",str);
                            fputs(str,p3);
                            fputs(",",p3);
                        }
                        
                    }
                
                }

            }

        }

    }

    fclose(p3);

}
int main()
{
        addLineNumberRemoveComment();
        separateLexim();
        detectUnbalancedCurlyBraces();
        detectConsequentDuplicates();
        detectHeaderFiles();
        detectKeywords();
        detectIdentifiers();
        detectFunctions();
       
}

