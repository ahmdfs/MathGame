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
