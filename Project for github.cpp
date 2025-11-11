
#include <iostream>
#include <iomanip>

using namespace std;

//dynamic header sceen to show title a
class clsScreen
{

protected :

    void ShowHeaderMenu(string title , string body = "") // I can use this function anytime , because it used parameters ,and I can modify it easier .
    {
        time_t T = time(0);
        tm now;
        localtime_s(&now,&T);

        short lengthOfTitle = title.length();  // I used 'short' because the numbers won't to be large
        short lengthOfBody = body.length();

        cout << setw(30) << "" << "-------------------------------------------------------\n";
        cout << setw(63 - lengthOfTitle) << "" << title << endl;
        cout << setw(40 - lengthOfBody) << body << endl;
        cout << setw(30) << "" << "-------------------------------------------------------\n";
        cout << setw(32) << "" <<
            (now.tm_mon + 1) << "/" 
            << (now.tm_mday) << "/" 
            << (now.tm_year + 1900) << endl;
    }
};

//Math game that asks random arithmetic questions with different difficulty levels
class clsMathGame : protected clsScreen
{
private :

    double _FirstNumber = 0;
    double _SecondNumber = 0;
    double _PlayerAnswer = 0;
    double _RightResult = 0;
    short _CorrectCount = 0;
    short _WrongCount = 0;

    enum enLevel {enEasy = 1 , enMedium = 2 , enHard = 3};
    enum enOpType {enSum = 1 , enSub = 2 , enMulti = 3 , enDiv = 4};

     short ReadNumberInRange(string message, short from, short to)
    {
        short number = 0;

        while (true)
        {
            cout << message;
            cin >> number;

            if (cin.fail())
            {

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\ninvalid number , please enter a number : ";
   
                continue;
            }

            if (number < from || number > to)
            {
                cout << "\nnumber out of range , please enter between " << from << " and " << to << " : ";
               
                continue;
            }

            break;
        }

        return number;
    }

    // Read number of rounds from user :
    short ReadRoundsCount()
    {
        return ReadNumberInRange("\nHow many rounds you want to play from 1 to 10 : ", 1, 10);

    }

    //read game Level from user : 
    enLevel ReadGameLevel()
    {
        return (enLevel)ReadNumberInRange("\nChoose Level you want : [1] easy , [2] medium , [3] hard  : ", 1, 3);

    }

    //Read Operator from user :
    enOpType ReadOperationType()
    {
        return (enOpType)ReadNumberInRange("\nChoose operator you want : 1 [+] , 2 [-] , 3 [*] , 4 [/]  ? ", 1, 4);
    }

    // return Random numbers : easy , medium , hard
    int GenerateRandomNumber(enLevel level)
    {
        switch (level)
        {
        case enLevel::enEasy:
            return rand() % 50 + 1;
        case enLevel::enMedium:
            return rand() % 100 + 1;
        case enLevel::enHard:
            return rand() % 200 + 1;
        default :
            return 0;
        }
    }

    //Get result of First number and Second number
    double CalculateAnswer(enOpType type)
    {
        switch (type)
        {
        case enOpType::enSum:
            return _FirstNumber + _SecondNumber;
        case enOpType::enSub:
            return _FirstNumber - _SecondNumber;
        case enOpType::enMulti:
            return _FirstNumber * _SecondNumber;
        case enOpType::enDiv:
                return _FirstNumber / _SecondNumber;
        default :
            return 0;
        }
    }

    // return Operations : + , - , * , /
    char GetOperatorSymbol(enOpType type)
    {
        switch (type)
        {
        case enOpType::enSum:
            return '+';
        case enOpType::enSub:
            return '-';
        case enOpType::enMulti:
            return '*';
        case enOpType::enDiv:
            return '/';
        default :
            return ' ';
        }
    }

    //Print the Question
    void AskPlayerForAnswer(enOpType type)
    {
        char Op = GetOperatorSymbol(type);

        cout << "Answer : \n";
        cout << _FirstNumber << " " << Op << " " << _SecondNumber << "  =  ";
        cin >> _PlayerAnswer;
    }

    //Check if answer is correct
    bool IsAnswerCorrect(enOpType type)
    {
        _RightResult = CalculateAnswer(type);
        if (abs(_RightResult - _PlayerAnswer) < 0.001)
        {
            _CorrectCount++;
            return true;
        }
        else
        {
            _WrongCount++;
            return false;
        }
    }

    // Print result of round
    void ShowRoundResult(enOpType type)
    {
        if (IsAnswerCorrect(type))
        {
            cout << "\nYour answer is right :)\n";
        }
        else
        {
            cout << "\nYour answer is wrong :(\n";
            cout << "Right answer is : " << _RightResult << endl;
        }
    }

    //print the final result in the last
    void ShowFinalResult()
    {
        cout << "\n-----------------------------------------\n";
        cout << "Number of Right answer : " << _CorrectCount << endl;
        cout << "Number of wrong answer : " << _WrongCount << endl;
        cout << "-----------------------------------------\n";
    }

    void PlayRound(enLevel level, enOpType type)
    {
        _FirstNumber = GenerateRandomNumber(level);
        _SecondNumber = GenerateRandomNumber(level);

        AskPlayerForAnswer(type);
        ShowRoundResult(type);
     
    }

public :

    //Constructor for Random Numbers
    clsMathGame()
    {
        srand(time(0));
    }

    // Start the game and ask if player want to play again
     void GameStart()
    {
         char answer = 'n';

         do
         {
             system("cls");

             ShowHeaderMenu("Math Game");

             enLevel level = ReadGameLevel();
             enOpType type = (enOpType)ReadOperationType();
             short rounds = ReadRoundsCount();

             for (short i = 1; i <= rounds; i++)
             {
                 cout << "\nRound [" << i << "] \n\n";
                 PlayRound(level,type);
             }

             ShowFinalResult();
             cout << "\nDo you want to play again : [y]/[n]  ? ";
             cin >> answer;
             _CorrectCount = 0;
             _WrongCount = 0;
         } while (toupper(answer) == 'Y');
    }
};
int main()
{
    srand(time(0));

    clsMathGame game;

    
    //Called final  function in main
    game.GameStart();

    return 0;
}