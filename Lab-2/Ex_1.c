#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int main(void)
{
char keyword[32][100]={
   "switch","case","enum","register","typedef","char",
    "goto","sizeof","voltile","do","if","static","while"
      "auto","double","int","struct","break","else","long",
       "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
     
   } ;
   char str[]="double";
   int flag=0;
   int i;
  
   for( i = 0; i < 32; i++) {
      if(strcmp(str,keyword[i])==0) {
         flag=1;
      }
   }
   if(flag==1)
      printf("%s is a keyword",str);
   else
      printf("%s is not a keyword",str);


      
}















