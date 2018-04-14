#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
typedef struct{
   float** array;
   int row;
   int col;
}Repertory;

Repertory* expression(int number, int max, int operandNumber, bool decimal, bool negative, bool bracketint, int opreation, int output);
void display(Repertory* rep,int output);
void getResult(Repertory* rep, bool isResult, bool isBracket);
#endif // CONTROLLER_H_INCLUDED
