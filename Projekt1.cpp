#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

//#using <System.xml.dll>
using namespace std;

struct BoardGame
{
  string name;
  int time;
  int age;
  int min_players;
  int max_players;
  double avg_rating;
  double geek_rating;
  int owned;
  double weight;
public:
  BoardGame() {}
  BoardGame( vector<string> dane )
  {
    this->name = dane.at(3);
    this->min_players = stoi(dane.at( 4 ));
    this->max_players = stoi(dane.at( 4 ));
    this->time = stoi( dane.at(6) );
    this->age = stoi( dane.at(14) );
    this->avg_rating = stod( dane.at(10) );
    this->geek_rating = stod( dane.at(11) );
    this->owned = stoi( dane.at(16) );
    this->weight = stod( dane.at(19) );
  }

  string getName() {
    return this->name;
  }
  int getAge()
  {
    return this->age;
  }
  friend ostream& operator<<( ostream& os, const BoardGame& x )
  {
    os << "NAME: " << x.name << endl << "PLAYTIME: " << x.time
      << endl << "AGE: " << x.age << endl << "AVERAGE RATING: " << x.avg_rating << endl << "GEEK RATING: " << x.geek_rating
      << endl << "OWNED BY: " << x.owned << endl << "WEIGHT: " << x.weight << endl;
    return os;
  }
};

bool readcsv( ifstream& file, vector<vector<string>> &data )
{
  if( !file.is_open() ) return 0;
  string line;//input line by line
  string word;
  vector <string> row;// vector for words
  getline( file, line );//reading first row 
  while( getline( file, line ) && line!="" )
  {
    row.clear();//clearing vector for a new line
    stringstream ss( line );

    while( getline( ss, word, ',' ) && word != "" )//while line isn't over
    {
      if( word[0] == 34 )//check if its a "" - then ommitt "," until next "
      {
        string add;
        while( word[word.size() - 1] != 34 )
        {
          getline( ss, add, ',' );
          word.append( add );
        }
      }
      row.push_back( word );
    }
      if(row.size() == 20 )
    data.push_back( row );
  }
  return 1;
}

bool readtxt( ifstream& file, vector<vector<string>>& data )
{
  if( !file.is_open() ) return 0;
  string line;//input line by line
  string word;
  vector <string> row;// vector for words
  getline( file, line );//reading first row 
  while( getline( file, line ) && line != "" )
  {
    row.clear();//clearing vector for a new line
    stringstream ss( line );

    while( getline( ss, word, '\t' ) && word != "" )//while line isn't over
    {
      row.push_back( word );
    }
    if( row.size() == 20 )
      data.push_back( row );
  }
  return 1;
}

void clear_data( vector<vector<string>> &dat )
{
  for( int i = 0; i < dat.size(); i++ )
  {
    dat[i].clear();
  }
  dat.clear();
}

void createboardgames( BoardGame* data, const vector< vector<string> > &data_input ) {
  for( int i = 0; i < data_input.size(); i++ )
  {
    new ( data + i ) BoardGame(data_input[i]);
  }
}

void createboardgames( vector<BoardGame>& data, const vector< vector<string> > &data_input ) {
  for( int i = 0; i < data_input.size(); i++ )
  {
    data.push_back(BoardGame( data_input[i] ));
  }
}

void sortbyage( const vector<BoardGame>& vec )
{
  sort( vec.begin(), vec.end(), []( const BoardGame& lhs, const BoardGame& rhs ) {
    return lhs.age < rhs.age;
    } );
}



int main()
{
  ifstream file2017;
  ifstream file2018;

  file2017.open( "bgg_db_2017_04.csv");
  file2018.open( "bgg_db_2018_01.txt" );

  vector< vector<string> > data2017;
  vector< vector<string> > data2018;

  readcsv( file2017, data2017 );
  readtxt( file2018, data2018 );
  
  //BoardGame* boardgames_2017 = new BoardGame[data2017.size()];
  //BoardGame* boardgames_2018 = new BoardGame[data2018.size()];

  vector<BoardGame> boardgames_2017;
  vector<BoardGame> boardgames_2018;
  
  createboardgames( boardgames_2017, data2017 );
  createboardgames( boardgames_2018, data2018 );

  //int size2017 = data2017.size();
  //int size2018 = data2018.size();

  clear_data( data2017 );
  clear_data( data2018 );

  /*vector<int> games_geek_rating;
  for( int i = 0; i < size2017; i++ )
  {
    games_geek_rating.push_back( boardgames_2017[i].getAge() );
  }
  sort( games_geek_rating.begin(), games_geek_rating.end() );
  for( int i = 0; i < games_geek_rating.size(); i++ )
    cout << games_geek_rating[i] << " ";*/

  //sort( boardgames_2017.begin(), boardgames_2017.end(), &sort_by_avg_rating );
  sortbyage( boardgames_2017 );

  //cout << boardgames_2017[4998];


  file2017.close( );
  file2018.close( );

  return 0;
}
