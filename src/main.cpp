#include "canvas.h"
#include "game.h"
#include "gl.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#define PIXELSIZE 20
#define SIZE 20
#define SPEED 10
Canvas *canvas;

using namespace std;

void run() {
  canvas->recalcBuffers();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(canvas->programID);
  glUniformMatrix4fv(canvas->MatrixID, 1, GL_FALSE, &canvas->MVP[0][0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, canvas->foodSnakePositionBuffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                  sizeof(GLfloat) * 3 * (canvas->game->snake()->size() + 1),
                  canvas->foodSnakePosition);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, canvas->foodSnakeColorBuffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                  sizeof(GLfloat) * 3 * (canvas->game->snake()->size() + 1),
                  canvas->foodSnakeColor);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_POINTS, 0, canvas->game->snake()->size() + 1);

  glDisableVertexAttribArray(0);

  glfwSwapBuffers(canvas->window);
  glfwPollEvents();
  canvas->calcInput();

  canvas->currentTime = high_resolution_clock::now();
  canvas->dur = canvas->currentTime - canvas->lastTime;
  if (canvas->dur.count() >= 1000.0 / canvas->game->speed()) {
    if (!(get<0>(canvas->direction) + get<0>(canvas->game->direction()) == 0 &&
          get<1>(canvas->direction) + get<1>(canvas->game->direction()) == 0))
      canvas->game->setDirection(canvas->direction);
    canvas->game->step();
    canvas->lastTime = high_resolution_clock::now();
  }
}
int main(int argc, char *argv[]) {
  Game game(SIZE, SIZE, SPEED);
  canvas = new Canvas(&game, SIZE, SIZE);
  canvas->init();
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(run, 0, 1);
#else
  while (glfwGetKey(canvas->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(canvas->window) == 0) {
    run();
  }
#endif

  return 0;
}
