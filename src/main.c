#include "raylib.h"

enum Shape { I, J, L, O, S, Z, T };

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 20
#define MATRIX_SCALE 60

int matrix[200];
int colors[8] = {0x000000FF, 0x00FFFFFF, 0x0000FFFF, 0xFFA500FF,
                 0xFFFF00FF, 0x00FF00FF, 0x800080FF, 0xFF0000FF};

int I_shape[16] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int O_shape[16] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
int T_shape[16] = {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
int S_shape[16] = {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
int Z_shape[16] = {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0};
int J_shape[16] = {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
int L_shape[16] = {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0};

int main() {
  InitWindow(600, 1200, "Tetris Clone");
  if (!IsWindowReady())
    return 1;

  SetTargetFPS(60);
  HideCursor();

  // Initialize matrix
  for (int i = 0; i < 200; ++i) {
    matrix[i] = colors[0];
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);

    // Prepare rectangle
    int size = MATRIX_SCALE;
    int offsetX = GetScreenWidth() / 2 - MATRIX_WIDTH * size / 2;
    int offsetY = GetScreenHeight() / 2 - MATRIX_HEIGHT * size / 2;

    // Draw matrix cells
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
      for (int x = 0; x < MATRIX_WIDTH; ++x) {
        Rectangle rect = {x * size + offsetX, y * size + offsetY, size, size};
        DrawRectangleRec(rect, GetColor(matrix[y * MATRIX_WIDTH + x]));
      }
    }

    EndDrawing();
  }

  CloseWindow();
}
