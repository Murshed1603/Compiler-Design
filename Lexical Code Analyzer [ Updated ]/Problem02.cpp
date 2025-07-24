#include<iostream>
#include<conio.h>
using namespace std;

int main(void)
{
    string input;
    cout<<"Enter your input : ";
    cin>>input;

    int opCount = 0;

    for(int i=0; i<input.length(); i++)
    {
        char ch = input[i];

        if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='=')
        {
            opCount = opCount + 1;
            cout<<"operator "<<opCount<<": "<<ch<<endl;
        }
    }
    if(opCount==0)
    {
        cout<<"No operators found !"<<endl;
    }
    getch();
}
