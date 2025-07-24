#include<iostream>
#include<conio.h>
using namespace std;
int main(void)
{
    string input;
    cout<<"Enter your input : ";
    cin>>input;
    for(int i=0; i<input.length(); i++)
    {
        if(input[i]>=48 && input[i]<=57)
        {
            cout<<"numeric constant";
            break;
        }
        else
        {
            cout<<"not numeric";
            break;
        }
    }
    getch();
}
