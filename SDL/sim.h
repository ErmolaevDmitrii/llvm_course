#ifndef SIM_H
#define SIM_H

#define FIELD_X_SIZE 100
#define FIELD_Y_SIZE 20

#define CELL_WIDTH 5

#define SIM_X_SIZE FIELD_X_SIZE * CELL_WIDTH
#define SIM_Y_SIZE FIELD_Y_SIZE * CELL_WIDTH

#ifndef __sim__
void simInit();
void app();
void simExit();
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand(void);
#endif // __sim__

#endif // SIM_H