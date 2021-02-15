#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int cnt=0;

char validConsKeywords[30][100]={
    "else if","typedef struct"
};
char keyword[32][100]={
   "switch","case","enum","register","typedef","char",
    "goto","sizeof","voltile","do","if","static","while"
      "auto","double","int","struct","break","else","long",
       "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
     
   } ;

int main()
{
    FILE *p1;
    char word[50];
    p1 = fopen("input1.txt", "r");
   
    int i;
    int count=0;
    if (p1 == NULL)
    {
      printf("Can't open %s for reading.\n", p1);
    }
    else
    {
        while (fscanf(p1, "%s", word) != EOF)
        {
            int flag=0;
            int i;
  
            for( i = 0; i < 32; i++) {
                if(strcmp(word,keyword[i])==0) {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {//keyword
                    char text[100];
                    strcpy(text,word); 
                    
                    fscanf(p1, "%s", word);
                    flag=0;
                    for( i = 0; i < 32; i++) {
                        if(strcmp(word,keyword[i])==0) {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==1)
                    {//keyword
                        flag=0;
                        strcat(text," ");
                        strcat(text,word);
                        for( i = 0; i < 2; i++) {
                        if(strcmp(text,validConsKeywords[i])==0) {
                            flag=1;
                            break;
                            }
                        }
                        if(flag==0) {
                            //subsequent keyword error count
                            cnt++;
                        }


                    }


            }
            

         }
        printf("Subsequent keyword Count: %d",cnt);


    }
       
}
    

