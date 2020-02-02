#ifndef _BOT_H_
#define _BOT_H_

#include "definition.h"
#include "board.h"
#include "bot.h"
/**
 * @brief get the best case rank of the board
 * @param game the game from which to collect information.
 * @param player the current player
 * @return the best rank
 */
int get_best_rank(board game, int player);

/**
 * @brief to initialized the bot
 * @param game the game from which to collect information.
 * @param infoPlayers the informations about the players.
 * @param tab_binary_color permit to see if a color is available
 */
void bot_init(info_player_s infoPlayers[], int tab_binary_color[], int num_player);

/**
 * @brief the turn of the bot
 * @param game the game from which to collect information.
 * @param info the informations about the players.
 * @param current_player the player who make the choice
 * @return 0 if things went smoothly, and 1 if not
 */
int tour_bot(board game, info_player_s info[], int current_player);

/**
 * @brief to use the easy bot
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 */
void bot_easy(board game, int current_player);

/**
 * @brief to use the medium bot
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 */
void bot_medium(board game, int current_player, info_player_s info[]);


/**
 * @brief get all informations of a moove or placement
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 * @param turNumber the turn number (1 to 108)
 * @param *turnChoice a pointor to an encoding number (1 for moove and 2 for place)
 * @param *source_line a pointor to the source line number
 * @column *source_column a pointor to the source columne number
 * @param *dest_line a pointor to the target line number
 * @column *dest_column a pointor to the target columne number
 * @param *piece_size a pointor to the size of the piece to add.
 * @return 0 if things went smoothly, and 1 if not
 */
int get_choice(board game, int current_player, int turnNumber, int* turnChoice, int* source_line, int* source_column, int* dest_line, int* dest_column, int* piece_size);

/**
 * @brief get the turn number of the best moove
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 * @param *turNumber a pointor to the turn number (1 to 108)
 * @return the rank of the best moove
 */
int get_best_moove(board game, int current_player, int* turnNumber, info_player_s info[]);

/**
 * @brief to get the case rank
 * @param game the game from which to collect information.
 * @param player the current player
 * @param line the line number
 * @column column the columne number
 * @return the case rank
 */
int get_case_rank(board game, int player, int line, int column);

/**
 * @brief test if it's possible to moove the piece
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 * @param line1 the source line number
 * @column column1 the source columne number
 * @param line2 the target line number
 * @column column2 the target columne number
 * @return 0 if things went smoothly, and 1 if not
 */
int moove_possible(board game,int current_player, int line1, int column1, int line2, int column2);

/**
 * @brief test if it's possible to place the piece
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 * @param line the line number
 * @column column the columne number
 * @param piece_size the size of the piece to add.
 * @return 0 if things went smoothly, and 1 if not
 */
int place_possible(board game, int current_player, int line, int column, int piece_size);

//

/**
 * @brief to moove or place a piece in terms of turnNumber
 * @param game the game from which to collect information.
 * @param current_player the player who make the choice
 * @param turNumber the turn number (1 to 108)
 * @return 0 if things went smoothly, and 1 if not
 */
int make_choice(board game, int current_player, int turnNumber);

#endif
