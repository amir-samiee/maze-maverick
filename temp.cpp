#include <iostream>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <ctype.h>
using namespace std;
void clearScreen()
{
}
void printmap(int **values, bool **ispassed, int x, int y, int x0, int y0, int m, int n, int t)
{
}

int main()
{
    return 0;
}
// this version of next can update the screen after a certain amount of time but duo to number of operations, doesn't work as expected
bool next(int **values, bool **ispassed, int m, int n, int x, int y, int x0, int y0, int sum, int start_time)
{
    if (x == m && y == n && values[x][y] * 2 == sum)
        return 1;
    if (values[x][y] == 0 || ispassed[x][y])
        return 0;
    ispassed[x][y] = 1;
    int x2 = x, y2 = y, ch, i = 0, screenupdatespersecond = 7;
    while (1)
    {
        clearScreen();
        printmap(values, ispassed, x, y, x0, y0, m + 2, n + 2, 0);
        cout << sum << endl
             << time(0) - start_time;
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
                return 0;      // exit the loop
            if (x2 == x0 && y2 == y0)
                break;
            if (next(values, ispassed, m, n, x2, y2, x, y, sum + values[x2][y2], start_time))
                return 1;
            x2 = x;
            y2 = y;
        }
        else
        {
            Sleep(1000 / screenupdatespersecond);
            if (i++ == screenupdatespersecond)
                i = 0;
        }
    }
    ispassed[x][y] = 0;
    return 0;
}