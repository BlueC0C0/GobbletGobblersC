#include "definition.h"
#include "board.h"


int main()
{
  	srand (time (NULL));

  	int return_end, nb_player;
  	info_player_s Infos_players[2];
  	board game = new_game();
  	player current_player = init_game(Infos_players, &nb_player);

	return_end = game_core(game, Infos_players, current_player, nb_player);

  	if (return_end==1)
  	{
    	destroy_game(game);
    	CLEAR();
    	WARNING(RED"Vous avez quitté la partie."RESET);
  	}
  	else if (return_end==2)
  	{
    	display_winner(game, Infos_players);
    	destroy_game(game);
  	}

  	return 0;
}
