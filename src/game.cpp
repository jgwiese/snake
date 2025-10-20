#include "game.h"

Game::Game(int width, int height, int speed) {
  srand(time(NULL));

  this->width = width;
  this->height = height;
  this->_speed = speed;
  _position = tuple<int, int>();
  _direction = tuple<int, int>();
  _food = tuple<int, int>();

  _snake = new deque<tuple<int, int>>();
  _snake->push_front(_position);

  positionFood();
}

void Game::step() {
  _position = tuple<int, int>(get<0>(position()) + get<0>(direction()),
                              get<1>(position()) + get<1>(direction()));
  correctPosition();

  if (validPosition(_position)) {
    if (_position == _food) {
      positionFood();
      _snake->push_front(_position);
    } else {
      _snake->push_front(_position);
      _snake->pop_back();
    }
  } else {
    resetGame();
  }
}

void Game::correctPosition() {
  if (get<0>(_position) < -width / 2) {
    get<0>(_position) = width / 2 - 1;
  } else if (get<0>(_position) > width / 2 - 1) {
    get<0>(_position) = -width / 2;
  } else if (get<1>(_position) < -height / 2) {
    get<1>(_position) = height / 2 - 1;
  } else if (get<1>(_position) > height / 2 - 1) {
    get<1>(_position) = -height / 2;
  }
}

bool Game::validPosition(tuple<int, int> position) {
  for (int i = 0; i < _snake->size() - 1; i++) {
    if (get<0>(position) == get<0>(_snake->at(i)) &&
        get<1>(position) == get<1>(_snake->at(i))) {
      return false;
    }
  }
  return true;
}

void Game::resetGame() {
  _snake->clear();
  _snake->push_front(_position);
}

void Game::positionFood() {
  _food = tuple<int, int>((rand() % width - (width / 2)),
                          (rand() % height - (height / 2)));
  while (!validPosition(_food)) {
    _food = tuple<int, int>((rand() % width - (width / 2)),
                            (rand() % height - (height / 2)));
  }
}

tuple<int, int> Game::position() { return *_snake->begin(); }

tuple<int, int> Game::direction() { return _direction; }

tuple<int, int> Game::food() { return _food; }

deque<tuple<int, int>> *Game::snake() { return _snake; }

int Game::speed() { return _speed; }

void Game::setPosition(tuple<int, int> position) { this->_position = position; }

void Game::setDirection(tuple<int, int> direction) {
  this->_direction = direction;
}
