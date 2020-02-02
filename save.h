#ifndef _TEST_H_
#define _TEST_H_

#include "definition.h"
#include "save.h"

char *replace(char *char_string);


void carriage_return_file(FILE* fichier);


char *get_player(FILE* fichier, long line, int player_number);


int get_player_win(FILE* fichier, long line, int player_number);


long check_versus(FILE* fichier, info_player_s Infos_players[]);


int total_game(FILE* fichier, long line);


void display_scoreboard(FILE* fichier);


int get_total_match_winner(FILE* fichier, info_player_s Infos_players[], int winner);


void add_in_file(FILE* fichier, info_player_s Infos_players[], long line);


void add_win(FILE* fichier, info_player_s Infos_players[], int winner);

void clear_scoreboard();

#endif