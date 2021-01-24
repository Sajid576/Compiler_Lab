#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char keyword[32][100]={
   "switch","case","enum","register","typedef","char",
    "goto","sizeof","voltile","do","if","static","while"
      "auto","double","int","struct","break","else","long",
       "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
     
   } ;
char separators[2][2]={
    ";",","
};
char paranthesis[6][2]={
    "(",")","{","}","[","]"
};
char operators[27][5]={
    "+","-","*","/","%","++","--","+=","-=","=","*=","/=","%=","==",">","<","!=",
    ">=","<=","&&","||","!","&","|","^","<<",">>",
};



void showLables(char *lexeme,int categoryNo)
{
    printf("[");
    if(categoryNo==1)
    {
        printf("%s",lexeme);
    }
    else if(categoryNo==2)
    {
        printf("id %s",lexeme);
    }
    else if(categoryNo==3)
    {
        printf("%s",lexeme);
    }
    else if(categoryNo==4)
    {
        printf("%s",lexeme);
    }
    else if(categoryNo==5)
    {
        printf("%s",lexeme);
    }
    else if(categoryNo==6)
    {
        printf("%s",lexeme);
    }
    else if(categoryNo==7)
    {
        printf("%s",lexeme);
    }


    printf("]");
}

int main(void)
{
    FILE *p1;
    char c;
    
    p1 = fopen("input.txt","r");
    
    if(!p1)
    {
        printf("File cannot be opened");
    }
    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if(c=='+'||c=='-'|| c=='*'|| c=='/'|| c=='%'||c=='='|| c=='>'|| c=='<'|| c=='!'|| c=='|' || c=='&')
            {
                char str[3];
                str[0] = c;
                c = fgetc(p1);
                if(c=='+'||c=='-'|| c=='*'|| c=='/'|| c=='%'||c=='='|| c=='>'|| c=='<'|| c=='!'|| c=='|' || c=='&')
                {
                    str[1] = c;
                    str[2] = '\0';
                    showLables(str,3);
                }
                else
                {
                    str[1] = '\0';
                    showLables(str,3);
                }
        
            }
            //printf("%c", c);
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
            {
                char str[50];


                str[0] = c;
                int i=1;
                while(1) 
                {
                    c = fgetc(p1);
                    if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'))
                    {
                        str[i++] = c;
                    }
                    else break;
                    
                }
                str[i] = '\0';
                int flag =0;
                //check for keyword
                for( i = 0; i < 32; i++) {
                    if(strcmp(str,keyword[i])==0) {
                        flag=1;
                    }
                }
                if(flag==1)
                {
                    showLables(str,1);
                }
                else
                {
                    showLables(str,2);
                }
                

            }
            if( c >= '0' && c <= '9' )
            {
                
                char str[50];
                str[0] = c;
                int i=1;
                int flag = 0;
                while(1) 
                {
                    c = fgetc(p1);
                    if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')  || c == '_'))
                    {
                        str[i++] = c;
                        flag=1;
                    }
                    else if ((c >= '0' && c <= '9') || c == '.')
                    {
                        str[i++] = c;
                    }
                    else break;
                    
                }
                str[i] = '\0';
                if(flag==1)
                {//error
                     showLables(str,7);
                }
                else
                {//number
                     showLables(str,6);
                }
            }

            
            if(c=='('|| c==')'|| c=='{'|| c=='}'|| c=='['|| c==']')
            {
                char str[3];
                str[0] = c;
                str[1] = '\0';
                showLables(str,5);
            }
            if (c == ';'|| c==',')
            {
                char str[3];

                
                str[0] = c;
                str[1] = '\0';
                showLables(str,4);
            }
            

        }
    }
}