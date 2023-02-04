#pragma once
#include "BoardGame.h"

void analyse_players_age( vector<BoardGame>& games );
void top10( vector<BoardGame> games );
void analyse_players_number( vector<BoardGame>& games );
void avg_med_playtime( vector<BoardGame>& games1, vector<BoardGame>& games2 );
void choose_boardgame( vector<BoardGame>& games, int time, int age, double weight, int players );
void printboardgames( vector<BoardGame>& vec );
void sortbyavgrating( vector<BoardGame>& game );
void sortbyplaytime( vector<BoardGame>& game );