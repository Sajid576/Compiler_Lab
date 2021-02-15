#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




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
            printf("%c", c);
                if(c=='c')
                {
                     c = fgetc(p1);
                     if (c >= 'a' && c <= 'z')
                     {
                           
                            c = fgetc(p1);
                           
                            if(c=='_')
                            {
                                c = fgetc(p1);
                                 char d;
                                 d=c;
                            if( c >= '0' && c <= '9' )
                             {
                                 c = fgetc(p1);
                                 if(d==c)
                                 {
                                     printf("String follows the pattern");
                                 }
                                 else 
                                 {
                                     printf("String doesnt follow the pattern");
                                      break;
                                 }

                             }
                             else 
                                 {
                                     printf("String doesnt follow the pattern");
                                      break;
                                 }
                            }
                             
                     }
                }
                else 
                    {
                                     printf("String doesnt follow the pattern");
                                     break;
                     }
        }

    }

}