#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "readdata.h"
#include "BoardGame.h"
#include "analyze.h"

using namespace std;

void clear_data( vector<vector<string>> &data )//clearing input data when stored in vector<BoardGame>
{
  for( int i = 0; i < data.size(); i++ )
  {
    data[i].clear();
  }
  data.clear();
}

void createboardgames( vector<BoardGame>& data, const vector< vector<string> > &data_input ) //moving data from vector<vector<string>> to vector<BoardGame>
{
  for( int i = 0; i < data_input.size(); i++ )
  {
    if(((data_input[i][6])[0] != '0') && (data_input[i][14] )[0] != '0') data.push_back(BoardGame(data_input[i]));//adding new boardgame as long as it does not have value 0 for age and/or playtime
  }
}


bool check_string( string str )//checking if input string is a number value
{
  for( int i = 0; i < str.length(); i++ )
  {
    if( str[0] == '0' ) return false;//checking if string does not start with 0
    if( isdigit( str[i] ) == false ) return false; //checking if every character is a number
  }
  return true;
}

int main()
{
  ifstream file2017;
  ifstream file2018;
  ifstream file_merged;

  file2017.open( "bgg_db_2017_04.csv", ios::in );//opening input files
  file2018.open( "bgg_db_2018_01.txt", ios::in );
  file_merged.open( "bgg_db.txt" , ios::in );

  vector< vector<string> > data2017;//declaration of data for input from files
  vector< vector<string> > data2018;
  vector< vector<string> > merged_data;

  readtxt( file2018, data2018 );//reading data and storing into vector<vector<string>>
  readcsv( file2017, data2017 );
  readtxt( file_merged, merged_data );

  vector<BoardGame> boardgames_2017;//declaration of target data storage
  vector<BoardGame> boardgames_2018;
  vector<BoardGame> boardgames;
  
  createboardgames( boardgames_2017, data2017 );//moving data from  vector< vector<string> > to vector<BoardGames>
  createboardgames( boardgames_2018, data2018 );
  createboardgames( boardgames, merged_data );

  clear_data( data2017 );//clearing used data
  clear_data( data2018 );
  clear_data( merged_data );
  
  cout << "This program analyse data on BoardGames in years 2017 and 2018. " << endl;
  char input;//declaring input char for options

  while( 1 ) //loop for multiple choices
  {
    cout << "Click the right button to get the results you want to see: " << endl<<endl;
    cout << "1 - Percentage of board games with a certain age restriction" << endl;
    cout << "2 - Most optimal number of players" << endl;
    cout << "3 - Top 10 games with highest ratings in year 2017" << endl;
    cout << "4 - Top 10 games with highest ratings in year 2018" << endl;
    cout << "5 - Average and median playtime for hundred games in years 2017 and 2018 with highest ratings" << endl;
    cout << "6 - Find a game for yourself" << endl;

    cin >> input;//input for an option
    if( input == '1' )
    {
      analyse_players_age( boardgames );
      cout << "Would you like to continue? : y - yes, n - no" << endl;//a possibility of continuing with another choice
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "please input correct character" << endl; cin >> input; }//checking if the input is correct
      if( input == 'n' ) break; //ending the loop
    }
    else if( input == '2' )
    {
      analyse_players_number( boardgames );
      cout << "Would you like to continue? : y - yes, n - no" << endl;
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "Please input correct character" << endl; cin >> input; }
      if( input == 'n' ) break;
    }
    else if( input == '3' )
    {
      top10( boardgames_2017 );
      cout << "Would you like to continue? : y - yes, n - no" << endl;;
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "Please input correct character" << endl; cin >> input; }
      if( input == 'n' ) break;
    }
    else if( input == '4' )
    {
      top10( boardgames_2018 );
      cout << "Would you like to continue? : y - yes, n - no" << endl;
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "Please input correct character" << endl; cin >> input; }
      if( input == 'n' ) break;
    }
    else if( input == '5' )
    {
      avg_med_playtime( boardgames_2017, boardgames_2018 );
      cout << "Would you like to continue? : y - yes, n - no" << endl;
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "please input correct character" << endl; cin >> input; }
      if( input == 'n' ) break;
    }
    else if( input == '6' )
    {
      string age;//declaring input data
      string time;
      char weight_type;
      string players;
      char year;
      double weight;
      cout << "Input number of players" << endl;
      cin >> players;
      while( !check_string(players) ) { cout << "Please input correct number" << endl; cin >> players; }//checking if input is a number
      cout << "Input the maximum time of the gameplay in minutes" << endl;
      cin >> time;
      while( !check_string( time) ) { cout << "Please input correct number" << endl; cin >> time; }
      cout << "Input the age of the youngest of the players" << endl;
      cin >> age;
      while( !check_string( age ) ) {cout << "Please input correct number" << endl; cin >> age;}
      cout << "Would you prefer your game to be lighter" << endl << "y - yes, n - no" << endl;
      cin >> weight_type;
      while( weight_type != 'n' && weight_type != 'y' ) { cout << "Please input correct character" << endl;  cin >> weight_type; }//input weight_type as long as it has desirable value
      switch( weight_type )
      {
      case 'y': weight = 1.5;
      default: weight = 10;
      }
      cout << "Choose the year of the rating" << endl << "7 - 2017, 8 - 2018" << endl;
      cin >> year;
      while( year != '7' && year != '8' ) { cout << "Please input correct number" << endl; cin >> year; }//input year as long as it has desirable value
      switch(year)
        {
          case '7': choose_boardgame( boardgames_2017, stoi( time ), stoi( age ), weight, stoi( players ) );
          case '8': choose_boardgame( boardgames_2018, stoi( time ), stoi( age ), weight, stoi( players ) );
        }
    
      cout << "Would you like to continue? : y - yes, n - no" << endl;
      cin >> input;
      while( input != 'n' && input != 'y' ) { cout << "Please input correct character" << endl; cin >> input; }//input character as long as it has desirable value
      if( input == 'n' ) break;
    }
    else {
      cout << "There is no option for character " << input << ". Please choose only available options" << endl;//in case of choosing wrong option
    }
  }

  file2017.close( );//closing files
  file2018.close( );
  file_merged.close();
  return 0;
}
