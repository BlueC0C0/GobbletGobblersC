#include <stdlib.h>
#include <string.h>
#include "board.h"

#define COLUMN 0
#define LINE 1
#define DIAG1 2
#define DIAG2 3



static bool is_not_on_grid(int line, int column);

static void is_holding(board game, int line, int column, int player_winner[][4], int check);



int nb_piece_case(board game, int line, int column)
{
	int i = 0;

	while(game->grid[line][column][i].player_owner!=0 && i!=3)
	{
		i++;//increase "i" if the current piece isn't a "0"
	}
	return i;
}

board new_game()
{
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));

  for (int depth = 0; depth < DIMENSIONS; depth++)
  {
    for (int column = 0; column< DIMENSIONS; column++)
    {
      for (int line = 0; line< NB_SIZE; line++)
      {
          new_board->grid[column][line][depth].piece_size=NONE;
          new_board->grid[column][line][depth].player_owner=NO_PLAYER;
      }
    }
  }
  for (int player=0; player<NB_PLAYERS; player++)
  {
    for (int nb_piece=0; nb_piece<NB_SIZE; nb_piece++)
    {
      new_board->player_house[player][nb_piece] = NB_INITIAL_PIECES;
    }
  }

	return new_board;
}

void destroy_game(board game)
{
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}

board copy_game(board original_game)
{
	// memory allocation for the board (leave it as is)
	board game_copy = malloc(sizeof(struct board_s));

	//to copy original_game in game_copy
	memcpy(game_copy,original_game,sizeof(struct board_s));

	return game_copy;
}

player next_player(player current_player)
{
	//permit to have more than two players
	if (current_player==NB_PLAYERS)
	{
		return PLAYER_1;
	}
  	else
  	{
    	return current_player+1;
  	}
}

player get_place_holder(board game, int line, int column)
{
	int i=0;

	if(line < 0 || line > 2 || column < 0 || column > 2) i=0;
	else i = nb_piece_case(game, line, column);

	if(i==0)
	{
		return NO_PLAYER;
	}

  return game->grid[line][column][i-1].player_owner;
}

size get_piece_size(board game, int line, int column)
{
	int i=0;

	if(line < 0 || line > 2 || column < 0 || column > 2) i=0;
	else i = nb_piece_case(game, line, column);

	if(i==0)
	{
		return NONE;
	}

	return game->grid[line][column][i-1].piece_size;
}

static void is_holding(board game, int line, int column, int player_winner[][4], int check)
{
  int holder = get_place_holder(game, line, column);
  if (holder!=NO_PLAYER)
  {
    player_winner[holder-1][check]++;
  }
}

player get_winner(board game)
{
  int winner=0, player_winner[NB_PLAYERS][4]={0}, nb_winner=0, i=0;

  while (i<DIMENSIONS)
  {
		for (int y = 0; y < NB_PLAYERS; y++)
		{
			for (int j = 0; j < 2; j++)
			{
				player_winner[y][j]=0;
			}
		}

    for (int j = 0; j < DIMENSIONS; j++)
    {
      is_holding(game, i, j, player_winner, COLUMN);
      is_holding(game, j, i, player_winner, LINE);
    }

    is_holding(game, i, i, player_winner, DIAG1);
    is_holding(game, 2-i, i, player_winner, DIAG2);

    for (int k = 0; k<NB_PLAYERS; k++)
    {
      for (int l = 0; l<4; l++)
      {
        if (player_winner[k][l]==3)
        {
					if (k+1!=winner)
					{
						nb_winner++;
						winner = k+1;
					}
        }
      }
    }
    i++;
  }
  if (nb_winner>1||nb_winner==0)
  {
    return 0;
  }
  else
  {
    return winner;
  }
}

int get_nb_piece_in_house(board game, player checked_player, size piece_size)
{
	int return_value = 0;
	if(piece_size > 0 && piece_size < 4)
	{
		if(checked_player == 1 || checked_player == 2) 
		{
			return_value = game->player_house[checked_player-1][piece_size-1];
		}
	}
	

	return return_value;
}

int place_piece(board game, player current_player, size piece_size, int line, int column)
{
	int i;

	if(is_not_on_grid(line, column)==1)
	{
		return 3;//stands for illegal entries: e.g. a too large line number.
	}
	if(piece_size<=get_piece_size(game, line, column))
	{
		return 2;//stands for (target): the piece is to small to be put there.
	}
	if(get_nb_piece_in_house(game, current_player, piece_size)== NONE)
	{
		return 1;//stands for (source): the piece is not available in the player's house.
	}

	i = nb_piece_case(game, line, column);

	game->grid[line][column][i].piece_size = piece_size;//place the piece in the box 
	game->grid[line][column][i].player_owner = current_player;//set the owner of the piece

	game->player_house[current_player-1][piece_size-1]--;//decrease the number of piece available
	return 0;
}

int move_piece(board game, int source_line, int source_column, int target_line, int target_column)
{
  int error, source_number_piece=0, target_number_piece=0;

  if (get_piece_size(game, source_line, source_column)==NONE)
  {
    error = 1;  //Stands for (source): there is no piece at the initial place.
  }

  else if (get_piece_size(game, source_line, source_column)<=get_piece_size(game, target_line, target_column))
  {
    error = 2;  //The piece is too small to be put at the target place.
  }

  else if (is_not_on_grid(source_line,source_column)||is_not_on_grid(target_line,target_column))
  {
    error = 3;  //Stands for illegal entries: e.g. a too large line number.
  }

  else
  {
    error = 0;

		source_number_piece = nb_piece_case(game, source_line, source_column);//to get the nb piece in the source box
		target_number_piece = nb_piece_case(game, target_line, target_column);//to get the nb piece in the target box

		game->grid[target_line][target_column][target_number_piece].piece_size = game->grid[source_line][source_column][source_number_piece-1].piece_size;
    game->grid[target_line][target_column][target_number_piece].player_owner = game->grid[source_line][source_column][source_number_piece-1].player_owner;
    game->grid[source_line][source_column][source_number_piece-1].piece_size = NONE;
    game->grid[source_line][source_column][source_number_piece-1].player_owner = NONE;
  }
  return error;
}

static bool is_not_on_grid(int line, int column)
{
  bool boolean;
  int y=line, x=column;
  if (y<0||y>=DIMENSIONS||x<0||x>=DIMENSIONS)
  {
    boolean = true;
  }
  else
  {
    boolean = false;
  }
  return boolean;
}