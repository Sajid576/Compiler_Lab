#include<stdio.h>
#include<stdlib.h>
#include<string.h>




int main(void)
{
    char str[10000];
    char original[10000];
    FILE *p1,*p2;
    char c;
    p1=fopen("sample.txt","r");
    p2=fopen("sample.txt","r");
   

    if(!p1 || !p2)
    {
        printf("File can't be opened");
    }
    else
    {
        int i=0;
        int j=0;
         while((c=fgetc(p2))!=EOF)
         {
             original[j++]=c;
         }
         printf("original file is: \n");
         puts(original);

        int checkSpaceON=0;
        while((c=fgetc(p1))!=EOF)
        {
            
            //printf("%c",c);
            if(c=='\n'|| c=='\r' || c=='\t' || c==' ')
            {
                continue;
            }
            
            if(c=='/' )
            {
                
                c=fgetc(p1);
                if(c=='/')
                {
                    //single line comment detected...
                     while((c=fgetc(p1))!='\n')
                     {
                            continue;
                     }
                }
                else if(c=='*')
                {
                    //multi line comment detected...
                    while(1)
                    {
                        c=fgetc(p1);
                        if(c=='*')
                        {
                            c=fgetc(p1);
                            if(c=='/')
                            {
                                break;
                            }
                        }
                        else 
                        {
                            continue;
                        }
                         
                    }
                }
                

            }
            else 
            {

                str[i++]=c;
            }
           
            
        }
        printf("Compressed file is: \n");
        puts(str);
        
    }
}