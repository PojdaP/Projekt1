#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
class BoardGame
{
  string name;
  int time;
  int age;
  int min_players;
  int max_players;
  double avg_rating;
  double weight;
public:
  BoardGame() = delete;
  BoardGame( vector<string> dane )
  {
    this->name = dane.at( 3 );
    this->min_players = stoi( dane.at( 4 ) );
    this->max_players = stoi( dane.at( 4 ) );
    this->time = stoi( dane.at( 6 ) );
    this->age = stoi( dane.at( 14 ) );
    this->avg_rating = stod( dane.at( 10 ) );
    this->weight = stod( dane.at( 19 ) );
  }

  string getName();
  int getAge();
  int getMax();
  int getMin();
  int getTime();
  double getRating();
  double getWeight();
  friend ostream& operator<<( ostream& os, const BoardGame& x );
};
