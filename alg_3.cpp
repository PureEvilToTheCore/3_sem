#include <iostream>
#define rows 6
#define cols 6
using namespace std;

int labirint[rows][cols] = {
    {0, 0, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0}
};

int result[rows][cols];
int temp[rows][cols];

void printArray(int arr[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void CopyArray(int source[][cols], int destination[][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

int Count(int array[rows][cols]) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (array[i][j] == 2) count++;
        }
    }
    return count;
}

void ZerosArray(int array[][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array[i][j] = 0;
        }
    }
}

bool WayIsSolve(int array[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        if ((array[i][0] == 2) || (array[0][i] == 2) || (array[i][cols-1] == 2) || (array[rows-1][i] == 2)) return true;
    }
    return false;
}

void ShortestWay(int xo, int yo, int array[rows][cols]) {
    if (xo < 0 || xo >= rows || yo < 0 || yo >= cols || temp[xo][yo] == 2) {
        return;
    }
    temp[xo][yo] = 2;
    if ((Count(result) == 0 || (Count(result) > Count(temp))) && WayIsSolve(temp)) {
        if (Count(temp) < ((rows - xo) || (cols - yo))) return;
        CopyArray(temp, result);
        ZerosArray(temp);
        return;
    }
    if (yo + 1 < cols && array[xo][yo + 1] == 0) ShortestWay(xo, yo + 1, labirint);
    if (xo + 1 < rows && array[xo + 1][yo] == 0) ShortestWay(xo + 1, yo, labirint);
    if (yo - 1 >= 0 && array[xo][yo - 1] == 0) ShortestWay(xo, yo - 1, labirint);
    if (xo - 1 >= 0 && array[xo - 1][yo] == 0) ShortestWay(xo - 1, yo, labirint);
}


int main() {
    printArray(labirint);
    cout << "------" << endl;
    ShortestWay(4, 3, labirint);
    printArray(result);
    return 0;
}