#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <sstream>

using namespace std;

void appinfo();
bool option_tokenizer(const string option);


int main()
{
    cout << "Welcome to the MATRIX APPLICATION!!" << endl;
    string option;
    appinfo();                  //chape moshakhasate barname
    while (option != "end_app") //while baraye daryafte option ta zamani ke mokhalefe end_app bashe
    {
        cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter your command:" << endl;
        getline(cin, option); //cin baraye in ke be space hasas nabashe
        if (option == "end_app") //agar "end_app" bood kharej she, OS ha khodeshoon bad az etmame barname dynamic memory ro delete mikonan, ehtiaji be delete kardan nist
        {
            break;
        }
        option_tokenizer(option); //farakhani tabe asli barname yani option_tokenizer baraye token kardane option va ejraye commande dade shode ba tabe e makhsoos
    }

    return 0;
}