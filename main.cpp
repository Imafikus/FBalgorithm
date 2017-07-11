#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#define MAX 1000
using namespace std;

float E[MAX][MAX];
float T[MAX][MAX];
float P[MAX];
int X[MAX];
float alfa[MAX][MAX];
float beta[MAX][MAX];
float normalized[MAX][MAX];


void forwardBackward(int &observedVars, int &possibleStates)
{
    //inicijalizacija vektora
    for (int i = 0; i < possibleStates; i++)
        for (int j = 0; j < possibleStates; j++)
            alfa[i][j]=0;

    for (int i = 0; i < possibleStates; i++)
        for (int j = 0; j < possibleStates; j++)
            beta[i][j]=0;

    ///////////FORWARD
    for(int i = 1; i <= possibleStates; i++)
        alfa[1][i] = P[i]*E[X[1]][i];

    for(int k = 2; k <= observedVars; k++)
        for(int i = 1; i <= possibleStates; i++)
            for(int j = 1; j <= possibleStates; j++)
                alfa[k][i] += alfa[k-1][i] * E[X[k]][i] * T[i][j];


    //BACKWARD

    for(int i = 1; i <= possibleStates; i++)
        beta[observedVars][i] = 1;

    for(int k = observedVars-1; k >= 1; k--)
        for(int i = 1; i <= possibleStates; i++)
            for(int j = 1; j <= possibleStates; j++)
                beta[k][i] += beta[k+1][i] * E[X[k+1]][i] * T[i][j];

    //NORMALIZACIJA

    for (int k = 1; k <= observedVars; k++)
    {
        float zbir = 0;

        for(int i = 1; i <= possibleStates; i++)
            zbir += alfa[k][i] * beta[k][i];

        float x = 1 / zbir;

        for (int i = 1; i <= possibleStates; i++)
            normalized[k][i] = alfa[k][i] * beta[k][i] * x;
    }


}
int main()
{
    int observedVars = 4;
    int possibleStates = 4;
    int possibleStatesX = 2;
    //pravljenje T
    for (int i = 0; i <= possibleStates; i++)
        for (int j = 0; j <= possibleStates; j++)
            T[i][j]=0.25;

    //pravljenje E
    for (int i = 0; i <= possibleStatesX; i++)
        for (int j = 0; j <= possibleStates; j++)
            E[i][j]=0.5;

    //pravljenje P
    for(int i = 0; i <= possibleStates; i++)
        P[i] = 0.25;
    //pravljenje X
    for(int i = 0; i < observedVars; i++)
        cin>>X[i];

    forwardBackward(observedVars, possibleStates);

    for (int i = 1; i <= observedVars; i++)
    {
        for (int j = 1; j <= possibleStates; j++)
            cout << normalized[i][j];
        cout << endl;
    }


}
