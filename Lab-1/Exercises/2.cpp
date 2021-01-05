#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    FILE *p1,*p2;
    char c;
    
    p1=fopen("1.txt","r");
    p2=fopen("2.txt","a");

    if(!p1 || !p2)
    {
        cout<<"File cant be opened"<<endl;
    }
    else
    {
         int line_cnt=1;
         string lineHolder;

        while((c=fgetc(p1))!=EOF)
        {
             lineHolder=lineHolder+c;
             //cout<<c<<endl;
            if(c=='\n')
            {

                stringstream ss;  
                ss<<line_cnt;
                string temp;
                ss>>temp;
                lineHolder=(temp)+lineHolder;
                char* str;
                str=&lineHolder[0];
                fputs(str,p2);
                lineHolder="";
                line_cnt++;
            }
        }
        cout<<"successfully written contents with line number in 2.txt"<<endl;
        fclose(p1);
        fclose(p2);

    }


}