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
void mazepathmaker(int eorh, int **& maze , int x , int y, int x_1 , int y_1, int togo , int& flag);

void clearScreen();                                             // this function has been declared to clear the screen on both windows and linux
bool isInteger(string s);                                       // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to); // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"
void createNewMap();
void showHistory();
void showUsers();
bool isvalidint(string& input, int& output);                    //checks if the input is integer

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

bool isvalidint(string& input , int& output)
{
    try
    {
        output = stoi(input);
    }
    catch(invalid_argument)
    {
        return false;
    }
    return true;
}

void getintinput(string interact, string& input, int& result)
{
    // clearScreen();
    cout << interact << '\n';
    getline(cin , input);
    while(!isvalidint(input, result))
    {
        clearScreen();
        cout << "Invalid entry. pls try again: \n";
        getline(cin, input);
    }
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

void createNewMap()
{
    string choice , Scolumn , Srow;
    int mapdif ,flag = 0 , column , row , length , **maze;
    getintinput("Create a new map: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    while(mapdif > 2 || mapdif < 0)
    {
        getintinput("Pls enter a valid choice: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    }
    getintinput("Pls enter maze height: \n", Srow, row);
    while(row < 2)
    {
        getintinput("Pls enter maze height (it cannot be less than 2): \n", Srow, row);
    }
    getintinput("Pls enter maze width: \n", Scolumn, column);
    while(column < 2)
    {
        getintinput("Pls enter maze width (it cannot be less than 2): \n", Scolumn, column);
    }
    length = column + row - 2;
    maze = new int*[row + 2];
    for(int i = 0; i < row + 2; i++)
    {
        maze[i] = new int[column + 2];
    }
    for(int i = 0; i < row + 2; i++)
    {
        if(i == 0 || i == row + 1)
        {
            for(int l = 0 ; l < column + 2; l++)
            {
                maze[i][l] = 0;
            }
        }
        else
        {
            for(int l = 0; l < column + 2; l++)
            {
                if(l == 0 || l == column + 1)
                {
                    maze[i][l] = 0;
                }
                else
                {
                    maze[i][l] = 1;
                }
            }
        }
    }
    mazepathmaker(mapdif, maze ,row, column, 1, 1, length, flag);
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
void mazepathmaker(int eorh, int**& maze, int x , int y, int x_1 , int y_1, int togo , int& flag)
{
    if(maze[x_1][y_1] == 0)
    {
        return;
    }
    maze[x_1][y_1] = 0;
    string Slength;
    if(eorh == 2)
    {
        getintinput("Pls enter the length of the path:\n", Slength, togo);
        while(togo < x + y - 2 || togo > x * y - 1)
        {
            cout << "Such a path cannot exist. \n Try again: \n";
            getintinput( "Pls enter the length of the path:\n", Slength, togo);
        }
    }
    if(togo == 0 && x_1 == x && y_1 == y)
    {
        flag = 1;
        return;
    }
    if(togo < x + y - x_1 - y_1)
    {
        maze[x_1][y_1] = 1;
        return;
    }
    vector<int> arr;
    for(int i = 1; i < 5; i++)
    {
        arr.push_back(i);
    }
    std::random_device rd;
    std::default_random_engine rng(rd());
    shuffle(arr.begin() , arr.end() ,rng);
    for(int i = 0; i < 4; i++)
    {
        switch (arr[i])
        {
        case 1:
            mazepathmaker(1 , maze ,x , y , x_1 + 1 , y_1, togo - 1, flag);
            if(flag == 1)
            {
                return;
            }
            break;
        case 2:
            mazepathmaker(1, maze ,x , y , x_1 - 1 , y_1, togo - 1, flag);
            if(flag == 1)
            {
                return;
            }
            break;
        case 3:
            mazepathmaker(1, maze ,x , y , x_1 , y_1 + 1, togo - 1, flag);
            if(flag == 1)
            {
                return;
            }
            break;
        default:
            mazepathmaker(1, maze ,x , y , x_1 , y_1 - 1, togo - 1, flag);
            if(flag == 1)
            {
                return;
            }
            break;
        }
    }
    maze[x_1][y_1] = 1;
}