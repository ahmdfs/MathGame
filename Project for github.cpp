
#include <iostream>
#include <iomanip>
#include "clsMathGame"

using namespace std;

int main()
{
    srand(time(0));

    clsMathGame game;
    //Called final  function in main
    game.GameStart();
    
    return 0;
}

