#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <windows.h>
#include <fstream>
#include <vector>
// #include <cstdio>
#include <conio.h>
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

//function to find a random path
void mazepathmaker(int eorh, int x , int y, int x_1 , int y_1, int& length, int togo)

void clearScreen();                                             // this function has been declared to clear the screen on both windows and linux
bool isInteger(string s);                                       // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to); // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"
void createNewMap();                                            // creates a map (part 1)
void showHistory();                                             // shows the history of the games (part 4)
void showUsers();                                               // shows the users (part 5)


// pieces of code that we will need:

// getting the date in the most proper format:
// #include <ctime>
// time_t now = time(0);
// tm *ltm = localtime(&now);
// char buffer[256];
// strftime(buffer, sizeof(buffer), "%m/%d/%Y", ltm);
// cout << buffer << endl;

// reading the history data:
// ifstream historyfile("Stats/History.txt");
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
//     historyfile >> time >> emptyline;
//     historyfile.ignore(8);
//     historyfile >> result;
//     getline(historyfile, emptyline);
//     /*
//     Processing data and printing it
//     */
// }
// historyfile.close();

// updating the screen:
// #include <windows.h>
// #include <conio.h>
// #include <ctime>
// char ch;
// int i = 0 while (true)
// {
//     if (kbhit())
//     {
//         ch = getch();
//         if (ch == ' ')
//             updateScreen();
//     }
//     else
//     {
//         Sleep(100);
//         if (i++ --9)
//         {
//             i = 0;
//             updateScreen();
//         }
//     }
// }

// getting arrow keys as input:
// #include <conio.h> // for getch()
// #include <iostream> // for cout
// using namespace std;

// int main() {
//   int ch; // to store the character code
//   while (true) { // loop until ESC is pressed
//     ch = getch(); // get the first value
//     if (ch == 0 || ch == 224) { // check if it is 0 or 224
//       ch = getch(); // get the second value
//       switch (ch) { // check the arrow key code
//         case 72: cout << "UP\n"; break; // up arrow
//         case 80: cout << "DOWN\n"; break; // down arrow
//         case 75: cout << "LEFT\n"; break; // left arrow
//         case 77: cout << "RIGHT\n"; break; // right arrow
//       }
//     }
//     else if (ch == 27) { // check if it is ESC
//       break; // exit the loop
//     }
//   }
//   return 0;
// }

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

int main()
{

    string choice1;
    getinput(choice1, menu0, 0, 6);
    switch (stoi(choice1))
    {
    case 1:
        createNewMap();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        showHistory();
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        cout << endl
             << yellow + "Exiting program...\n\n" + reset;
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

void easy()
{
    clearScreen();
    cout << "This part of the program has not been ready yet\nEnter something to go back";
    _getch();
    return;
}

void hard()
{
    clearScreen();
    cout << "This part of the program has not been ready yet\nEnter something to go back";
    _getch();
    return;
}

void createNewMap()
{
    string choice;
    getinput(choice, "Create a new map:\n" + menu1, 0, 2);
    switch (stoi(choice))
    {
    case 1:
        easy();
        break;
    case 2:
        hard();
        break;
    default:
        return;
    }
}
void showHistory()
{
    clearScreen();
    ifstream historyfile("Stats/History.txt");
    string line;
    while (getline(historyfile, line))
        cout << line << endl;
    historyfile.close();
    cout << "\nPress any key to coninue: ";
    _getch();
}
void showUsers()
{
    clearScreen();
    ifstream usersfile("Users/allusers.txt");
    vector<string> users;
    // incomplete
    // incomplete
    // incomplete
    // incomplete
    // incomplete
    // incomplete
    usersfile.close();
    cout << "\nPress any key to coninue: ";
    _getch();
}