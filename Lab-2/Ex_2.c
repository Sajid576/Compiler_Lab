#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool isValid(char *str, int n) 
{     
    int i;
        
    if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_')) 
        return false; 
  
    
    for ( i = 1; i < strlen(str); i++)
    {
        if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_')) 
            return false; 
    } 

    return true; 
} 

int main(void)
{
    char str[] = "lol"; 
    int n = strlen(str); 
  
    if (isValid(str, n)) 
        printf( "Valid"); 
    else
       printf( "Invalid"); 

}