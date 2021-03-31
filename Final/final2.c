/* Name: Abu Syeed Sajid Ahmed ID:170104082 Lab Group:B2
    Course No: CSE4130 Final Online Assessment, Spring 2020
*/

#include<stdio.h>

char str[10];
int i=0;
int l=0;
int f=0;

/*
    E-> aA | bAB
    A-> b | bA
    B-> a | epsilon
*/
void B(){
//string b
    if(str[i]=='a') f=1;
    if(i<l) f=1;
}



void A(){
//string b bbb
    if(str[i]=='b'){
        i++;
        f=1;
        if(i<l){
            A();
        }
        else{
            return;
        }
    }

}

void E(){
    //string ab abb bb
    if(str[i]=='a'){
        i++;
        A();

    }
    else if(str[i]=='b'){
        i++;
        A();
        if(f && i<l){
            i++;
            B();
        }
        else {
            return;
        }

    }
    else {
        f=0;
        return;
    }


}

int main(){

    printf("\nEnter a string to parse: ");
    scanf("%s",&str);


    l=strlen(str);
    //printf("%d",l);

    if(l>=2)
    {
        E();
        if(f==0){
             printf("Invalid String");
         }
        else if(i==l){
                if(f==1)printf("Valid String");
        }
        else{
            printf("Invalid String");
        }
    }
    else{
        printf("Invalid string");
    }





}
