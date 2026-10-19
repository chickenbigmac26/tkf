#include <raylib.h>
#include <stdio.h>

// gcc cgof.c -o ~/programing/c/cgof $(pkg-config --cflags --libs raylib) &&
// ~/programing/c/cgof

#define width 1000
#define height 1000
#define size 2

typedef unsigned char Grid[width / size][width / size];

int const gwidth = width / size;
int const gheight = height / size;

unsigned char paused = 0;

Grid gridA;
Grid gridB;

void draw(Grid grid) {
  Color awhite = {244, 24, 74, 255};
  Color ablack = { 0, 2 ,2 , 20 };
  for (int x = 0; x < gwidth; x++)
    for (int y = 0; y < gwidth; y++)
      if (grid[x][y] == 1) {
        DrawRectangle(x * size, y * size, size, size, awhite);
      } else {
        DrawRectangle(x * size, y * size, size, size, ablack);
      }
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
              // exclude self
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

void mouseDraw(Grid grid, unsigned char state) {
  int mousegx = GetMousePosition().x / size;
  int mousegy = GetMousePosition().y / size;

  paused = 1;

  grid[mousegx][mousegy] = state;
}

int main(void) {
  InitWindow(width, height, "cgol");
 
  Grid *oldg = &gridA;
  Grid *newg = &gridB;

  for (int x = 0; x < gwidth; x++) {
    gridA[x][gheight/2]=1;
  }
  
  /* gridA[1][3] = 1; */
  /* gridA[2][3] = 1; */
  /* gridA[3][3] = 1; */
  /* gridA[3][2] = 1; */
  /* gridA[2][1] = 1; */
 

  SetTargetFPS(60);
  while (!WindowShouldClose()) {

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      mouseDraw(*oldg, 1);
    } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      mouseDraw(*oldg, 0);
    } else {
      paused = 0;
    }
   
    
    BeginDrawing();

    //ClearBackground(BLACK);
    draw(*oldg);


    EndDrawing();
     if (paused == 0) {
      update(*oldg, *newg);
      // swap pointers of newg and oldg
      Grid *temp = oldg;
      oldg = newg;
      newg = temp;
    }
  }

  CloseWindow();

  return 0;
}
