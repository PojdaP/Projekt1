#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
  ifstream file2017;
  file2017.open( "bgg_db_2017_04.csv");
  string line;
  string word;
  vector <string> row;
  vector< vector<string> > dane2017;
  while( getline( file2017, line ) )
  {
    row.clear();
    stringstream ss(line);
    while( getline( ss, word, ',' ) )
    {
      row.push_back( word );
    }
    dane2017.push_back( row );
  }
  //for( vector<string> i : dane2017 )
  //{
  //  for( string j : i )
  //  {
  //    cout << j << " ";
  //  }
  //  cout << endl;
  //}
  cout << dane2017[0][0];
  return 0;
}
