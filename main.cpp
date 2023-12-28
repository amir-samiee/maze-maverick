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
bool isInteger(string s);
void getinput(string &input, string options, int from, int to);

// pieces of code that we will need:

// getting the date in the most proper format:
    // #include <ctime>
    // time_t now = time(0);
    // tm *ltm = localtime(&now);
    // char buffer[256];
    // strftime(buffer, sizeof(buffer), "%m/%d/%Y", ltm);
    // cout << buffer << endl;

// reading the history data:
    // ifstream historyfile("./Stats/History.txt");
    // string date, user, map, emptyline;
    // int time;
    // char result;
    // while (historyfile.ignore(6))
    // {
    //     getline(historyfile, date);
    //     historyfile.ignore(11);
    //     getline(historyfile, user);
    //     historyfile.ignore(10);
    //     getline(historyfile, map);
    //     historyfile.ignore(6);
    //     historyfile >> time;
    //     historyfile.ignore(8);
    //     historyfile >> result;
    //     getline(historyfile, emptyline);
    //     /*
    //     Processing data and printing it
    //     */
    // }
    // historyfile.close();


int main()
{
    string menu0 =
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
    string menu1 =
        "\n1. Easy"
        "\n2. Hard"
        "\n0. Back";
    string menu2 =
        "\n1. Choose from Existing Maps"
        "\n2. Import a Custom Map"
        "\n0. Back";
    string choice1, choice2;
    getinput(choice1, menu0, 0, 6);
    switch (stoi(choice1))
    {
    case 1:
        getinput(choice2, menu1, 0, 2);
        break;
    case 2:
        getinput(choice2, menu1, 0, 2);
        break;
    case 3:
        getinput(choice2, menu2, 0, 2);
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        cout << endl << yellow + "Exiting program...\n\n" + reset;
        return 0;
    }
    main();
}

void clearScreen()
{
    system("cls");
    // linux command must be added
}

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

void getinput(string &input, string options, int from, int to)
{
    bool indexerror = 0, typeerror = 0;
    do
    {
        clearScreen();
        cout << options << endl
             << ((indexerror) ? red + "Out of Index!\nPlease enetr a number between 0 and 6" + reset + "\n" : "")
             << ((typeerror) ? red + "Input wasn't a number!\nPlease enetr a number between 0 and 6" + reset + "\n" : "")
             << string(2 * (1 - indexerror - typeerror), '\n')
             << "Enter your choice: ";
        indexerror = typeerror = 0;
        cin >> input;
        if (isInteger(input))
        {
            if (input.size() > 2 || stoi(input) > to || stoi(input) < from)
                indexerror = 1;
        }
        else
            typeerror = 1;

    } while (indexerror || typeerror);
}
