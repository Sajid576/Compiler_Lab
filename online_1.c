#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

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
        int count =0;
        while((c = fgetc(p1)) != EOF)
        {
            if(c=='%')
            {
                c = fgetc(p1);
                if(c=='d')
                {
                    count++;
                }else
                {
                    while((c = fgetc(p1))!= '%')
                    {};
                }
            }
        }
       
       printf("%d",count);
    }

}