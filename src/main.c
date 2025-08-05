#include "raylib.h"

enum Shape { I, J, L, O, S, Z, T };

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 20
#define MATRIX_SCALE 60

int main() {
  int matrix[200];
  int colors[8] = {0x000000FF, 0x00FFFFFF, 0x0000FFFF, 0xFFA500,
                   0xFFFF00FF, 0x00FF00FF, 0x800080FF, 0xFF0000FF};

  InitWindow(600, 1200, "Tetris Clone");
  if (!IsWindowReady())
    return 1;

  SetTargetFPS(60);
  HideCursor();

  for (int i = 0; i < 200; ++i) {
    matrix[i] = colors[0];
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);

    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
      for (int x = 0; x < MATRIX_WIDTH; ++x) {
        DrawRectangle(GetScreenWidth() / 2 + x * MATRIX_SCALE -
                          MATRIX_WIDTH * MATRIX_SCALE / 2,
                      GetScreenHeight() / 2 + y * MATRIX_SCALE -
                          MATRIX_HEIGHT * MATRIX_SCALE / 2,
                      MATRIX_SCALE, MATRIX_SCALE,
                      GetColor(matrix[y * MATRIX_WIDTH + x]));
      }
    }

    EndDrawing();
  }

  CloseWindow();
}
