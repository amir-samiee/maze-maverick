#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <windows.h>
#include <fstream>
#include <vector>
#include <iomanip>
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
void mazepathmaker(int **& maze , int row , int column , int rowin , int columnin , int togo , int& flag);
//function to fill the maze
void mazefiller(int **& maze, int row, int column, int length , int lowV , int highV , int leastW, int mostW);
//function for generating random int excluding 0
int randint(int floor, int ceil);
//function for getting input util its a valid int input
void getintinput(string interact, string& input, int& output);
//function that solves a map
void mazesolver(int** maze, int**& copymaze , string**& path , int row , int column , int rowin , int coulumnin, int togo , int& flag , int sum);
void clearScreen();                                             // this function has been declared to clear the screen on both windows and linux
bool isInteger(string s);                                       // returns 1 if a string can be converted to an integer, otherwise 0
void getinput(string &input, string options, int from, int to); // shows a list of options and gets input until user inputs a valid choice. the choice should be an integer from integer "from" to integer "to"
void createNewMap();
void mazesolving();
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
        mazesolving();
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
    clearScreen();
    cout << interact;
    cin >> input;
    while(!isvalidint(input, result))
    {
        clearScreen();
        cout << interact << "\n" <<"Invalid entry. pls try again: \n";
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
    string choice , Scolumn , Srow , Slength;
    int mapdif ,flag = 0 , column , row , length , **maze , reseter = 1;
reset_dif:
    //gets map difficulty from user
    getintinput("Create a new map: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    while(mapdif > 2 || mapdif < 0)
    {
        getintinput("Pls enter a valid choice: \n1. Easy\n2. Hard\n0. Back\nPls enter your choice: ", choice, mapdif);
    }
    if(mapdif == 0)
    {
        return;
    }
    // gets maze height from user 
    getintinput("Pls enter maze height or enter 0 to restart the process: \n", Srow, row);
    while(row < 2 && row != 0)
    {
        getintinput("Pls enter maze height (it cannot be less than 2) or enter 0 to restart the process: \n", Srow, row);
    }
    if(row == 0)
    goto reset_dif;
    // gets maze width from user
    getintinput("Pls enter maze width or enter 0 to restart the process: \n", Scolumn, column);
    while(column < 2 && column != 0)
    {
        getintinput("Pls enter maze width (it cannot be less than 2) or enter 0 to restart the process: \n", Scolumn, column);
    }
    if(column == 0)
    goto reset_dif;
    //length for basic maze
    length = column + row - 2;
    // checks the difficulty option for advanced path making
    if(mapdif == 2)
    {
        // gets length of path for the maze from user
        getintinput("Pls enter the length of the path or enter 0 to restart the process:\n", Slength, length);
        while(length < row + column - 2 || length > row * column - 1 || length % 2 != (row + column) % 2 && length != 0)
        {
            cout << "Such a path cannot exist. \nTry again: \n";
            getintinput( "Pls enter the length of the path or enter 0 to restart the process:\n", Slength, length);
        }
    }
    if(length == 0)
    goto reset_dif;
    clearScreen();
    cout << yellow <<"You won't be able to reset the settings for the maze from this point forward\n" << reset <<"Enter 0 to restart the process:";
    cin >> reseter;
    if(reseter == 0)
    goto reset_dif;
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
    int lowV = -3 , highV = 3, leastW = 2, mostW = 5 , filecapacity = 2;
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
    for (int i = 1; i < row + 1; i++)
            for (int j = 1; j < column + 1; j++)
            {
                int digitscout = log10(fabs(maze[i][j])) + 1;
                if (digitscout > filecapacity)
                    filecapacity = digitscout;
            }

    //filling the maze
    mazefiller(maze , row , column , length , lowV , highV , leastW, mostW);
    cout << "Maze has been made, Press any Key to return to menu: ";
    _getch();
    return;
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

void mazesolving()
{
    clearScreen();
    int row , column, length, mapdif, sum = 0, flag = 0 , **maze , **copymaze , filecapacity = 2;
    string **path;
    cin >> row >> column >> length;
    maze = new int*[row + 2];
    copymaze = new int*[row + 2];
    path = new string*[2 * (row + 2)];
    for(int i = 0; i < row + 2; i++)
    {
        maze[i] = new int[column + 2];
        copymaze[i] = new int[column + 2];
        path[2 * i] = new string[column + 2];
        path[2 * i + 1] = new string[column + 2];
    }
    for(int i = 0; i < row + 2; i++)
    {
        for(int l = 0; l < column + 2; l++)
        {
            if(i == 0 || i == row + 1 || l == 0 || l == column + 1)
            {
                maze[i][l] = 0;
                copymaze[i][l] = 0;
                path[2 * i][l] = "";
                path[2 * i + 1][l] = "";
            }
            else
            {
                cin >> maze[i][l];
                int digitscout = log10(fabs(maze[i][l])) + 2;
                if (digitscout > filecapacity)
                {
                    filecapacity = digitscout;
                }
                if(maze[i][l] == 0)
                {
                    copymaze[i][l] = 0;
                }
                else
                {
                    copymaze[i][l] = 1;
                }
                path[2 * i][l] = " ";
                path[2 * i + 1][l] = " ";
            }
        }
    }
    mazesolver(maze , copymaze , path , row , column , 1 , 1 , length , flag , sum);
    for(int i = 1; i < row + 1; i++)
    {
        for(int l = 1; l < column + 1; l++)
        {
            if(copymaze[i][l] == 2)
            {
                cout << green;
            }
            cout << left << setw(filecapacity) << maze[i][l] << cyan << left << setw(filecapacity) << path[2 * i][l] << reset;
        }
        cout << endl;
        for(int l = 1; l < column + 1; l++)
        {
            cout << cyan << left << setw(2 * filecapacity) << path[2 * i + 1][l] << reset;
        }
        cout << endl;
    }
    cout << "\nPress any key to coninue: ";
    _getch();
    return;
}

void mazesolver(int** maze, int**& copymaze , string**& path , int row , int column , int rowin , int columnin, int togo , int& flag , int sum)
{
    if(maze[rowin][columnin] == 0 || copymaze[rowin][columnin] == 2)
    {
        return;
    }
    sum += maze[rowin][columnin];
    copymaze[rowin][columnin] = 2;
    if(togo == 0 && rowin == row && columnin == column && sum == 2 * maze[row][column])
    {
        flag = 1;
        return;
    }
    if(togo < row + column - rowin - columnin)
    {
        copymaze[rowin][columnin] = 1;
        return;
    }
    if(copymaze[rowin - 1][columnin] != 0 && copymaze[rowin - 1][columnin] != 2)
    {
        path[2 * rowin - 1][columnin] = "|";
        mazesolver(maze , copymaze , path , row , column , rowin - 1 , columnin , togo - 1 , flag , sum);
        if(flag == 1)
        {
            return;
        }
        path[2 * rowin - 1][columnin] = " ";
    }
    if(copymaze[rowin][columnin + 1] != 0 && copymaze[rowin][columnin + 1] != 2)
    {
        path[2 * rowin][columnin] = "_";
        mazesolver(maze , copymaze , path , row , column , rowin , columnin + 1 , togo - 1 , flag , sum);
        if(flag == 1)
        {
            return;
        }
        path[2 * rowin][columnin] = " ";
    }
    if(copymaze[rowin + 1][columnin] != 0 && copymaze[rowin + 1][columnin] != 2)
    {
        path[2 * rowin + 1][columnin] = "|";
        if(copymaze[rowin + 1][columnin] != 0 && copymaze[rowin + 1][columnin] != 2)
        mazesolver(maze , copymaze , path , row , column , rowin + 1 , columnin , togo - 1 , flag , sum);
        if(flag == 1)
        {
            return;
        }
        path[2 * rowin + 1][columnin] = " ";
    }
    if(copymaze[rowin][columnin - 1] != 0 && copymaze[rowin][columnin - 1] != 2)
    {
        path[rowin * 2][columnin - 1] = "_";
        mazesolver(maze , copymaze , path , row , column , rowin , columnin - 1 , togo - 1 , flag , sum);
        if(flag == 1)
        {
            return;
        }
        path[rowin * 2][columnin - 1] = " ";
    }
    sum -= maze[rowin][columnin];
    copymaze[rowin][columnin] = 1;
}