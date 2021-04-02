#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int E(char seq[]);
int T(char seq[]);
int F(char seq[]);
int I(char seq[]);
int N(char seq[]);
/*
    (a/b)+(a*B)
*/
int containCheck(char seq[], char c){
    int i;
    for( i=0;i<strlen(seq);++i){
        
        if(seq[i]==c)
        {
            return 1;
        }
    }
    return 0;
}

/*
    startSeq="(a/b)"
    endSeq="(a*B)"
*/

int E(char seq[]){
    //printf("E got: %s\n",seq);
    if(containCheck(seq,'+')){
        char startSeq[500];
        char endSeq[500];
        int i=0;
        for(;i<strlen(seq);++i)
        {
            if(seq[i]=='+') break;
            startSeq[i]=seq[i];
        }
        startSeq[i]='\0';
        int j=0;
        for(++i;i<strlen(seq);++i)
        {
            endSeq[j++]=seq[i];
        }
        endSeq[j]='\0';
        //printf("From E-> S: %s\n",startSeq);
        //printf("From E-> E: %s\n",endSeq);
        return T(startSeq)&&T(endSeq);
    }
    else if(containCheck(seq,'-')){
        char startSeq[500];
        char endSeq[500];
        int i=0;
        for(;i<strlen(seq);++i){
            if(seq[i]=='-') break;
            startSeq[i]=seq[i];
        }
        startSeq[i]='\0';
        int j=0;
        for(++i;i<strlen(seq);++i){
            endSeq[j++]=seq[i];
        }
        endSeq[j]='\0';
        //printf("From E-> S: %s\n",startSeq);
        //printf("From E-> E: %s\n",endSeq);
        return T(startSeq)&&T(endSeq);

    }
    else return T(seq);
    return 0;
}

int T(char seq[]){
    //printf("T got: %s\n",seq);
    if(seq[0]=='('&&seq[strlen(seq)-1]==')'){
        return F(seq);
    }
    if(containCheck(seq,'*')){
        char startSeq[500];
        char endSeq[500];
        int i=0;
        for(;i<strlen(seq);++i){
            if(seq[i]=='*') break;
            startSeq[i]=seq[i];
        }
        startSeq[i]='\0';
        int j=0;
        for(++i;i<strlen(seq);++i){
            endSeq[j++]=seq[i];
        }
        endSeq[j]='\0';
        //printf("From T-> S: %s\n",startSeq);
        //printf("From T-> E: %s\n",endSeq);
        return F(startSeq)&&F(endSeq);
    }
    else if(containCheck(seq,'/')){
        char startSeq[500];
        char endSeq[500];
        int i=0;
        for(;i<strlen(seq);++i){
            if(seq[i]=='/') break;
            startSeq[i]=seq[i];
        }
        startSeq[i]='\0';
        int j=0;
        for(++i;i<strlen(seq);++i){
            endSeq[j++]=seq[i];
        }
        endSeq[j]='\0';
        //printf("From T-> S: %s\n",startSeq);
        //printf("From T-> E: %s\n",endSeq);
        return F(startSeq)&&F(endSeq);
    }
    else return F(seq);
    return 0;
}

int F(char seq[]){
    //printf("F got: %s\n",seq);
    if(seq[0]=='('&&seq[strlen(seq)-1]==')')
    {
        char newSeq[500];
        int i;
        for(i=0;i<strlen(seq)-2;++i){
            newSeq[i]=seq[i+1];
        }
        //printf("From F-> S: %s\n",newSeq);
        return E(newSeq);
    }
    return I(seq)||N(seq);
}

int I(char seq[]){
    //printf("I got: %s\n",seq);
    int i;
    for( i=0;i<strlen(seq);++i){
        if(seq[i]<'a'||seq[i]>'e') return 0;
    }
    return 1;
}

int N(char seq[]){
    //printf("N got: %s\n",seq);
    int i;
    for( i=0;i<strlen(seq);++i){
        if(seq[i]<'0'||seq[i]>'9') return 0;
    }
    return 1;
}

int main(){
    char input[10000];
    FILE *inputFile;
    FILE *outputFile;
    char c;
    int lineLength = 0;
    inputFile = fopen("input2.txt","r");
    outputFile = fopen("output2.txt","w");
    if(!inputFile){
        printf("\nFile can't be open.");
    }else{
        while((c = fgetc(inputFile))!=EOF){
            input[lineLength++] = c;

        }
    }
    printf("The string is: %s\n",input);
    input[lineLength]='\0';
    if(E(input)) {
        printf("The string is accepted.");
        fputs("The string is accepted.",outputFile);
    }
    else {
        printf("The string is not accepted.");
        fputs("The string is not accepted.",outputFile);
    }
}
