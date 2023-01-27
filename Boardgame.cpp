#include "BoardGame.h"

ostream& operator<<( ostream& os, const BoardGame& x )// operator << for a board game
{
  os << "Name: " << x.name << " | Playtime: " << x.time
    << " | Age: " << x.age << " | Min players " << x.min_players << " | Max players " << x.max_players 
    << " | Average rating: " << x.avg_rating << " | Weight: " << x.weight << endl;
  return os;
}

string BoardGame::getName() {//returning private values
  return this->name;
}

int BoardGame::getMax() {
  return this->max_players;
}

int BoardGame::getTime() {
  return this->time;
}

double BoardGame::getRating() {
  return this->avg_rating;
}

double BoardGame::getWeight() {
  return this->weight;
}

int BoardGame::getMin() {
  return this->min_players;
}

int BoardGame::getAge() {
  return this->age;
}