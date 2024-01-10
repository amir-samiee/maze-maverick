#include <iostream>
#include <algorithm>
#include <random>
// #include <windows.h>
// #include <cstdlib>
#include <fstream>
#include <iomanip>
#include <vector>
// #include <cstdio>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <ctype.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
int kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized)
    {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
#endif
using namespace std;
// COLORS
const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");
// FUNCTIONS

void mazepathmaker(int **&maze, int row, int column, int rowin, int columnin, int togo, int &flag);                                      // function to find a random path
void mazefiller(int **&maze, int row, int column, int length, int lowV, int highV, int leastW, int mostW);                               // function to fill the maze
int randint(int floor, int ceil);                                                                                                        // function for generating random int excluding 0
void getintinput(string interact, string &input, int &output, bool flag);                                                                // function for getting input util its a valid int input
void mazesolver(int **maze, int **&copymaze, char **&path, int row, int column, int rowin, int coulumnin, int togo, int &flag, int sum); // function that solves a map
void clearScreen();                                                                                                                      // this function has been declared to clear the screen on windows
bool isInteger(string s);                                                                                                                // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to, string indexerrormessage = "Out of Index!");                              // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"
void createNewMap();                                                                                                                     // creates a new map --maze-- (part 1)
void mazesolving();                                                                                                                      // gets and solves a maze
void playground();                                                                                                                       // the interactive game part (part 2)
void showHistory();                                                                                                                      // shows the history of the games (part 4)
void showUsers();                                                                                                                        // shows the users (part 5)
void leaderboard();                                                                                                                      // shows the leader users (part 6)
void resetstats();                                                                                                                       // clears user and games history data but keeps the maps
void clearmaps();                                                                                                                        // clears all maps
string mtos(int **maze, int row, int column, int filecapacity = 1, bool removeEdges = 1);                                                // maze to string convertor so we can add it to string parameter of input functions

string menu0 =
    cyan + "\n __  __            ______ ______   __  __       __      __ ______  _____   _____  _____  _  __"
           "\n|  \\/  |    /\\    |___  /|  ____| |  \\/  |    /\\\\ \\    / /|  ____||  __ \\ |_   _|/ ____|| |/ /" +
    red + "\n| \\  / |   /  \\      / / | |__    | \\  / |   /  \\\\ \\  / / | |__   | |__) |  | | | |     | ' / "
          "\n| |\\/| |  / /\\ \\    / /  |  __|   | |\\/| |  / /\\ \\\\ \\/ /  |  __|  |  _  /   | | | |     |  <  "
          "\n| |  | | / ____ \\  / /__ | |____  | |  | | / ____ \\\\  /   | |____ | | \\ \\  _| |_| |____ | . \\ " +
    cyan + "\n|_|  |_|/_/    \\_\\/_____||______| |_|  |_|/_/    \\_\\\\/    |______||_|  \\_\\|_____|\\_____||_|\\_\\" +
    reset +
    "\n\n1. Create a New Map"
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
    "\n7. Reset stats"
    "\n8. Clear Maps"
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
    while (1)
    {
        string choice1;
        getinput(choice1, menu0, 0, 8);
        switch (stoi(choice1))
        {
        case 1:
            createNewMap();
            break;
        case 2:
            playground();
            break;
        case 3:
            mazesolving();
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
        case 7:
            resetstats();
            break;
        case 8:
            clearmaps();
            break;
        default:
            cout << endl
                 << yellow + "Exiting program...\n\n" + reset;
            return 0;
        }
    }
}

void clearScreen()
{
    system("clear||cls");
}

bool isInteger(string s)
{
    for (int i = 1; i < s.size(); i++)
        if (!isdigit(s[i]))
            return 0;
    if (!(isdigit(s[0]) || s[0] == '-'))
        return 0;
    return 1;
}

