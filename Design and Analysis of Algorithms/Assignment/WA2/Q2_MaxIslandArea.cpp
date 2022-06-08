#include <stdio.h>
#include <stdlib.h>
#include <cmath>

int MaxIsland();
int FindIsland(int row, int col);

int main(){
 
    int maxIsland = MaxIsland();
    printf("%d\n", maxIsland);

    return 0;

}

// Set the Island as a globle variable.
int grid[8][13] = {{0,0,1,0,0,0,0,1,0,0,0,0,0}, {0,0,0,0,0,0,0,1,1,1,0,0,0},
                   {0,1,1,0,1,0,0,0,0,0,0,0,0}, {0,1,0,0,1,1,0,0,1,0,1,0,0},
                   {0,1,0,0,1,1,0,0,1,1,1,0,0}, {0,0,0,0,0,0,0,0,0,0,1,0,0},
                   {0,0,0,0,0,0,0,1,1,1,0,0,0}, {0,0,0,0,0,0,0,1,1,0,0,0,0}};

int FindIsland(int row, int col) {

     // The basic case is that reach the boundary, begin from zero and stop at length-1
    if ((row < 0 || row >= 8) || (col < 0 || col >= 13)) {
        return 0;
    }
    if (grid[row][col]==0){
        return 0;
    }

    grid[row][col] = 0;

    // 1 is the first point you visit
    // Then recursively visited the vertex by the four directions.
    return (1 + FindIsland(row + 1,col) + FindIsland(row, col - 1)) + FindIsland(row, col + 1) + FindIsland(row - 1, col) ;
}


int MaxIsland() {
    int area = 0;
    // Traversal all the grids in the map
    for (int row = 0; row < 8; row++) {
        for (int col = 0;col < 13; col++) {
            int temp = FindIsland(row,col);
            // If the temp is larger than the previous island area
            area = area>temp ? area:temp;
        }
    }
    return area;
}
