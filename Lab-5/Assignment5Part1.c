#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
    A-> aXd
        abbXd
        abbbcXd
        abbbcd


ex:
   seq= ['A','b','c','b','b','d']
    newSeq=['b','c','b','b']
*/
int A(char seq[]){
    
    if(strlen(seq)%2!=0) return 0;
    
    if(seq[0]=='A'&&seq[strlen(seq)-1]=='d'){
        char newSeq[10000];
        int i=0;
        for(;i<strlen(seq)-2;++i){
            newSeq[i]=seq[i+1];
        }
        return X(newSeq);
    }
    else return 0;
}

int X(char seq[]){
    int i;
    for( i=0;i<strlen(seq);++i)
    {
        
        if(i %2 == 0 && seq[i]!='b')
        {
            return 0;
        }
        if( i%2 ==1 && !(seq[i]=='b'||seq[i]=='c'))
        {
            return 0;
        }
    }

    return 1;
}

int main(){
    char input[10000];
    FILE *inputFile;
    FILE *outputFile;
    char c;
    int lineLength = 0;
    inputFile = fopen("input1.txt","r");
    outputFile = fopen("output1.txt","w");
    if(!inputFile){
        printf("\nFile can't be open.");
    }else{
        while((c = fgetc(inputFile))!=EOF){
            input[lineLength++] = c;

        }
    }


    input[lineLength]='\0';
    printf("The string is: %s\n",input);
    if(A(input)) {
        printf("The string is accepted.");
        fputs("The string is accepted.",outputFile);
    }
    else {
        printf("The string is not accepted");
        fputs("The string is not accepted.",outputFile);
    }
}