string mtos(int **maze, int row, int column, int filecapacity, bool removeEdges)
{
    string res = "";
    for (int i = removeEdges; i < row + removeEdges; i++)
    {
        for (int j = removeEdges; j < column + removeEdges; j++)
        {
            string f = to_string(maze[i][j]);
            int cap = filecapacity - f.size();
            // cout << filecapacity << ' ' << cap << endl;
            res += string((cap > 0 ? cap : 0), ' ') + f + ' ';
        }
        res += "\n";
        // cout << right << setw(filecapacity) << maze[i][j] << ' ';
        // cout << endl;
    }
    return res;
}

void getintinput(string interact, string &input, int &result, bool flag)
{
    if (!flag)
        clearScreen();
    cout << interact;
    // cin >> input;
    getline(cin, input);
    // while (!isvalidint(input, result))
    while (!isInteger(input))
    {
        clearScreen();
        cout << interact << "\n"
             << red << "Invalid entry. Please try again: " << reset;
        getline(cin, input);
    }
    result = stoi(input);
}

void getinput(string &input, string options, int from, int to, string indexerrormessage)
{
    bool indexerror = 0, typeerror = 0, emptystring = 0;
    do
    {
        clearScreen();
        cout << options << endl
             << ((indexerror) ? red + indexerrormessage + "\nPlease enetr a number between " + to_string(from) + " and " + to_string(to) + reset + "\n" : "")
             << ((typeerror) ? red + "Input wasn't a number!\nPlease enetr a number between " + to_string(from) + " and " + to_string(to) + reset + "\n" : "")
             << string(2 * (1 - indexerror - typeerror), '\n')
             << "Enter your choice: ";
        indexerror = typeerror = 0;
        // cin >> input;
        getline(cin, input);
        if (input == "")
            emptystring = 1;
        else
        {
            emptystring = 0;
            if (isInteger(input))
            {
                if (input.size() > to_string(to).size() || stoi(input) > to || stoi(input) < from)
                    if (input != "0" && input != "-0")
                        indexerror = 1;
            }
            else
                typeerror = 1;
        }

    } while (indexerror || typeerror || emptystring);
}

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
            cout << setw(filecapacity) << right << values[i][j] << reset << ' ';
        }
        cout << endl;
    }
}

struct user
{
    string name = "";
    int games = 0;
    int wins = 0;
    int lastwintime = 0;
    int totaltime = 0;
};

vector<string> getnames(string filename = "Users/allusers.txt") // returns the stored names in the given file
{
    ifstream namesfile(filename);
    vector<string> names;
    string name;
    while (getline(namesfile, name))
        names.push_back(name);
    return names;
}
user formuser(string name) // gets a username in string format and returns the user format
{
    ifstream userfile("Users/" + name + ".txt");
    user opened;
    opened.name = name;
    // getline(usersfile, line);
    userfile.ignore(7);
    userfile >> opened.games;
    // getline(userfile, opened.games);
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
vector<user> getusersdata(string filename = "Users/allusers.txt") // returns a vector including the user format of all uses
{
    vector<string> users = getnames(filename);
    vector<user> players;
    for (auto u : users)
        players.push_back(formuser(u));
    return players;
}

void updateusers(user &player, bool won) // when a game ends, this function compares the player with the leader players and updates the leaderboard
{
    vector<string> users = getnames();
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
        usersfile << player.name
                  << endl;
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

int next(int **values, bool **ispassed, int m, int n, int x, int y, int x0, int y0, int sum, int start_time, int filecapacity, int &lastupdate) // this is the recursive function of motion in the playground. it returns a code: 0 for continuing, 1 for "User won", -1 for "User lost"
{
    if (x == m && y == n && values[x][y] * 2 == sum)
    {
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0, filecapacity);
        return 1;
    }
    // if (!values[x][y] || ispassed[x][y])
    //     return 0;
    // if (values[x][y] == 0 || ispassed[x][y])
    //     return 0;
    ispassed[x][y] = 1;
    int x2 = x, y2 = y, ch, i = 0, screenupdatespersecond = 7, j = time(0);
    while (1)
    {
        clearScreen();
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0, filecapacity);
        cout << "\nSum of the blocks: " << sum << "\nTime: "
             << time(0) - start_time << "\r";
        lastupdate = time(0);
    dontupdatescreen:
        if (kbhit())
        {
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
            else
                goto dontupdatescreen;
        }
        else
        {
            if (time(0) - lastupdate >= 1)
            {
                cout << "Time: "
                     << time(0) - start_time << "\r";
                lastupdate = time(0);
                // continue;
            }
            // else
            goto dontupdatescreen;
        }
        if (x2 == x0 && y2 == y0)
            break;

        if (ispassed[x2][y2] || !(values[x2][y2] || (x2 == m && y2 == n)))
        {
            x2 = x;
            y2 = y;
            goto dontupdatescreen;
            // continue;
        }
        int flag = next(values, ispassed, m, n, x2, y2, x, y, sum + values[x2][y2], start_time, filecapacity, lastupdate);
        if (flag)
            return flag;
        x2 = x;
        y2 = y;
    }
    ispassed[x][y] = 0;
    return 0;
}

