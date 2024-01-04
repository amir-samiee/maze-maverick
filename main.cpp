#include <iostream>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
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
void clearScreen();                                             // this function has been declared to clear the screen on both windows and linux
bool isInteger(string s);                                       // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to); // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"
void createNewMap();                                            // creates a map (part 1)
void playground();                                              // the interactive game part (part 2)
void showHistory();                                             // shows the history of the games (part 4)
void showUsers();                                               // shows the users (part 5)
void leaderboard();                                             // shows the leader users (part 6)

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
    playground();
    string choice1;
    // cin >> choice1;
    getinput(choice1, menu0, 0, 6);
    switch (stoi(choice1))
    {
    case 1:
        createNewMap();
        break;
    case 2:
        playground();
        break;
    case 3:
        break;
    case 4:
        showHistory();
        break;
    case 5:
        showUsers();
        break;
    case 6:
        leaderboard();
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
             << ((indexerror) ? red + "Out of Index!\nPlease enetr a number between " + to_string(from) + " and " + to_string(to) + reset + "\n" : "")
             << ((typeerror) ? red + "Input wasn't a number!\nPlease enetr a number between " + to_string(from) + " and " + to_string(to) + reset + "\n" : "")
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

// struct mfile // a struct for the
// {
//     int value;
//     bool ispassed = 0;
//     bool ison = 0;
// };

void printmap(int **values, bool **ispassed, int currentx, int currenty, int lastx, int lasty, int m, int n, bool includezeros = 1)
{
    clearScreen();
    for (int i = 0 + !includezeros; i < m - !includezeros; i++)
    {
        for (int j = 0 + !includezeros; j < n - !includezeros; j++)
        {
            if (i == currentx && j == currenty)
                cout << red;
            else if (i == lastx && j == lasty)
                cout << yellow;
            else if (ispassed[i][j])
                cout << green;
            else if (i == m - 2 + includezeros && j == n - 2 + includezeros)
                cout << cyan;
            else if (!values[i][j])
                cout << magenta;
            cout << values[i][j] << reset << ' ';
        }
        cout << endl;
    }
    // clearScreen();
    // int i, j;
    // for (i = 0 + !includezeros; i < min(currentx, lastx); i++)
    // {
    //     for (j = 0 + !includezeros; j < n - !includezeros; j++)
    //     {
    //         if (ispassed[i][j])
    //             cout << green;
    //         else if (!values[i][j])
    //             cout << magenta;
    //         cout << values[i][j] << reset << ' ';
    //     }
    //     cout << endl;
    // }
    // // bool lastlinehandle = max(currentx, lastx) == m - !includezeros - 1;
    // if (min(currentx, lastx) == m - !includezeros - 1)
    // {
    //     i = m - !includezeros - 1;
    //     for (j = 0 + !includezeros; j < n - !includezeros - 1; j++)
    //     {
    //         if (i == currentx && j == currenty)
    //             cout << red;
    //         else if (i == lastx && j == lasty)
    //             cout << yellow;
    //         else if (ispassed[i][j])
    //             cout << green;
    //         else if (!values[i][j])
    //             cout << magenta;
    //         cout << values[i][j] << reset << ' ';
    //     }
    //     cout << cyan << values[i][j] << reset << endl;
    // }
    // for (i = min(currentx, lastx); i <= max(currentx, lastx); i++)
    // {
    //     for (j = 0 + !includezeros; j < n - !includezeros; j++)
    //     {
    //         if (!values[i][j])
    //             cout << magenta;
    //         else if (i == currentx && j == currenty)
    //             cout << red;
    //         else if (i == lastx && j == lasty)
    //             cout << yellow;
    //         else if (ispassed[i][j])
    //             cout << green;
    //         cout << values[i][j] << reset << ' ';
    //     }
    //     cout << endl;
    // }
    // for (i = max(currentx, lastx) + 1; i < m - !includezeros - 1; i++)
    // {
    //     for (j = 0 + !includezeros; j < n - !includezeros; j++)
    //     {
    //         if (ispassed[i][j])
    //             cout << green;
    //         else if (!values[i][j])
    //             cout << magenta;
    //         cout << values[i][j] << reset << ' ';
    //     }
    //     cout << endl;
    // }
    // i = m - !includezeros - 1;
    // for (j = 0 + !includezeros; j < n - !includezeros - 1; j++)
    // {
    //     if (ispassed[i][j])
    //         cout << green;
    //     else if (!values[i][j])
    //         cout << magenta;
    //     cout << values[i][j] << reset << ' ';
    // }
    // cout << cyan << values[i][j] << reset << endl;
}

struct user
{
    string name;
    int games;
    int wins;
    int lastwintime;
    int totaltime;
};

vector<user> getplayersdata()
{
    ifstream usersfile("Users/allusers.txt");
    vector<string> users;
    string name, line;
    while (usersfile >> name)
        users.push_back(name);
    usersfile.close();
    vector<user> players;
    for (auto u : users)
    {
        // cout << user << endl;
        ifstream userfile("Users/" + u + ".txt");
        user opened;
        opened.name = u;
        // getline(usersfile, line);
        userfile.ignore(7);
        userfile >> opened.games;
        userfile.ignore(6);
        userfile >> opened.wins;
        // getline(usersfile, line);
        userfile.ignore(15);
        userfile >> opened.lastwintime;
        userfile.ignore(12);
        userfile >> opened.totaltime;
        players.push_back(opened);
        userfile.close();
    }
    return players;
}
int next(int **values, bool **ispassed, int m, int n, int x, int y, int x0, int y0, int sum, int start_time) // returns a code: 0 for continuing, 1 for "User won", -1 for "User lost"
{
    if (x == m && y == n && values[x][y] * 2 == sum)
    {
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0);
        return 1;
    }
    // if (values[x][y] == 0 || ispassed[x][y])
    //     return 0;
    ispassed[x][y] = 1;
    int x2 = x, y2 = y, ch, i = 0, screenupdatespersecond = 7;
    while (1)
    {
        clearScreen();
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0);
        cout << "Sum of the blocks: " << sum << "\nTime: "
             << time(0) - start_time;
        ch = getch(); // get the first value
        while (ch != 0 && ch != 224 && ch != 27)
            ch = getch(); // get the first value
        if (ch == 0 || ch == 224)
        {                 // check if it is 0 or 224
            ch = getch(); // get the second value
            switch (ch)
            {        // check the arrow key code
            case 72: // UP
                x2 = x - 1;
                break; // up arrow
            case 80:   // DOWN
                x2 = x + 1;
                break; // down arrow
            case 75:   // LEFT
                y2 = y - 1;
                break; // left arrow
            case 77:   // RIGHT
                y2 = y + 1;
                break; // right arrow
            }
        }
        else if (ch == 27) // check if it is ESC
            return -1;     // exit the loop
        if (x2 == x0 && y2 == y0)
            break;
        if (!values[x2][y2] || ispassed[x2][y2])
        {
            x2 = x;
            y2 = y;
            continue;
        }
        int flag = next(values, ispassed, m, n, x2, y2, x, y, sum + values[x2][y2], start_time);
        if (flag)
            return flag;
        x2 = x;
        y2 = y;
    }
    ispassed[x][y] = 0;
    return 0;
}

