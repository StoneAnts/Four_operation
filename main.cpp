#include<iostream>
#include "model.h"
#include "controller.h"
using namespace std;

int main(int argc, char* argv[])
{
    Repertory* r = expression(50, 100, 6, 1, 0, 0, 15, 0);
   // display(r,0);
    /*int array[9];
    for(int i = 1; i <= 9; i++)
    {
        array[i-1] = atoi(argv[i]);
    }
    Repertory* r = expression(array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7]);
    if(array[2]<=2)
    {
        array[8] = 0;
        getResult(r,1,array[8]);//array[8]表示是否加括号
    }*/
    getResult(r,1,1);
    return 0;
}

