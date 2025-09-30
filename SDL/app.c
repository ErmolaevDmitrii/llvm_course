#include "sim.h"

int game_field_1[FIELD_X_SIZE][FIELD_Y_SIZE];
int game_field_2[FIELD_X_SIZE][FIELD_Y_SIZE];

int (*game_field     )[FIELD_X_SIZE][FIELD_Y_SIZE];
int (*prev_game_field)[FIELD_X_SIZE][FIELD_Y_SIZE];

void draw_rectangle(int x, int y) {
  if((*game_field)[x][y]) {
    for(int j = y * CELL_WIDTH; j < ((y + 1) * CELL_WIDTH); ++j) {
      for(int i = x * CELL_WIDTH; i < ((x + 1) * CELL_WIDTH); ++i) {
        simPutPixel(i, j, 0xFFFFFFFF);
      }
    }
  }
  else {
    for(int j = y * CELL_WIDTH; j < ((y + 1) * CELL_WIDTH); ++j) {
      for(int i = x * CELL_WIDTH; i < ((x + 1) * CELL_WIDTH); ++i) {
        simPutPixel(i, j, 0xFF000000);
      }
    }
  }
  return;
}

void game_step() {
  int neighbors_count;

  for(int y = 0; y < FIELD_Y_SIZE; ++y) {
    for (int x = 0; x < FIELD_X_SIZE; ++x) {
      neighbors_count = 0;

      if (x > 0) {
        if (y > 0)
          neighbors_count += (*prev_game_field)[x - 1][y - 1];

          neighbors_count += (*prev_game_field)[x - 1][y    ];

        if (y < FIELD_Y_SIZE - 1)
          neighbors_count += (*prev_game_field)[x - 1][y + 1];
      }

      if (x < FIELD_X_SIZE - 1) {
        if (y > 0)
          neighbors_count += (*prev_game_field)[x + 1][y - 1];

          neighbors_count += (*prev_game_field)[x + 1][y    ];

          if(y < FIELD_Y_SIZE - 1)
          neighbors_count += (*prev_game_field)[x + 1][y + 1];
      }

      if(y > 0)
          neighbors_count += (*prev_game_field)[x    ][y - 1];

      if(y < FIELD_Y_SIZE - 1)
          neighbors_count += (*prev_game_field)[x    ][y + 1];

      if((*prev_game_field)[x][y]) {
        (*game_field)[x][y] = (neighbors_count == 2) || (neighbors_count == 3);
      }
      else {
        (*game_field)[x][y] = (neighbors_count == 3);
      }
    }
  }
}

void app(void) {
  game_field      = &game_field_1;
  prev_game_field = &game_field_2;

  for (int y = 0; y < FIELD_Y_SIZE; ++y) {
    for(int x = 0; x < FIELD_X_SIZE; ++x) {
      (*prev_game_field)[x][y] = simRand() % 2;
    }
  }

  while(1) {
    game_step();
    for (int y = 0; y < FIELD_Y_SIZE; ++y) {
      for(int x = 0; x < FIELD_X_SIZE; ++x) {
        draw_rectangle(x, y);
      }
    }

    int (*swap)[FIELD_X_SIZE][FIELD_Y_SIZE];
    swap = game_field;
    game_field = prev_game_field;
    prev_game_field = swap;

    simFlush();
  }
}