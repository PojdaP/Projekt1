#include "readdata.h"

bool readcsv( ifstream& file, vector<vector<string>>& data )
{
  if( !file.is_open() ) return 0;
  string line;//input line by line
  string word;
  vector <string> row;// vector for words
  getline( file, line );//reading first row of headers
  while( getline( file, line ) && line != "" )//reading as long as there's a line and it's not empty
  {
    row.clear();//clearing vector for a new line
    stringstream ss( line );//changing sting into stream

    while( getline( ss, word, ',' ) && word != "" )//while line isn't over get every word beetween ','
    {
      if( word[0] == 34 )//check if its a " - then ommitt "," until next "
      {
        string add;//new string for appending words
        while( word[word.size() - 1] != 34 )//as long as the last character of the word is not "
        {
          getline( ss, add, ',' );//get another word and append to word
          word.append( add );
        }
      }
      row.push_back( word );//when word is form " to ", add to row
    }
    if( row.size() == 20 )//checking if numbers of words in the row is equal to number of columns in the file
      data.push_back( row );//adding row to data
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
  while( getline( file, line ) && line != "" )//reading as long as there's a line and it's not empty
  {
    row.clear();//clearing vector for a new line
    stringstream ss( line );//changing sting into stream

    while( getline( ss, word, '\t' ) && word != "" )//while line isn't over od word does not exist
    {
      row.push_back( word );//adding word to thw row
    }
    if( row.size() == 20 )//checking if numbers of words in the row is equal to number of columns in the file
      data.push_back( row );
  }
  return 1;
}