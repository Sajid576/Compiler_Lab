#include <bits/stdc++.h>

using namespace std;

vector<string>vec;

int main(void)
{
    FILE *p1;
    char c;

    p1=fopen("1.txt","r");
    
    if(!p1 )
    {
        cout<<"File cant be opened"<<endl;
    }
    else
    {
        bool headerFound=false;
        bool storeHeaderName=false;
        bool stopHeaderName=false;

        string headerContainer="";
       
        while((c=fgetc(p1))!=EOF)
        {
            
 
            if(c=='#')
            {
                headerFound=true;
                
            }
            else if(headerFound==true && storeHeaderName==false)
            {
                if(c=='<')
                {
                    storeHeaderName=true;   
                }
            }
            else if(storeHeaderName==true && headerFound==true)
            {
                if(c=='>')
                {
                        stopHeaderName=true;
                        headerFound=false;
                        storeHeaderName=false;
                        vec.push_back(headerContainer);
                        headerContainer="";
                }
                else
                {
                        headerContainer+=c;
                }
               
            }

        }
    }
    cout<<"List of names of header files: "<<endl;
    for(int i=0;i< vec.size();i++)
    {
            cout<<vec[i]<<endl;  
    }

    fclose(p1);
    


}