#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <ctype.h>
// #include <cstdio>
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
void mazepathmaker(int **& maze , int row , int column , int rowin , int columnin , int togo , int& flag);
//function to fill the maze
void mazefiller(int **& maze, int row, int column, int length , int lowV , int highV , int leastW, int mostW);
//function for generating random int excluding 0
int randint(int floor, int ceil);
void clearScreen();                                             // this function has been declared to clear the screen on both windows and linux
bool isInteger(string s);                                       // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to); // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"

void createNewMap();
bool isvalidint(string& input, int& output);                    //checks if the input is integer
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

    string choice1;
    // cin >> choice1;
    getinput(choice1, menu0, 0, 6);
    switch (stoi(choice1))
    {
    case 1:
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

void createNewMap()
{
    string choice , Scolumn , Srow , Slength;
    int mapdif ,flag = 0 , column , row , length , **maze;
    //gets map difficulty from user
    getintinput("Create a new map: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    while(mapdif > 2 || mapdif < 0)
    {
        getintinput("Pls enter a valid choice: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    }
    // gets maze height from user 
    getintinput("Pls enter maze height: \n", Srow, row);
    while(row < 2)
    {
        getintinput("Pls enter maze height (it cannot be less than 2): \n", Srow, row);
    }
    // gets maze width from user
    getintinput("Pls enter maze width: \n", Scolumn, column);
    while(column < 2)
    {
        getintinput("Pls enter maze width (it cannot be less than 2): \n", Scolumn, column);
    }
    //length for basic maze
    length = column + row - 2;
    // checks the difficulty option for advanced path making
    if(mapdif == 2)
    {
        // gets length of path for the maze from user
        getintinput("Pls enter the length of the path:\n", Slength, length);
        while(length < row + column - 2 || length > row * column - 1 || length % 2 != (row + column) % 2)
        {
            cout << "Such a path cannot exist. \nTry again: \n";
            getintinput( "Pls enter the length of the path:\n", Slength, length);
        }
    }
    // setting the maze up
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
    // finding a random path for maze
    mazepathmaker(maze ,row, column, 1, 1, length, flag);
    
    string SlowV , ShighV, SleastW, SmostW;
    int lowV = -3 , highV = 3, leastW = 2, mostW = 5;
    if(mapdif == 2)
    {
        // inputs the min value of blocks
        getintinput("Pls enter your choice of min value of block: ", SlowV, lowV);
        // inputs the max value of blocks
        getintinput("Pls enter your choice of max value of block: ", ShighV, highV);
        while(lowV > highV || (lowV == highV && lowV == 0))
        {
            getintinput("Pls enter your choice of max value of block (it can't be less than the min value): ", ShighV, highV);
        }
        // inputs the least amount of walls
        getintinput("Pls enter your choice of min amount of walls: ", SleastW, leastW);
        while(leastW < 0 || leastW > row * column - length - 1)
        {
            getintinput("Pls enter your choice of min amount of walls \n(it can't be less than 0 or more than amount of block available): ", SleastW, leastW);
        }
        //inputs the most amount of walls
        getintinput("Pls enter your choice of max amount of walls: ", SleastW, mostW);
        while(leastW > mostW)
        {
            getintinput("Pls enter your choice of max amount of walls (it can't be less than the min amount of walls): ", SleastW, mostW);
        }
    }
// struct mfile // a struct for the
// {
//     int value;
//     bool ispassed = 0;
//     bool ison = 0;
// };

void printmap(int **values, bool **ispassed, int currentx, int currenty, int lastx, int lasty, int m, int n, bool includezeros = 1, int filecapacity = 1)
{
    clearScreen();
    cout << "Use the arrow keys to move. Press Esc to exit\n\n";
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
            cout << left << setw(filecapacity) << values[i][j] << reset << ' ';
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
    string name = "";
    int games = 0;
    int wins = 0;
    int lastwintime = 0;
    int totaltime = 0;
};

vector<string> getusers(string filename = "Users/allusers.txt")
{
    ifstream usersfile(filename);
    vector<string> users;
    string name;
    while (usersfile >> name)
        users.push_back(name);
    return users;
}
user formuser(string name)
{
    ifstream userfile("Users/" + name + ".txt");
    user opened;
    opened.name = name;
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
    userfile.close();
    return opened;
}
vector<user> getusersdata(string filename = "Users/allusers.txt")
{
    vector<string> users = getusers(filename);
    vector<user> players;
    for (auto u : users)
        players.push_back(formuser(u));
    return players;
}

void updateusers(user &player, bool won)
{
    vector<string> users = getusers();
    bool isin = 0;
    for (int i = 0; i < users.size(); i++)
        if (player.name == users[i])
        {
            isin = 1;
            break;
        }
    if (isin)
    {
        user beforeupdate = formuser(player.name);
        player.games = beforeupdate.games;
        player.wins = beforeupdate.wins;
        if (!won)
            player.lastwintime = beforeupdate.lastwintime;
        player.totaltime += beforeupdate.totaltime;
    }
    else
    {
        ofstream usersfile("Users/allusers.txt", ios::app);
        usersfile << endl
                  << player.name;
        usersfile.close();
    }
    player.totaltime += player.lastwintime;
    player.wins += won;
    player.games++;
    ofstream userfile("Users/" + player.name + ".txt");
    userfile << "Games: " << player.games << endl;
    userfile << "Wins: " << player.wins << endl;
    userfile << "Last Win Time: " << player.lastwintime << endl;
    userfile << "Total Time: " << player.totaltime;
    userfile.close();
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

void updateleaderboard(user player)
{
    vector<user> leaders = getusersdata("Stats/Leaderboard.txt");
    bool isin = 0;
    for (int i = 0; i < leaders.size(); i++)
    {
        if (leaders[i].name == player.name)
        {
            isin = 1;
            break;
        }
    }
    if (!isin)
        leaders.push_back(player);
    sort(leaders.begin(), leaders.end(), compare);
    reverse(leaders.begin(), leaders.end());
    int size = leaders.size();
    ofstream leadfile("Stats/Leaderboard.txt");
    for (int i = 0; i < min(size, 3); i++)
        leadfile << leaders[i].name << endl;
    leadfile.close();
}

string Date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[256];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y", ltm);
    return buffer;
}

int next(int **values, bool **ispassed, int m, int n, int x, int y, int x0, int y0, int sum, int start_time, int filecapacity) // returns a code: 0 for continuing, 1 for "User won", -1 for "User lost"
{
    if (x == m && y == n && values[x][y] * 2 == sum)
    {
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0, filecapacity);
        return 1;
    }
    // if (values[x][y] == 0 || ispassed[x][y])
    //     return 0;
    ispassed[x][y] = 1;
    int x2 = x, y2 = y, ch, i = 0, screenupdatespersecond = 7;
    while (1)
    {
        clearScreen();
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0, filecapacity);
        cout << "\nSum of the blocks: " << sum << "\nTime: "
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
        {
            clearScreen();
            printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0, filecapacity);
            return -1; // exit the loop
        }
        if (x2 == x0 && y2 == y0)
            break;
        if (!values[x2][y2] || ispassed[x2][y2])
        {
            x2 = x;
            y2 = y;
            continue;
        }
        int flag = next(values, ispassed, m, n, x2, y2, x, y, sum + values[x2][y2], start_time, filecapacity);
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
        // int i = 1;
        bool valid = 1, brk = 0;
        string choice, name, list = "List of maps:\n", mapchoice, mapaddress;
        user player;
        ifstream mapfile, allmaps("Maps/allmaps.txt");
        vector<string> maps = getusers("Maps/allmaps.txt");
        for (int i = 0; i < maps.size(); i++)
            list += "\n\t" + to_string(i + 1) + ". " + maps[i];
        allmaps.close();
        getinput(choice, "Playground\n" + menu2, 0, 2);
    choose_map:
        mapfile.close();
        switch (stoi(choice))
        {
        case 0:
            return;
        case 1:
            // while (allmaps >> name)
            // {
            //     list += "\n\t" + to_string(i) + ". " + name;
            //     maps.push_back(name);
            //     i++;
            // }
            getinput(mapchoice, list + "\n\t0. Back", 0, maps.size());
            if (mapchoice == "0")
                continue;
            mapfile.open("Maps/" + maps[stoi(mapchoice) - 1] + ".txt");
            break;
        case 2:
            while (!mapfile.is_open())
            {
                clearScreen();
                if (!valid && mapaddress != "")
                    cout << red << "The file doesn't exist" << reset;
                cout << "\nEnter a path to a custom map or enter 0 to go back: ";
                valid = 0;
                getline(cin, mapaddress);
                if (mapaddress == "0")
                {
                    brk = 1;
                    break;
                }
                mapfile.open(mapaddress);
            }
            if (brk)
                continue;
            break;
        }
        allmaps.close();
        brk = 0;
        while (player.name == "0" || player.name == "" || player.name == "allusers")
        {
            clearScreen();
            cout << "\nPlease enter a username or enter 0 to go back: ";
            getline(cin, player.name);
            if (player.name == "0")
            {
                brk = 1;
                break;
            }
        }
        if (brk)
            goto choose_map;
        int m, n, x = 1, y = 1, filecapacity = 1;
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
            {
                mapfile >> values[i][j];
                int digitscout = log10(values[i][j]) + 1;
                if (digitscout > filecapacity)
                    filecapacity = digitscout;
            }
        mapfile.close();
        int start = time(0);
        // printmap(values, ispassed, 1, 1, 0, 0, m + 2, n + 2, 0);
        int sum = 0, ch, x2 = x, y2 = y, x0 = x, y0 = y;
        bool won = next(values, ispassed, m, n, x, y, 1, 1, values[1][1], start, filecapacity) == 1;
        int end = time(0);

        cout << endl;
        if (won)
            cout << green << "YOU WON" << red << "!!!" << reset << endl;
        else
            cout << red << "YOU LOST" << green << "!!!" << reset << endl;
        cout << "Time: " << end - start << endl;
        player.lastwintime = end - start;
        updateusers(player, won);
        // update history
        ofstream temp("Stats/temp.txt");
        ifstream hist("Stats/History.txt");
        temp << "Date: " << Date() << "\n";
        temp << "User Name: " << player.name << "\n";
        temp << "Map: " << ((choice == "1") ? maps[stoi(mapchoice) - 1] : mapaddress) << "\n";
        temp << "Time: " << end - start << "\n";
        temp << "Result: " << (won ? "Win" : "Loose") << "\n"
             << "\n";
        int sizecontrol = 0;
        string line;
        while (getline(hist, line) && sizecontrol++ < 54)
            temp << line << endl;
        temp.close();
        hist.close();
        remove("Stats/History.txt");
        rename("Stats/temp.txt", "Stats/History.txt");
        updateleaderboard(player);
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
    
    //filling the maze
    mazefiller(maze , row , column , length , lowV , highV , leastW, mostW);
    cout << '\n';
    // for(int i = 1 ; i < row + 1; i++)
    // {
    //     for(int l = 1; l < column + 1; l++)
    //     {
    //         cout << maze[i][l] << ' ';
    //     }
    //     cout << '\n';
    // }
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
    vector<string> users = getusers();
    string name;

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
    cout << "\nPress any key to coninue: ";
    _getch();
    showUsers();
}

void leaderboard()
{
    // clearScreen();
    // cout << "Finding best players...";
    // vector<user> players = getusersdata();
    // sort(players.begin(), players.end(), compare);
    // clearScreen();
    // cout << "Leaderboard:\n\n";
    // int size = players.size();
    // for (int i = min(3, size) - 1; i >= 0; i--)
    //     cout << min(3, size) - i << ". " << players[i].name << endl;
    // cout << "\nPress any key to coninue: ";
    // _getch();
    clearScreen();
    vector<string> leaders = getusers("Stats/Leaderboard.txt");
    cout << "Leaderboard:\n\n";
    for (int i = 0; i < leaders.size(); i++)
        cout << '\t' << i + 1 << ". " << leaders[i] << endl;
    cout << "\nPress any key to coninue: ";
    _getch();
}
void mazepathmaker(int**& maze, int row , int column, int rowin , int columnin, int togo , int& flag)
{
    // checks if there is a wall in the way of advancing
    if(maze[rowin][columnin] == 0)
    {
        return;
    }
    // makes this block a wall so we can't go through this block again in the path
    maze[rowin][columnin] = 0;
    string Slength;
    // checks if the path has been found
    if(togo == 0 && rowin == row && columnin == column)
    {
        // with changing the flag we make sure we get out of the function in total
        flag = 1;
        return;
    }
    // a boolean for the case we can't reach the final house from this block anymore
    if(togo < row + column - rowin - columnin)
    {
        maze[rowin][columnin] = 1;
        return;
    }
    // a vector to make randomness
    vector<int> arr;
    for(int i = 1; i < 5; i++)
    {
        arr.push_back(i);
    }
    // pure randomness :))
    std::random_device rd;
    std::default_random_engine rng(rd());
    shuffle(arr.begin() , arr.end() ,rng);
    // choosing the path options randomly
    // pathfinding
    for(int i = 0; i < 4; i++)
    {
        switch (arr[i])
        {
        case 1:
            mazepathmaker(maze , row , column , rowin + 1 , columnin , togo - 1 , flag);
            if(flag == 1)
            {
                return;
            }
            break;
        case 2:
            mazepathmaker(maze , row , column , rowin - 1 , columnin , togo - 1 , flag);
            if(flag == 1)
            {
                return;
            }
            break;
        case 3:
            mazepathmaker(maze , row , column , rowin , columnin + 1 , togo - 1 , flag);
            if(flag == 1)
            {
                return;
            }
            break;
        default:
            mazepathmaker(maze , row , column , rowin , columnin - 1 , togo - 1 , flag);
            if(flag == 1)
            {
                return;
            }
            break;
        }
    }
    // if the path hasn't been found yet the path does not go 
    //through this block of the maze with the path given till now at all
    maze[rowin][columnin] = 1;
}

void mazefiller(int**& maze , int row , int column , int length , int lowV , int highV , int leastW , int mostW)
{
    srand(time(0));
    // finalblock is the sum for the final block of the path
    int finalblock = 0;
    // generates a random number for the aount of walls in the maze
    int walls = rand() % (mostW - leastW + 1) + leastW;
    vector<int> mazeparts;
    vector<int> mazepathparts;
    // walls
    for(int i = 0; i < walls; i++)
    {
        mazeparts.push_back(0);
    }
    // values for the blocks in the path
    for(int i = 0; i < length; i++)
    {
        int part;
        part = randint(lowV , highV);
        mazepathparts.push_back(part);
    }
    // values for the blocks that are not walls and are not in the path
    for(int i = 0; i < row * column - walls - length; i++)
    {
        int part;
        part = randint(lowV, highV);
        mazeparts.push_back(part);
    }

    std::random_device rd;
    std::default_random_engine rng(rd());
    // shuffling the vector so walls are in a random place in the maze
    shuffle(mazeparts.begin(), mazeparts.end() , rng);
    // filling time :)
    for(int i = 1; i <= row; i++)
    {
        for(int l = 1; l <= column; l++)
        {
            if(maze[i][l] == 0 && i + l != row + column)
            {
                maze[i][l] = mazepathparts[mazepathparts.size() - 1];
                finalblock += mazepathparts[mazepathparts.size() - 1];
                mazepathparts.pop_back();
            }
            else if(i + l == column + row)
            {
                maze[i][l] = finalblock;
            }
            else
            {
                maze[i][l] = mazeparts[mazeparts.size() - 1];
                mazeparts.pop_back();
            }
        }
    }
}

int randint(int floor, int ceil)
{
    bool zeroin = floor * ceil <= 0;
    int dif = ceil - floor + 1;
    int res = rand() % dif + floor - zeroin;
    return res + (res >= 0) * zeroin;
}