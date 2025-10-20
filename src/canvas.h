#ifndef CANVAS_H
#define CANVAS_H

#include "game.h"
#include "gl.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <tuple>

#define PIXELSIZE 20

using namespace std;
using namespace std::chrono;

class Canvas {
public:
  Canvas(Game *game, int width, int height);
  void init();
  void run();
  void recalcBuffers();
  void calcInput();

  Game *game;
  int **board;

  GLFWwindow *window;

  int width, height;

  GLfloat *foodSnakePosition;
  GLfloat *foodSnakeColor;

  glm::mat4 MVP;
  GLuint programID;
  GLuint MatrixID;
  GLuint foodSnakePositionBuffer;
  GLuint foodSnakeColorBuffer;

  high_resolution_clock::time_point lastTime;
  high_resolution_clock::time_point currentTime;
  duration<double, milli> dur;
  int fpsCounter;

  tuple<int, int> direction;
};

#endif // CANVAS_H
