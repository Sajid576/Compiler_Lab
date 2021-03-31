#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char reloperators[27][5]={
   "==",">","<","!=",">=","<=",
};
int reloperatorsNum=6;

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



void detectRelOperators()
{
    
    char str[10000];
    p1 = fopen("lexim.txt", "r");
    int ln=1;
    int cnt=0;

    while(fscanf(p1, "%s", str)!=EOF)
    {
        char snum[5];
        itoa(ln, snum, 10);
        if(strcmp(str, snum)==0)
        {
            ln++;
            cnt=0;
            
        }
            
        
        if(strcmp(str,"#include")==0)
        {
            
            while (1)
            {
                fscanf(p1, "%s", str);
                printf("%s",str);
                if(strcmp(str,">")==0)
                {

                    strcpy(str,"");
                    break;
                }
                
            }
            
        }
        if(strcmp(str,"printf")==0)
        {
            while (1)
            {
                fscanf(p1, "%s", str);
                
                if(strcmp(str,";")==0)
                {
                    //fscanf(p1, "%s", str);
                    break;
                }
                
            }
            
        }
        int flag=0;
        int i;
        for(i=0;i<reloperatorsNum;i++)
        {
            if(strcmp(str, reloperators[i])==0 )
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {//operators found
            printf("\nRelational operators found in line %d",ln-1);
            cnt++;
          
        }


    }
    fclose(p1);

}

int main()
{
    addLineNumberRemoveComment();
    separateLexim();
        detectRelOperators();
}