/* Name: Abu Syeed Sajid Ahmed ID:170104082 Lab Group:B2
Course No: CSE4130 Final Online Assessment, Spring 2020
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

char headerStorage[100][30];
int headerStorageSize=0;
void detectHeaderFiles()
{
    FILE *p1;
    
    p1=fopen("lexim.txt","r");
    
    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
        char str[100];
        //printf("\nHeader Files: ");
        while(fscanf(p1, "%s", str)!=EOF)
        {
             if(strstr(str, ".h")!=NULL)
             {
                strcpy( headerStorage[headerStorageSize++],str );
                // printf("%s ,", str);
             }

        }
    }
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
    char keyword[40][100]={
        "printf","scanf","switch","case","enum","register","typedef","char",
        "goto","sizeof","voltile","do","if","static","while"
        "auto","double","int","struct","break","else","long",
        "extern","return","union","const","float","short",
        "unsigned","continue","for","signed","void","default",
     
   };

    

    p1=fopen("lexim.txt","r");
     int ln=1;
    int cnt=0;

    if(!p1 )
    {
        printf("file cant be opened");
    }
    else
    {
        char str[100];
       
        while(fscanf(p1, "%s", str)!=EOF)
        {
            char snum[5];
            itoa(ln, snum, 10);
            if(strcmp(str, snum)==0)
            {
                ln++;
                cnt=0;
                
            }
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
                            printf("%s : Line No:%d\n",str,ln-1);
                        }
                        
                    }
                
                }

            }

        }

    }
}

int main()
{
    addLineNumberRemoveComment();
    separateLexim();
    detectHeaderFiles();
   
    detectFunctions();

}