void playground()
{
    while (1)
    {
        string choice, name, list = "List of maps:\n", mapchoice, mapaddress;
        user player;
        ifstream mapfile, allmaps("Maps/allmaps.txt");
        vector<string> maps = getnames("Maps/allmaps.txt");
        for (int i = 0; i < maps.size(); i++)
            list += "\n\t" + to_string(i + 1) + ". " + maps[i];
        allmaps.close();
        getinput(choice, "Playground:\n" + menu2, 0, 2);
    choose_map:
        mapfile.close();
        bool valid = 1, brk = 0;
        switch (stoi(choice))
        {
        case 0:
            return;
        case 1:
            getinput(mapchoice, list + "\n\t0. Back", 0, maps.size());
            if (mapchoice == "0")
                continue;
            mapfile.open("Maps/" + maps[stoi(mapchoice) - 1] + ".txt");
            break;
        case 2:
            while (!mapfile.is_open() || mapaddress.substr(0, 5) == "Users" || mapaddress.substr(0, 5) == "Stats")
            {
                clearScreen();
                if (!valid && mapaddress != "")
                    cout << red << "Invalid file!!" << reset;
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
            if (player.name == "allusers")
                cout << red << "You can't choose this username!!" << reset << endl;
            else
                cout << endl;
            cout << "Please enter a username or enter 0 to go back: ";
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
                int digitscout = log10(abs(values[i][j])) + (values[i][j] < 0) + 1;
                if (digitscout > filecapacity)
                    filecapacity = digitscout;
            }
        mapfile.close();
        int start = time(0);
        int sum = 0, ch, x2 = x, y2 = y, x0 = x, y0 = y, lastupdate = time(0);
        bool won = next(values, ispassed, m, n, x, y, 1, 1, values[1][1], start, filecapacity, lastupdate) == 1;
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
        getch();
        // return;
    }
}

template <class t>
bool isin(t value, vector<t> vec)
{
    for (int i = 0; i < vec.size(); i++)
        if (value == vec[i])
            return 1;
    return 0;
}

void createNewMap()
{
reset_dif:
    string choice, Scolumn, Srow, Slength, reseter = "1";
    int mapdif, flag = 0, column, row, length, **maze;
    // gets map difficulty from user

    // getintinput("Create a new map: \n1. Easy\n2. Hard\n0. Back\nPlease enter your choice: ", choice, mapdif, 0);
    // while (mapdif > 2 || mapdif < 0)
    //     getintinput("Please enter a valid choice: \n1. Easy\n2. Hard\n0. Back\nPlease enter your choice: ", choice, mapdif, 0);
    getinput(choice, "Creste a New Map:\n" + menu1, 0, 2);
    mapdif = stoi(choice);
    if (mapdif == 0)
        return;

    // gets maze height from user
    // getintinput("Please enter maze height or enter 0 to restart the process: \n", Srow, row, 0);
    // while (row < 2 && row != 0)
    //     getintinput("Please enter maze height (it cannot be less than 2) or enter 0 to restart the process: \n", Srow, row, 0);
    getinput(Srow, "Please enter maze height or enter 0 to restart the process: ", 2, 2000000000, "Not Accepted");
    row = stoi(Srow);
    if (row == 0)
        goto reset_dif;
    // gets maze width from user
    // getintinput("Please enter maze width or enter 0 to restart the process: \n", Scolumn, column, 0);
    // while (column < 2 && column != 0)
    //     getintinput("Please enter maze width (it cannot be less than 2) or enter 0 to restart the process: \n", Scolumn, column, 0);
    getinput(Scolumn, "Please enter maze width or enter 0 to restart the process: ", 2, 2000000000, "Not Accepted");
    column = stoi(Scolumn);
    if (column == 0)
        goto reset_dif;
    // length for basic maze
    length = column + row - 2;
    // checks the difficulty option for advanced path making
    if (mapdif == 2)
    {
        // gets length of path for the maze from user
        getintinput("Please enter the length of the path or enter 0 to restart the process:\n", Slength, length, 0);
        while (length < row + column - 2 || length > row * column - 1 || length % 2 != (row + column) % 2 && length != 0)
        {
            clearScreen();
            cout << red << "Such a path cannot exist. \nTry again: \n"
                 << reset;
            getintinput("Please enter the length of the path or enter 0 to restart the process:\n", Slength, length, 1);
        }
    }
    if (length == 0)
        goto reset_dif;
    clearScreen();
    cout << yellow << "You won't be able to reset the settings for the maze from this point forward\n"
         << reset << "Enter 0 to restart the process or something else to continue:";
    // cin >> reseter;
    getline(cin, reseter);
    if (reseter == "0")
        goto reset_dif;
    // setting the maze up
    maze = new int *[row + 2];
    for (int i = 0; i < row + 2; i++)
        maze[i] = new int[column + 2];
    for (int i = 0; i < row + 2; i++)
    {
        if (i == 0 || i == row + 1)
            for (int l = 0; l < column + 2; l++)
                maze[i][l] = 0;
        else
        {
            for (int l = 0; l < column + 2; l++)
            {
                if (l == 0 || l == column + 1)
                    maze[i][l] = 0;
                else
                    maze[i][l] = 1;
            }
        }
    }
    // finding a random path for maze
    mazepathmaker(maze, row, column, 1, 1, length, flag);
    string SlowV, ShighV, SleastW, SmostW;
    int lowV = -3, highV = 3, leastW = 2, mostW = 5, filecapacity = 2;
    if (mapdif == 2)
    {
        // inputs the min value of blocks
        getintinput("Please enter your choice of min value of block: ", SlowV, lowV, 0);
        // inputs the max value of blocks
        getintinput("Please enter your choice of max value of block: ", ShighV, highV, 0);
        while (lowV > highV || (lowV == highV && lowV == 0))
            getintinput("Please enter your choice of max value of block (it can't be less than the min value): ", ShighV, highV, 0);
        // inputs the least amount of walls
        getintinput("Please enter your choice of min amount of walls: ", SleastW, leastW, 0);
        while (leastW < 0 || leastW > row * column - length - 1)
            getintinput("Please enter your choice of min amount of walls \n(it can't be less than 0 or more than amount of block available): ", SleastW, leastW, 0);
        // inputs the most amount of walls
        getintinput("Please enter your choice of max amount of walls: ", SleastW, mostW, 0);
        while (leastW > mostW)
            getintinput("Please enter your choice of max amount of walls (it can't be less than the min amount of walls): ", SleastW, mostW, 0);
    }
    // filling the maze
    mazefiller(maze, row, column, length, lowV, highV, leastW, mostW);
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
        {
            // int digitscout = log10(abs(maze[i][j])) + 2;
            int digitscout = to_string(maze[i][j]).size();
            // cout << maze[i][j] << ' ' << digitscout << endl;
            if (digitscout > filecapacity)
                filecapacity = digitscout;
        }
    // getch();

    string mapname = "";
    vector<string> allmapsnames = getnames("Maps/allmaps.txt");
    while (mapname == "" || mapname == "allmaps" || isin(mapname, allmapsnames))
    {
        clearScreen();
        if (mapname == "allmaps" || isin(mapname, allmapsnames))
            cout << red << "You can't choose this name!!" << reset << endl;
        else
            cout << endl;
        cout << mtos(maze, row, column, filecapacity);
        // cout << filecapacity << endl;
        cout << "Maze has been made. Please enter a name for it or 0 to cancel: ";
        getline(cin, mapname);
        if (mapname == "0")
            goto reset_dif;
        // return;
    }
    ofstream mapfile("Maps/" + mapname + ".txt");
    mapfile << row << ' ' << column << endl;
    mapfile << mtos(maze, row, column, filecapacity);
    // for (int i = 1; i <= row; i++)
    // {
    //     for (int j = 1; j <= column; j++)
    //         mapfile << setw(filecapacity) << maze[i][j] << ' ';
    //     mapfile << endl;
    // }
    mapfile.close();
    ofstream allmapsfile("Maps/allmaps.txt", ios::app);
    allmapsfile << mapname
                << endl;
    allmapsfile.close();
    cout << green << "\nDone! Press any key to continue: " << reset;
    getch();
    goto reset_dif;
    // return;
}

void showHistory()
{
    clearScreen();
    ifstream historyfile("Stats/History.txt");
    string line;
    cout << "History:\n\n";
    while (getline(historyfile, line))
        cout << line << endl;
    historyfile.close();
    cout << "\nPress any key to coninue: ";
    getch();
}

void showUsers()
{
    vector<string> users = getnames();
    while (1)
    {
        clearScreen();
        string name;
        bool nameerror = 0;
        do
        {
            clearScreen();
            cout << "Users:\n\n";
            for (int i = 0; i < users.size(); i++)
                cout << '\t' << users[i] << endl;
            cout << (nameerror ? red + "Invalid name!\nPlease enter a name included in the list\n" + reset : "\n\n")
                 << "Enter a name or enter 0 to go back: ";
            // cin >> name;
            getline(cin, name);
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
        clearScreen();
        cout << "Name: " << name << endl;
        while (getline(userfile, line))
            cout << line << endl;
        cout << "\nPress any key to coninue: ";
        getch();
    }
}

void leaderboard()
{
    // the following commented code can be used to reset the leaderboard from the start and not with updating after each game. it's not efficient but is useful for when we have lost the leaderboard's file or data.
    // clearScreen();
    // cout << "Finding best players...";
    // vector<user> players = getusersdata();
    // sort(players.begin(), players.end(), compare);
    // reverse(players.begin(), players.end());
    // clearScreen();
    // cout << "Leaderboard:\n\n";
    // int size = players.size();
    // for (int i = 0; i < min(3, size); i++)
    // {
    //     user leader = players[i];
    //     cout << string(4, ' ') << i + 1 << ". " << leader.name << endl
    //          << string(7, ' ') << "Wins: " << leader.wins << endl
    //          << string(7, ' ') << "Total time: " << leader.totaltime << endl;
    // }
    // cout << "\nPress any key to coninue: ";
    // getch();

    clearScreen();
    vector<string> leaders = getnames("Stats/Leaderboard.txt");
    cout << "Leaderboard:\n\n";
    for (int i = 0; i < leaders.size(); i++)
    {
        user leader = formuser(leaders[i]);
        cout << string(4, ' ') << i + 1 << ". " << leader.name << endl
             << string(7, ' ') << "Wins: " << leader.wins << endl
             << string(7, ' ') << "Total time: " << leader.totaltime << endl;
    }
    cout << "\nPress any key to coninue: ";
    getch();
}

void resetstats()
{
    clearScreen();
    cout << "Reset Stats:\n\n"
         << "This action clears any data related to users and games history but keeps the maps"
         << "\nEnter yes to confirm the action. Enter anything else to cancel and go back: ";
    string choice;
    getline(cin, choice);
    if (choice != "yes")
    {
        cout << red + "no changes applied" + reset;
        cout << "\nPress any key to coninue: ";
        getch();
        return;
    }
    vector<string> users = getnames();
    for (string u : users)
    {
        string filename = "Users/" + u + ".txt";
        remove(filename.c_str());
    }
    ofstream file;
    file.open("Users/allusers.txt");
    file.close();
    file.open("Stats/History.txt");
    file.close();
    file.open("Stats/Leaderboard.txt");
    file.close();
    cout << green << "Cleared successfully!!" << reset;
    cout << "\nPress any key to coninue: ";
    getch();
}

void clearmaps()
{
    clearScreen();
    cout << "Clear Maps:\n\n"
         << "This action clears all the maps"
         << "\nEnter yes to confirm the action. Enter anything else to cancel and go back: ";
    string choice;
    getline(cin, choice);
    if (choice != "yes")
    {
        cout << red + "no changes applied" + reset;
        cout << "\nPress any key to coninue: ";
        getch();
        return;
    }
    vector<string> maps = getnames("Maps/allmaps.txt");
    for (string map : maps)
    {
        string filename = "Maps/" + map + ".txt";
        remove(filename.c_str());
    }
    ofstream file;
    file.open("Maps/allmaps.txt");
    file.close();
    cout << green << "Cleared successfully!!" << reset;
    cout << "\nPress any key to coninue: ";
    getch();
}

void mazepathmaker(int **&maze, int row, int column, int rowin, int columnin, int togo, int &flag)
{
    // checks if there is a wall in the way of advancing
    if (maze[rowin][columnin] == 0)
        return;
    // makes this block a wall so we can't go through this block again in the path
    maze[rowin][columnin] = 0;
    string Slength;
    // checks if the path has been found
    if (togo == 0 && rowin == row && columnin == column)
    {
        // with changing the flag we make sure we get out of the function in total
        flag = 1;
        return;
    }
    // a boolean for the case we can't reach the final house from this block anymore
    if (togo < row + column - rowin - columnin)
    {
        maze[rowin][columnin] = 1;
        return;
    }
    // a vector to make randomness
    vector<int> arr;
    for (int i = 1; i < 5; i++)
        arr.push_back(i);
    // pure randomness :))
    random_device rd;
    default_random_engine rng(rd());
    shuffle(arr.begin(), arr.end(), rng);
    // choosing the path options randomly
    // pathfinding
    for (int i = 0; i < 4; i++)
    {
        switch (arr[i])
        {
        case 1:
            mazepathmaker(maze, row, column, rowin + 1, columnin, togo - 1, flag);
            if (flag == 1)
                return;
            break;
        case 2:
            mazepathmaker(maze, row, column, rowin - 1, columnin, togo - 1, flag);
            if (flag == 1)
                return;
            break;
        case 3:
            mazepathmaker(maze, row, column, rowin, columnin + 1, togo - 1, flag);
            if (flag == 1)
                return;
            break;
        default:
            mazepathmaker(maze, row, column, rowin, columnin - 1, togo - 1, flag);
            if (flag == 1)
                return;
            break;
        }
    }
    // if the path hasn't been found yet the path does not go
    // through this block of the maze with the path given till now at all
    maze[rowin][columnin] = 1;
}

void mazefiller(int **&maze, int row, int column, int length, int lowV, int highV, int leastW, int mostW)
{
    srand(time(0));
    // finalblock is the sum for the final block of the path
    int finalblock = 0;
    // generates a random number for the aount of walls in the maze
    int walls = rand() % (mostW - leastW + 1) + leastW;
    vector<int> mazeparts;
    vector<int> mazepathparts;
    // walls
    for (int i = 0; i < walls; i++)
        mazeparts.push_back(0);
    // values for the blocks in the path
    for (int i = 0; i < length; i++)
    {
        int part;
        part = randint(lowV, highV);
        finalblock += part;
        while (i == length - 1 && finalblock == 0) // not efficient
        {
            finalblock -= part;
            part = randint(lowV, highV);
            finalblock += part;
        }
        mazepathparts.push_back(part);
    }
    // values for the blocks that are not walls and are not in the path
    for (int i = 0; i < row * column - walls - length; i++)
    {
        int part;
        part = randint(lowV, highV);
        mazeparts.push_back(part);
    }

    random_device rd;
    default_random_engine rng(rd());
    // shuffling the vector so walls are in a random place in the maze
    shuffle(mazeparts.begin(), mazeparts.end(), rng);
    // filling time :)
    for (int i = 1; i <= row; i++)
    {
        for (int l = 1; l <= column; l++)
        {
            if (maze[i][l] == 0 && i + l != row + column)
            {
                maze[i][l] = mazepathparts[mazepathparts.size() - 1];
                mazepathparts.pop_back();
            }
            else if (i + l == column + row)
                maze[i][l] = finalblock;
            else
            {
                maze[i][l] = mazeparts[mazeparts.size() - 1];
                mazeparts.pop_back();
            }
        }
    }
}

int randint(int floor, int ceil) // returns a random number between integers floor and ceil that will never be 0
{
    bool zeroin = floor * ceil <= 0;
    int dif = ceil - floor + 1;
    int res = rand() % dif + floor - zeroin;
    return res + (res >= 0) * zeroin;
}

void mazesolving()
{
    while (1)
    {
        clearScreen();
        string choice, list = "List of maps:\n", mapchoice, mapaddress;
        ifstream mapfile, allmaps("Maps/allmaps.txt");
        vector<string> maps = getnames("Maps/allmaps.txt");
        for (int i = 0; i < maps.size(); i++)
            list += "\n\t" + to_string(i + 1) + ". " + maps[i];
        allmaps.close();
        getinput(choice, "Solve a maze:\n" + menu2, 0, 2);
    dontcontinue:
        mapfile.close();
        bool valid = 1, brk = 0;
        switch (stoi(choice))
        {
        case 0:
            return;
        case 1:
            getinput(mapchoice, list + "\n\t0. Back", 0, maps.size());
            if (mapchoice == "0")
                continue;
            mapfile.open("Maps/" + maps[stoi(mapchoice) - 1] + ".txt");
            break;
        case 2:
            while (!mapfile.is_open() || mapaddress.substr(0, 5) == "Users" || mapaddress.substr(0, 5) == "Stats")
            {
                clearScreen();
                if (!valid && mapaddress != "")
                    cout << red << "Invalid file!!" << reset;
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
        int row, column, length, mapdif, sum = 0, flag = 0, **maze, **copymaze, filecapacity = 2;
        char **path;
        mapfile >> row >> column;
        string input;
        // cin >> row >> column >> length;
        maze = new int *[row + 2];
        copymaze = new int *[row + 2];
        path = new char *[2 * (row + 2)];
        for (int i = 0; i < row + 2; i++)
        {
            maze[i] = new int[column + 2];
            copymaze[i] = new int[column + 2];
            path[2 * i] = new char[column + 2];
            path[2 * i + 1] = new char[column + 2];
        }
        for (int i = 0; i < row + 2; i++)
        {
            for (int l = 0; l < column + 2; l++)
            {
                if (i == 0 || i == row + 1 || l == 0 || l == column + 1)
                {
                    maze[i][l] = 0;
                    copymaze[i][l] = 0;
                    path[2 * i][l] = '\0';
                    path[2 * i + 1][l] = '\0';
                }
                else
                {
                    mapfile >> maze[i][l];
                    int digitscout = log10(fabs(maze[i][l])) + 2;
                    if (digitscout > filecapacity)
                        filecapacity = digitscout;
                    if (maze[i][l] == 0)
                        copymaze[i][l] = 0;
                    else
                        copymaze[i][l] = 1;
                    path[2 * i][l] = ' ';
                    path[2 * i + 1][l] = ' ';
                }
            }
        }
        mapfile.close();
        clearScreen();
        // for (int i = 1; i < row + 1; i++)
        // {
        //     for (int j = 1; j < column + 1; j++)
        //         cout << right << setw(filecapacity) << maze[i][j] << ' ';
        //     cout << endl;
        // }
        getintinput(mtos(maze, row, column, filecapacity) + "Enter the length of path: ", input, length, 1);
        clearScreen();
        cout << yellow << "Calculating, please wait..." << reset << endl;
        if (length % 2 == (row + column) % 2 && length <= row * column - 1 - !(row % 2 || column % 2))
            mazesolver(maze, copymaze, path, row, column, 1, 1, length, flag, sum);
        clearScreen();
        for (int i = 1; i < row + 1; i++)
        {
            for (int l = 1; l < column + 1; l++)
            {
                if (copymaze[i][l] == 2)
                    cout << green;
                cout << right << setw(filecapacity) << maze[i][l] << cyan << right << setw(filecapacity) << string((filecapacity == 1 ? 1 : filecapacity - 1), path[2 * i][l]) << reset;
            }
            cout << endl;
            for (int l = 1; l < column + 1; l++)
                cout << right << cyan << setw(filecapacity) << path[2 * i + 1][l] << string(filecapacity, ' ') << reset;
            cout << endl;
        }
        // cout << filecapacity << endl;
        cout << endl;
        if (flag == 0)
            cout << yellow << "There's no path with the given length in this maze" << reset;
        cout << "\nPress any key to coninue: ";
        getch();
        goto dontcontinue;
        // return;
    }
}

void mazesolver(int **maze, int **&copymaze, char **&path, int row, int column, int rowin, int columnin, int togo, int &flag, int sum)
{
    if (maze[rowin][columnin] == 0 || copymaze[rowin][columnin] == 2)
        return;
    // if (togo < 0 || togo > row * column - 1 - !(row % 2 || column % 2)) // samiee added
    //     return;                                                         // samiee added
    sum += maze[rowin][columnin];
    copymaze[rowin][columnin] = 2;
    if (togo == 0 && rowin == row && columnin == column && sum == 2 * maze[row][column])
    {
        flag = 1;
        return;
    }
    if (togo < row + column - rowin - columnin)
    {
        copymaze[rowin][columnin] = 1;
        return;
    }
    if (copymaze[rowin - 1][columnin] != 0 && copymaze[rowin - 1][columnin] != 2)
    {
        path[2 * rowin - 1][columnin] = '|';
        mazesolver(maze, copymaze, path, row, column, rowin - 1, columnin, togo - 1, flag, sum);
        if (flag == 1)
            return;
        path[2 * rowin - 1][columnin] = ' ';
    }
    if (copymaze[rowin][columnin + 1] != 0 && copymaze[rowin][columnin + 1] != 2)
    {
        path[2 * rowin][columnin] = '_';
        mazesolver(maze, copymaze, path, row, column, rowin, columnin + 1, togo - 1, flag, sum);
        if (flag == 1)
            return;
        path[2 * rowin][columnin] = ' ';
    }
    if (copymaze[rowin + 1][columnin] != 0 && copymaze[rowin + 1][columnin] != 2)
    {
        path[2 * rowin + 1][columnin] = '|';
        if (copymaze[rowin + 1][columnin] != 0 && copymaze[rowin + 1][columnin] != 2)
            mazesolver(maze, copymaze, path, row, column, rowin + 1, columnin, togo - 1, flag, sum);
        if (flag == 1)
            return;
        path[2 * rowin + 1][columnin] = ' ';
    }
    if (copymaze[rowin][columnin - 1] != 0 && copymaze[rowin][columnin - 1] != 2)
    {
        path[rowin * 2][columnin - 1] = '_';
        mazesolver(maze, copymaze, path, row, column, rowin, columnin - 1, togo - 1, flag, sum);
        if (flag == 1)
            return;
        path[rowin * 2][columnin - 1] = ' ';
    }
    sum -= maze[rowin][columnin];
    copymaze[rowin][columnin] = 1;
}