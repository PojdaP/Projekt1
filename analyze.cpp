#include "analyze.h"
#include "readdata.h"
#include "BoardGame.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

void sortbyplaytime( vector<BoardGame>& game )
{
  sort( game.begin(), game.end(), []( BoardGame g1, BoardGame g2 ) { return g1.getTime() < g2.getTime(); } );//sorting by time growingly
}

void sortbymaxplayers( vector<BoardGame>& game )
{
  sort( game.begin(), game.end(), []( BoardGame g1, BoardGame g2 ) { return g1.getMax() < g2.getMax(); } );//sorting by max players number growingly
}

void sortbyavgrating( vector<BoardGame>& game )
{
  sort( game.begin(), game.end(), []( BoardGame g1, BoardGame g2 ) { return g1.getRating() > g2.getRating(); } );//sorting by rating in descending order
}

void printboardgames( vector<BoardGame>& vec )//printing vector of borad games
{
  vector<BoardGame>::iterator ptr;
  ptr = vec.begin();
  while( ptr != vec.end() )//until the end of the vector
  {
    cout << *ptr++;//print the BoardGame and increase ptr so its pointing to the next BoardGame
  }
}

void analyse_players_age( vector<BoardGame>& games )
{
  int max = (*max_element( games.begin(), games.end(), []( BoardGame g1, BoardGame g2 ) { return g1.getAge() < g2.getAge(); })).getAge();
  int* table = new int[ max + 1 ]{};
  for( vector<BoardGame>::iterator ptr = games.begin(); ptr != games.end(); ptr++ )
  {
    table[( *ptr ).getAge()]++;
  }

  cout << "Percentage of board games with a certain age restriction:" << endl;
  for( int i = 0; i <= max; i++ )
  {
    cout << setprecision( 2 ) << fixed;
    if( table[i] != 0 )
    {
      cout << "age " << i << ":\t" << ( double )table[i] / games.size() * 100 << "%" << endl;
    }
  }
  delete [ ]table;
}

void top10( vector<BoardGame> games )
{
  sortbyavgrating( games );
  vector<BoardGame>   sub( &games[0], &games[9] );
  printboardgames( sub );
}


void analyse_players_number( vector<BoardGame>& games )
{
  sortbymaxplayers( games );
  int max = games[games.size() - 1].getMax();
  int* table = new int[max + 1]{};

  for( vector<BoardGame>::iterator ptr = games.begin(); ptr != games.end(); ptr++ )
  {
    for( int i = ( *ptr ).getMin(); i <= ( *ptr ).getMax(); i++ )
      table[i]++;
  }
  int max_elem = *max_element( table, table + max + 1 );
  int index = find( table, table + max, max_elem ) - table;

  cout << "Most optimal number of players: ";
  cout << index << endl;
  delete [ ]table;
}

void avg_med_playtime( vector<BoardGame>& games1, vector<BoardGame>& games2 )
{
  sortbyavgrating( games1 );
  sortbyavgrating( games2 );
  vector<BoardGame> sub1( &games1[0], &games1[9] );
  vector<BoardGame> sub2( &games2[0], &games2[9] );
  int total_playtime1 = accumulate( sub1.begin(), sub1.end(), 0,
    []( int total, BoardGame& g1 ) {
      return total + g1.getTime();
    } );
  int total_playtime2 = accumulate( sub2.begin(), sub2.end(), 0,
    []( int total, BoardGame& g2 ) {
      return total + g2.getTime();
    } );
  sortbyplaytime( sub1 );
  sortbyplaytime( sub2 );

  cout << "Average playtime for hundred games in year 2017 with highest ratings: " << ( double )total_playtime1 / 10 << endl;
  cout << "Median playtime for hundred games in year 2017 with highest ratings: " << sub1[5].getTime() << endl;
  cout << "Average playtime for hundred games in year 2018 with highest ratings: " << ( double )total_playtime2 / 10 << endl;
  cout << "Median playtime for hundred games in year 2018 with highest ratings: " << sub2[5].getTime() << endl;

}

void choose_boardgame( vector<BoardGame>& games, int time, int age, double weight, int players )
{
  char input;
  int running = 1;
  vector<BoardGame> filtered_games;

  copy_if( games.begin(), games.end(), back_inserter( filtered_games ),
    [time, age, players, weight]( BoardGame& game ) {
      return game.getTime() <= time && game.getAge() <= age && game.getMin() <= players && game.getMax() >= players && game.getWeight() <= weight;
    } );
  sortbyavgrating( filtered_games );

  cout << "Board games that meets your critiria: " << endl;
  while( running )
  {
    if( filtered_games.size() >= running )
    {
      cout << filtered_games[running - 1] << endl << "Another one? : y - yes, n - no" << endl;
      cin >> input;
      while( input != 'y' && input != 'n' ) { cout << "Please input correct character" << endl; cin >> input; }
      if( input == 'y' ) running++;
      else
      {
        cout << "Would you like to store your options in the file? : y - yes, n - no" << endl;
        cin >> input;
        while( input != 'y' && input != 'n' ) { cout << "Please input correct character" << endl; cin >> input; }
        if( input == 'y' )
        {
          ofstream file_out;
          file_out.open( "results.txt", ios::out);
          for( int i = 0; i < running; i++ )
          {
            file_out << filtered_games[running - 1] << endl;
          }
          file_out.close();
          cout << "Your options were stored" << endl << endl;
        }
        running = 0;
      }
    }
    else {
      cout << "I'm sorry. There is no game that matches your critiria" << endl;
      running = 0;
    }
  }
}