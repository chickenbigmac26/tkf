#include <raylib.h>
#include <stdio.h>

// gcc cgof.c -o ~/programing/c/cgof $(pkg-config --cflags --libs raylib) &&
// ~/programing/c/cgof

#define width 1000
#define height 1000
#define size 10

typedef unsigned char Grid[width / size][width / size];

int const gwidth = width / size;
int const gheight = height / size;

Grid gridA;
Grid gridB;

void draw(Grid grid) {
  for (int x = 0; x < gwidth; x++)
    for (int y = 0; y < gwidth; y++)
      if (grid[x][y] == 1)
        DrawRectangle(x * size, y * size, size, size, DARKGRAY);
}

//
// give in the old grid and writes the udated old grid into the new grid
void update(Grid const oldg, Grid newg) {

  // for loop over each square in grid

  for (int x = 0; x < gwidth; x++) {
    for (int y = 0; y < gheight; y++) {

      // count neighbours
      short int neighbours = 0;
      // loop over neighbours of square
      for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
          int lx = x + dx;
          int ly = y + dy;

          // check if neighbour possition is actualy in array
          if (lx >= 0 && lx < gwidth) {
            if (ly >= 0 && ly < gheight) {
              // look at neighbour state and increment neighbours by 1 if it is
              // alive
              if (oldg[lx][ly] == 1 && !((dx == 0) && (dy == 0))) {
                neighbours = neighbours + 1;
              }
            }
          }
        }
      }

      // rules to live or die
      short int newState = 0;
      short int currentState = oldg[x][y];

      if (currentState == 1 && neighbours < 2) {
        newState = 0;
      } else if (currentState == 1 && neighbours > 3) {
        newState = 0;
      } else if (currentState == 1 && neighbours == 2 || neighbours == 3) {
        newState = 1;
      } else if (currentState == 0 && neighbours == 3) {
        newState = 1;
      } else {
        newState = 0;
      }

      newg[x][y] = newState;
    }
  }
}

int main(void) {
  InitWindow(width, height, "cgol");
  int midx = gwidth / 2;
  int midy = gheight / 2;

  Grid *oldg = &gridA;
  Grid *newg = &gridB;
  gridA[1][3] = 1;
  gridA[2][3] = 1;
  gridA[3][3] = 1;
  gridA[3][2] = 1;
  gridA[2][1] = 1;
  // gridA[midx+2][midy+2] = 1;

  SetTargetFPS(10);
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);
    draw(*oldg);
    update(*oldg, *newg);

    EndDrawing();

    // swap pointers of newg and oldg
    Grid *temp = oldg;
    oldg = newg;
    newg = temp;
  }

  CloseWindow();

  return 0;
}
