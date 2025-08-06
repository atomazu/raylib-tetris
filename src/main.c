#include "raylib.h"
#include <stdlib.h>

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 20
#define MATRIX_SCALE 60
#define BACKGROUND_COLOR 0x000000FF
#define GRID_COLOR 0x111111FF

int matrix[200];
int colors[8] = {0,          0x00FFFFFF, 0x0000FFFF, 0xFFA500FF,
                 0xFFFF00FF, 0x00FF00FF, 0x800080FF, 0xFF0000FF};

enum ShapeType { I, J, L, O, S, Z, T };
enum ShapeRotation { UP, RIGHT, DOWN, LEFT };
struct Shape {
  enum ShapeType type;
  enum ShapeRotation rot;
  int minos[16];
  int posX;
  int posY;
};

void drawShape(struct Shape shape) {
  for (int i = 0; i < 4; ++i) {
    for (int l = 0; l < 4; ++l) {
      if (shape.minos[i * 4 + l]) {
        int offset = shape.posX + shape.posY * MATRIX_WIDTH;
        matrix[offset + i * MATRIX_WIDTH + l] = shape.type;
      }
    }
  }
}

struct Shape shapes[7] = {
    {I, UP, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {J, UP, {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {L, UP, {0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {O, UP, {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {S, UP, {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {Z, UP, {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
    {T, UP, {0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0}};

struct Shape currentShape;
struct Shape *lockedShapes;
int lockedShapesSize = 0;

void lockShape(struct Shape shape) {
  lockedShapes =
      realloc(lockedShapes, (lockedShapesSize + 1) * sizeof(struct Shape));
  lockedShapes[lockedShapesSize] = shape;
  lockedShapesSize++;
}

int main() {
  InitWindow(600, 1200, "Tetris Clone");
  if (!IsWindowReady())
    return 1;

  SetTargetFPS(60);
  HideCursor();

  currentShape = shapes[1 + random() % 7];

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(BACKGROUND_COLOR));

    // Clear matrix
    for (int i = 0; i < 200; ++i) {
      matrix[i] = 0;
    }

    // Draw all locked shapes
    for (int i = 0; i < lockedShapesSize; ++i) {
      drawShape(lockedShapes[i]);
    }

    // Movement
    if (IsKeyDown(KEY_L)) {
      currentShape.posX += 1;
    } else if (IsKeyDown(KEY_H)) {
      currentShape.posX -= 1;
    } else if (IsKeyPressed(KEY_ENTER)) {
      lockShape(currentShape);
      currentShape = shapes[1 + random() % 7];
    }

    // Draw current shape
    drawShape(currentShape);

    // Prepare rectangle
    int size = MATRIX_SCALE;
    int offsetX = GetScreenWidth() / 2 - MATRIX_WIDTH * size / 2;
    int offsetY = GetScreenHeight() / 2 - MATRIX_HEIGHT * size / 2;

    // Draw matrix
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
      for (int x = 0; x < MATRIX_WIDTH; ++x) {
        Rectangle rect = {x * size + offsetX, y * size + offsetY, size, size};
        DrawRectangleLinesEx(rect, 1, GetColor(GRID_COLOR));

        int type = matrix[y * MATRIX_WIDTH + x];
        if (type) {
          DrawRectangleRec(rect, GetColor(colors[type]));
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();
}
