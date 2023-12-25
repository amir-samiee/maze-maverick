#include <iostream>
#include <windows.h>
#include <ctype.h>
using namespace std;
// COLORS
const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");
// FUNCTIONS
void clearScreen();
bool isInteger(char c);
bool isInteger(string s);
void menu();

int main()
{
    menu();
    return 0;
}

void clearScreen()
{
    system("cls");
    // linux command must be added
}

// bool isInteger(char c)
// {
//     if (!(48 <= c && c <= 57))
//         return 0;
//     return 1;
// }

bool isInteger(string s)
{
    for (int i = 1; i < s.size(); i++)
    {
        // if (!isInteger(s[i]))
        if (!isdigit(s[i]))
            return 0;
    }
    // if (!(isInteger(s[0]) || s[0] == '-'))
    if (!(isdigit(s[0]) || s[0] == '-'))
        return 0;
    return 1;
}

void menu()
{
    string menu =
        "\n1. Create a New Map"
        // "\n- 1.1 Easy"
        // "\n- 1.2 Hard"
        "\n2. Playground"
        // "\n- 2.1 Choose from Existing Maps"
        // "\n- 2.1 Import a Custom Map"
        "\n3. Solve a Maze"
        // "\n- 3.1 Choose from Existing Maps"
        // "\n- 3.1 Import a Custom Map"
        "\n4. History"
        "\n5. Users"
        "\n6. Leaderboard"
        "\n0. Exit";
    string choice1;
    bool indexerror = 0, typeerror = 0;
    do
    {
        clearScreen();
        cout << menu << endl
             << ((indexerror) ? red + "Out of Index! Please enetr a number between 0 and 6" + reset + "\n" : "\n")
             << ((typeerror) ? red + "Input wasn't a number! Please enetr a number between 0 and 6" + reset + "\n" : "\n")
             << "Enter your choice: ";
        indexerror = typeerror = 0;
        cin >> choice1;
        if (isInteger(choice1))
        {
            if (choice1.size() > 2 || stoi(choice1) > 6 || stoi(choice1) < 0)
                indexerror = 1;
        }
        else
            typeerror = 1;

    } while (indexerror || typeerror);
}