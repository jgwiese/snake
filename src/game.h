#ifndef GAME_H
#define GAME_H

#include <deque>
#include <iostream>
#include <tuple>

using namespace std;
class Game {
public:
  Game(int width, int height, int speed);
  tuple<int, int> position();
  tuple<int, int> direction();
  tuple<int, int> food();
  deque<tuple<int, int>> *snake();
  int speed();

  void setPosition(tuple<int, int> position);
  void setDirection(tuple<int, int> direction);
  void step();

private:
  int width, height, _speed;
  tuple<int, int> _position;
  tuple<int, int> _food;
  tuple<int, int> _direction;

  deque<tuple<int, int>> *_snake;
  void correctPosition();
  bool validPosition(tuple<int, int> position);
  void resetGame();
  void positionFood();
};

#endif // GAME_H
