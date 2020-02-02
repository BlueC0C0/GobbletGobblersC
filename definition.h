#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "board.h"


/**
 * @brief Colors for the game
 *
 * These ANSI code are used to get in shape
 * what we display on console.
 */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLINK		"\033[5m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define ORANGE  "\033[33m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define SELECT	BLINK "> " RESET

/**
 * @brief Clear the console.
 */
#define CLEAR()   printf("\e[1;1H\e[2J\n")

/**
 * @brief Formatting error messages.
 */
#define WARNING(msg) printf(RED BOLD "%s" RESET"\n",msg)

/**
 * @brief Size for the character strings.
 */
#define TAILLE 40

/**
 * @brief Structure that holds the player's
 * informations.
 *
 * The structure holds the player's :
 *    - color
 *    - name
 */
typedef struct
{
  char player_name[20];
  char color[8];
}info_player_s;

/**
 * @brief the different types of errors.
 */
enum errors_e {QUIT=-1, NOERROR=0, NOPIECE=1, TOOSMALL=2, WRONGBOX=3, MOVEENNEMY=4, WRONGSIZE=5, WRONGCHOICE=6, BACK=7};

/**
 * @brief Displays the grid and the players houses.
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 * @param current_player the player whose piece to add.
 */
void display(board game, info_player_s Infos_players[], player current_player);

/**
 * @brief Collects the informations about the piece to display it on the grid
 *
 * Takes the column and line number of the box,
 * collects the informations of the player's color
 * and piece size.
 * Returns a character string in which is added the color and the size.
 *
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 * @param column the column number of the box to display.
 * @param line  the line number of the box to display.
 * @return a character string with the piece size and the color of the current player.
 */
char *cl(board game, info_player_s Infos_players[], int column, int line);

/**
 * @brief Gets what the player want to do
 *
 * Loop until there are no errors in the player choice
 *
 * Returns 1 for move_piece, 2 for place_piece, -1 if the player want to quit
 *
 * @param game the game from which to collect information.
 * @param current_player the player whose piece to add.
 * @param Infos_players the informations about the players.
 * @return return the player choice
 */
int player_choice(board game, player current_player, info_player_s Infos_players[]);

/**
 * @brief Gets the informations of the piece movements
 *
 * Ask the player where he wants to put the piece or move it
 * and the size of the piece he wants.
 * Returns the type of errors if there is one
 *
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 * @param current_player the player whose piece to add.
 * @param choice number for the action (1 : place or 2 : move a piece).
 * @return the type of error or NOERROR if everything went smoothly.
 */
int get_piece_movement(board game, player current_player, info_player_s Infos_players[], int choice);

/**
 * @brief Display a message for the type of error
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 * @param current_player the player whose piece to add.
 * @param choice number for the action (place or move a piece).
 * @param error_code
 * @return the type of error or NOERROR if everything went smoothly.
 */
void display_error(board game, player current_player, info_player_s Infos_players[], int choice, int error_code);

/**
 * @brief Add the player name and color to the Infos_player strcture
 * @param Infos_players the informations about the players.
 */
void add_info_player(info_player_s Infos_players[], int nb_player);

/**
 * @brief Initialize the game
 *
 * Chooses a random player to start,
 * adds the informations about the players
 *
 * @param Infos_players the informations about the players.
 * @return the player who starts the game
 */
player init_game(info_player_s Infos_players[], int* nb_player);

/**
 * @brief Display for the winner
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 */
void display_winner(board game, info_player_s Infos_players[]);

/**
 * @brief Chooses a value randomly between two bounds.
 * @param min lower bound.
 * @param max upper bound.
 * @return a random number between the bounds.
 */
int Random(int min, int max);

/**
 * @brief a security int entry.
 * @param sentence[] the sentence to display.
 * @return the int entered by the player.
 */
int get_entry(char sentence[]);

/**
 * @brief Get the line and column value depending on the box number.
 * @param *line a pointor to the line number.
 * @param *column a pointor to the column number.
 * @param dest the box number
 */
void get_destination(int *line, int *column, int dest);

/**
 * @brief permit to get the terminal code color in terms of player choice.
 * @param num_color the player's color choice.
 * @return the terminal color code which corresponds to the color number.
 */
char *choice_color_code(int num_color);

/**
 * @brief get the color of players
 * @param Infos_players the informations about the players.
 * @param nb_player the players' number
 * @param num_player the current player
 * @param tab_binary_color permit to see if a color is available
 */
void get_choice_color(info_player_s Infos_players[], int nb_player, int num_player, int tab_binary_color[]);

/**
 * @brief get the name of players
 * @param Infos_players the informations about the players.
 * @param nb_player the players' number
 * @param num_player the current player
 */
void get_choice_name(info_player_s Infos_players[], int nb_player, int num_player);

/**
 * @brief get the number of players
 * @return the number of players
 */
int get_nb_player();

/**
 * @brief the game core
 * @param game the game from which to collect information.
 * @param Infos_players the informations about the players.
 * @param current_player the player who make the choice_color_code
 * @param nb_player the players' number
 * @return 1 to quit, 2 for a win
 */
int game_core(board game, info_player_s Infos_players[], int current_player, int nb_player);

/**
 * @brief to choose between bot turn and player turn
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice_color_code
 * @param Infos_players the informations about the players.
 * @param nb_player the players' number
 * @return tour_bot() or player_choice() return number
 */
int turn_owner(board game, player current_player, info_player_s Infos_players[], int nb_player);


#endif