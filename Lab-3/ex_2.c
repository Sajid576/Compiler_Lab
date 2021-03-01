#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdbool.h>



struct keyVal {
    char name[100];
    char val[100];
    int visited;
    
};
struct keyVal NameVal[10];
int nv = 0;



struct node{
    char name[100], type[100], dtype[100], scope[100], value[100];
    int del;
};
struct node store[100];

char scope1[100];
char str[10000];
char all[100][100];
int allrow = 1, rowNum = 1;
int cnt=0;
void identifierSep(){
    FILE *p1, *p2;
    p1=fopen("input.txt","r");
    p2=fopen("output.txt","w");

    char ch;
    
    while((ch=fgetc(p1)) !=EOF){
        if(ch=='['){
            fputc(ch, p2);
            str[cnt++]=ch;
            char tmp[100];
            int indx = 0;
            while((ch=fgetc(p1))!=EOF){
                if(ch==' '){
                    tmp[indx] = '\0';
                    if(strcmp(tmp,"id")==0){
                        fputc('i', p2);
                        fputc('d', p2);
                        fputc(' ', p2);
                        str[cnt++] = 'i';
                        str[cnt++] = 'd';
                        str[cnt++] = ' ';
                    }
                    break;
                }
                else{
                    tmp[indx++] = ch;
                }
            }
            while((ch = fgetc(p1)) != EOF){
                if(ch==' '){
                    break;
                }
                fputc(ch, p2);
                str[cnt++] = ch;
            }
        }
    }
    str[cnt] = '\0';
    fclose(p1);
    fclose(p2);
}

/* newly added start */

int valueValid(char *str) {
    char *searchForId;
    searchForId = strstr(str, "id");

    if(searchForId == NULL) {
        return 1;
    }
    return 0;
}

/* newly added end */

void storeAll(){
    int len = strlen(str);
    int i = 0;
    int valFlag = 0;
    char tempVarName[50] = {'\0'};
    while(i<len)
    {
        if(str[i]=='[')
        {
            char tmp[100];
            int indx = 0;
            i++;
            while(str[i] != ']'){
                tmp[indx++] = str[i++];
            }
            tmp[indx] = '\0';

            if(valFlag && strlen(tempVarName)) {
                if(valueValid(tmp))
                {
                    strcpy(NameVal[nv].val, tmp);
                }
                else {
                    strcpy(NameVal[nv].val, "");
                }
                strcpy(NameVal[nv].name, tempVarName);
                NameVal[nv].visited = 0;
                nv++;

                valFlag = 0;
                memset(tempVarName, 0, 50);
            }

            if(strcmp(tmp, "=") == 0) {
                valFlag = 1;
                int j = 0, k= 3;
                while(k<strlen(all[allrow - 1])){
                     tempVarName[j++] = all[allrow - 1][k++];
                }
            }

            /* newly added end */

            strcpy(all[allrow++], tmp);
        }
        i++;
    }
}

bool dataType(char *s){
    return ((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "long")) || (!strcmp(s, "long long")) || (!strcmp(s, "double")) || (!strcmp(s, "char")));
}

char scopeDet[100][100];
void scopeDetect(){
    int i=0;
    char sc[100];
    strcpy(sc, "global");
    while(i<allrow){
        char temp[100];
        strcpy(temp, all[i]);
        if(dataType(temp)){
            i++;
            char temp2[100];
            strcpy(temp2, all[i]);
            char temp4[100];
            int indx1=0;
            int j=3;
            while(temp2[j]!='\0'){
                temp4[indx1++]= temp2[j++];
            }
            temp4[indx1] = '\0';
            i++;
            char temp3[100];
            strcpy(temp3, all[i]);
            if(strcmp(temp3, "(")==0){
                strcpy(scopeDet[i-1], "global");
                strcpy(sc, temp4);
            } else{
                strcpy(scopeDet[i-1],sc);
            }
        } else if (strlen(temp)>2 && temp[0]=='i' && temp[1]=='d'){
            strcpy(scopeDet[i], sc);
        }
        i++;
    }
}

/* newly added start */
void setValue(char *name, int rowIdx) {
    int flag = 0;
    int i;
    for( i=0; i<nv; i++) {
        if(strcmp(NameVal[i].name, name) == 0 && !NameVal[i].visited) {
            strcpy(store[rowIdx].value, NameVal[i].val);
            NameVal[i].visited = 1;
            flag = 1;
            break;
        }
    }

    if(!flag) {
        strcpy(store[rowIdx].value, " ");
    }
}

/* newly added end */

