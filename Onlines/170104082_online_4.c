#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int curlyCnt=0;
int paranthesisCnt=0;



int main(void)
{

    FILE *p1;
    char c;
    p1 = fopen("input.txt", "r");

    int ln=1;

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if(c =='(')
            {
                paranthesisCnt++;
            }
            if(c =='{')
            {   
                curlyCnt++;
            }
            if(c ==')')
            {
                paranthesisCnt--;
            }
            if(c =='}')
            {
                curlyCnt--;
            }
            if(c =='\n')
            {
                if(curlyCnt!=0 )
                {
                    printf("\nUnbalanced curly braces found in line %d",ln);
                }
                if(paranthesisCnt!=0)
                {
                     printf("\nUnbalanced paranthesis found in line %d",ln);
                }
                ln++;
                curlyCnt=0;
                paranthesisCnt=0;
            }



        }



    }


}