void playground() // more than 1 digit is not supported yet
{
    while (1)
    {
        int i = 1;
        bool valid = 1, brk = 0;
        string choice, name, list = "List of maps:\n", username;
        ifstream mapfile, allmaps("Maps/allmaps.txt"), allusers("Users/allusers.txt");
        vector<string> maps;
        getinput(choice, "Playground\n" + menu2, 0, 2);
        switch (stoi(choice))
        {
        case 0:
            return;
        case 1:
            while (allmaps >> name)
            {
                list += "\n\t" + to_string(i) + ". " + name;
                maps.push_back(name);
                i++;
            }
            getinput(choice, list + "\n\t0. Back", 0, maps.size());
            if (choice == "0")
                continue;
            mapfile.open("Maps/" + maps[stoi(choice) - 1] + ".txt");
            break;
        case 2:
            while (!mapfile.is_open())
            {
                clearScreen();
                if (!valid && choice != "")
                    cout << red << "The file doesn't exist" << reset;
                cout << "\nEnter a path to a custom map or enter 0 to go back: ";
                valid = 0;
                getline(cin, choice);
                // getline(cin, choice);
                if (choice == "0")
                {
                    brk = 1;
                    break;
                }
                mapfile.open(choice);
            }
            if (brk)
                continue;
            break;
        }
        allmaps.close();

        vector<string> users;
        while (getline(allusers, name))
            users.push_back(name);
        allusers.close();
        valid = 1;
        clearScreen();
        while (1)
        {
            cout << "\nPlease enter a username: ";
            getline(cin, username);
            for (i = 0; i < users.size(); i++)
                if (users[i] == username)
                {
                    valid = 0;
                    break;
                }
            if (valid && username != "")
                break;
            clearScreen();
            if (username != "")
                cout << red << "Username taken before!!" << reset;
        }
        // ifstream mapfile("Maps/Map2.txt");
        // get input ...
        int m, n, x = 1, y = 1;
        mapfile >> m >> n;
        int **values = new int *[m + 2];
        bool **ispassed = new bool *[m + 2];
        for (int i = 0; i < m + 2; i++)
        {
            values[i] = new int[n + 2];
            ispassed[i] = new bool[n + 2];
            fill(&values[i][0], &values[i][0] + n + 2, 0);
            fill(&ispassed[i][0], &ispassed[i][0] + n + 2, 0);
        }
        for (int i = 1; i < m + 1; i++)
            for (int j = 1; j < n + 1; j++)
                mapfile >> values[i][j];
        mapfile.close();
        int start = time(0);
        // printmap(values, ispassed, 1, 1, 0, 0, m + 2, n + 2, 0);
        int sum = 0, ch, x2 = x, y2 = y, x0 = x, y0 = y;
        next(values, ispassed, m, n, x, y, 1, 1, values[1][1], start);
        int end = time(0);

        for (int i = 0; i < m; i++)
        {
            delete[] values[i];
            delete[] ispassed[i];
        }
        delete[] values;
        delete[] ispassed;
        cout << "\nPress any key to coninue: ";
        _getch();
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
    string name;
    while (usersfile >> name)
        users.push_back(name);
    usersfile.close();

    bool nameerror = 0;
    do
    {
        clearScreen();
        cout << "List of users:\n\n";
        for (int i = 0; i < users.size(); i++)
            cout << '\t' << users[i] << endl;
        cout << (nameerror ? red + "Invalid name!\nPlease enter a name included in the list\n" + reset : "\n\n")
             << "Enter a name or enter 0 to go back: ";
        cin >> name;
        if (name == "0")
            return;
        nameerror = 1;
        for (int i = 0; i < users.size(); i++)
            if (users[i] == name)
            {
                nameerror = 0;
                break;
            }

    } while (nameerror);
    ifstream userfile("Users/" + name + ".txt");
    string line;
    // if (userfile.is_open())
    clearScreen();
    cout << "Name: " << name << endl;
    while (getline(userfile, line))
        cout << line << endl;
    // else
    //     cout << red + "error" + reset;
    usersfile.close();
    cout << "\nPress any key to coninue: ";
    _getch();
    showUsers();
}

bool compare(user a, user b)
{
    if (a.wins > b.wins)
        return 0;
    if (a.wins < b.wins)
        return 1;
    if (a.totaltime < b.totaltime)
        return 0;
    if (a.totaltime > b.totaltime)
        return 1;
    return (b.name.compare(a.name) < 0);
}

void leaderboard()
{
    clearScreen();
    cout << "Finding best players...";
    vector<user> players = getplayersdata();
    sort(players.begin(), players.end(), compare);
    clearScreen();
    cout << "Leaderboard:\n\n";
    int size = players.size();
    for (int i = min(3, size) - 1; i >= 0; i--)
        cout << min(3, size) - i << ". " << players[i].name << endl;
    cout << "\nPress any key to coninue: ";
    _getch();
}