void symbolTableGenerate(){
    int i = 1;
    while (i < allrow)
    {
        char temp[100];
        strcpy(temp, all[i]);
        if(strlen(temp)>2 && temp[0]=='i' && temp[1]=='d'){
            char name2[100];
            int j = 3, indx2=0;
            while(temp[j]!='\0'){
                name2[indx2++] = temp[j++];
            }
            name2[indx2] = '\0';
            bool found = 0;
            int in;
            for( in=1;in<rowNum;++in){ 
                if(strcmp(store[in].name, name2)==0 && strcmp(store[in].scope, scopeDet[i])==0){
                    found = 1;
                    break;
                }
            }
            if(!found){
                strcpy(store[rowNum].name, name2);
                strcpy(store[rowNum].scope, scopeDet[i]);

                /* newly added start */
                setValue(name2, rowNum);
                /* newly added end */

                store[rowNum].del=0;
                char dt[100];

                strcpy(dt, all[i-1]);
                if(dataType(dt))
                {
                    strcpy(store[rowNum].dtype, dt);
                }
                else{
                    char ty[100];
                    bool found = 0;
                    int in;
                    for ( in = rowNum-1; in>=1; --in){
                        if(strcmp(store[in].name, name2)==0){
                            found = 1;
                            strcpy(ty, store[in].dtype);
                            break;
                        }
                    }
                    if(found){
                        strcpy(store[rowNum].dtype, ty);
                    }
                }
                i++;
                if(strcmp(all[i], "(")){
                    strcpy(store[rowNum].type, "var");
                } else{
                    strcpy(store[rowNum].type, "func");
                }
                rowNum++;
            }
        }
        i++;
    }
}

void insert(){

    char name1[100], type1[100], dtype1[100], scope1[100];
    printf("Name: ");
    scanf("%s", &name1);
    printf("Type: ");
    scanf("%s",&type1);
    printf("Data Type: ");
    scanf("%s", &dtype1);
    printf("Scope: ");
    scanf("%s",&scope1);
    strcpy(store[rowNum].name, name1);
    strcpy(store[rowNum].type, type1);
    strcpy(store[rowNum].dtype, dtype1);
    strcpy(store[rowNum].scope, scope1);
    store[rowNum].del = 0;
    rowNum++;

}
void update()
{
    char name1[100], type1[100], dtype1[100], scope1[100],value1[100];
    printf("Name: ");
    scanf("%s", &name1);
    int i=0;
    int flag=0;
    int selectedrow;
    for (i=0; i<rowNum; i++)
    {
        if(strcmp(store[i].name, name1)==0)
        {
            selectedrow=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("identifier not found");
    }
    else
    {
        printf("Type: ");
        scanf("%s",&type1);
        printf("Data Type: ");
        scanf("%s", &dtype1);
        printf("Scope: ");
        scanf("%s",&scope1);
        printf("value: ");
        scanf("%s",&value1 );
        strcpy(store[selectedrow].name, name1);
        strcpy(store[selectedrow].type, type1);
        strcpy(store[selectedrow].dtype, dtype1);
        strcpy(store[selectedrow].scope, scope1);
        strcpy(store[selectedrow].value, value1);
        store[selectedrow].del = 0;
    }
    
    
}
/*
void search()
{
    int i;
    for (i=0; i<rowNum; i++)
    {
        int j;
        for(j=0; j<cnt;j++)
        {

        }
    }
    
}*/

void removeA(){
    int de;
    printf("Enter Row Number: ");
    scanf("%d",&de);
    int org=1;
    int i;
    for( i=0; i<rowNum; ++i){
        if(store[i].del==1) continue;
        if(org == de){
            store[i].del=1;
            break;
        }
        org++;
    }
}

void display(){
    int org=1;
    printf("SI No.\t\tName\t Type\t Data Type\tScope\tValue\n");
    int i;
    for (i=1; i<rowNum; ++i){
        if(store[i].del==1) continue;

        printf("%8d   |",org);
        printf("%8s   |",store[i].name);
        printf("%8s   |",store[i].type);
        printf("%8s   |",store[i].dtype);
        printf("%8s   |",store[i].scope);
        /* newly added start */
        printf("%7s\n",store[i].value);
        /* newly added end */
        org++;
    }

}

int main(){

    strcpy(scope1, "global");

    identifierSep();
    storeAll();
    scopeDetect();
    symbolTableGenerate();


    while (true)
    {
        printf("1.Insert\n2.update\n3.Delete\n4.Display\n5.Exit\n");
        printf("Select Operation: ");
        int op;
        scanf("%d", &op);
        if(op==1) insert(), printf("\n");
        else if(op==2)update(), printf("\n");
        else if(op==3) removeA(), printf("\n");
        else if(op==4) display(), printf("\n");
       // else if(op==5) search(), printf("\n");
        else printf("Invalid Option");
    }
    return 0;
}
