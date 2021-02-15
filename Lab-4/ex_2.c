
#include <stdio.h>

int main(void)
{
    FILE *p1,*p2;
    char c;
    int count=0;
    


    p1 = fopen("input1.txt", "r");
    p2 = fopen("output.txt","w");

    if(!p1)
    {
        printf("The file can't be opened!!");
    }
    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if((c=='{') || (c=='}'))
            {
                fputc(c,p2);
                if(c=='{')
                {
                    count=count+1;
                }
                else if(c=='}')
                {
                   count=count-1;
                }

            }

        }
    }
    if(count==0)
    {
        printf("Balanced Curly Braces \n");
    }
    else
    {
        printf("Not Balanced Curly Braces \n");
    }
    fclose(p1);
    fclose(p2);

    p2=fopen("output.txt","r");
    while((c=fgetc(p2)) != EOF)
    {
        printf("%c",c);
    }
    fclose(p2);
    return 0;
}