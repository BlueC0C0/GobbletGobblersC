#include "board.h"
#include "definition.h"
#include "bot.h"

//Player choice
int player_choice(board game, player current_player, info_player_s Infos_players[])
{
	int choice;
	
  do
  {
    choice = get_entry("Que souhaitez-vous faire ?\n1° Deplacer une piece\n2° Poser une piece\nq° Quitter la partie\n"SELECT);
  } while(choice!=QUIT&&get_piece_movement(game, current_player, Infos_players, choice));	//Verify the player's choice
	return choice;
}

//Asks data about the move
int get_piece_movement(board game, player current_player, info_player_s Infos_players[], int choice)
{
  int line_source, column_source, line_dest, column_dest, size, error=NOERROR, holder;

	display(game, Infos_players, current_player);

	if (choice==QUIT)	//If player enters 'q'
	{
		error=BACK;
	}

	else if (choice!=1&&choice!=2)	//If players enter neither a 1 or 2
	{
		error = WRONGCHOICE;
	}
	
	else if (choice==1)	//If players choosed move_piece
  {
		//Line and column for the chosen box
    get_destination(&line_source,&column_source,get_entry("Quelle pièce voulez-vous déplacer ? - (q pour annuler le choix)\n"SELECT));

		//Who is on the chosen box
    holder = get_place_holder(game, line_source, column_source);

		if (line_source==QUIT)	//If the player enters 'q'
		{
			error=BACK;
		}

    else if (holder!=current_player&&holder!=NONE)	//If players wants to move an ennemy
    {
      error = MOVEENNEMY;
    }

    else if (holder==NONE)	//If there is no piece on the chosen box
    {
      error = NOPIECE;
    }

    else
    {
      display(game, Infos_players, current_player);

			//Line and column for the chosen box
      get_destination(&line_dest,&column_dest,get_entry("Quelle est la case de destination ? - (q pour annuler le choix)\n"SELECT));

			if (line_dest==QUIT)	//If the player enters 'q'
			{
				error=BACK;
			}

			else
			{
				error = move_piece(game, line_source, column_source, line_dest, column_dest);  //Gets error return from move_piece function
			}
    }
  }
	
  else
  {
		//Line and column for the chosen box
    get_destination(&line_dest,&column_dest,get_entry("Quelle est la case de destination ? - (q pour annuler le choix)\n"SELECT));

		if (line_dest==QUIT)	//If the player enters 'q'
		{
			error=BACK;
		}

		else
    {
			display(game, Infos_players, current_player);

	    switch (get_entry("Quelle taille voulez-vous ? - (q pour annuler le choix)\n"SELECT))
	    {
				case QUIT: //If the player enters 'q'
					size=0;
					break;
	      case SMALL:
	        size = SMALL;
	        break;
	      case MEDIUM:
	        size = MEDIUM;
	        break;
	      case LARGE:
	        size = LARGE;
	        break;
	      default :
	        size = -1;
	        break;
	    }

			if (size==0)	//If the player entered 'q'
			{
				error = BACK;
			}

	    else if (size!=SMALL&&size!=MEDIUM&&size!=LARGE)	//If the size is not in size enum
	    {
	      error = WRONGSIZE;
	    }
			
	    else
	    {
	      error = place_piece(game, current_player, size, line_dest, column_dest); //Gets error return from palce_piece function
	    }
		}
  }

  display_error(game, current_player, Infos_players, choice, error);

  return error;
}

int game_core(board game, info_player_s Infos_players[], int current_player, int nb_player)
{
	int quit=0, exit;
	do
	{
		do 
		{
			display(game, Infos_players, current_player);
			quit = turn_owner(game, current_player, Infos_players, nb_player);
			if (quit==QUIT)
			{	
				do 
				{
					display(game, Infos_players, current_player);
					exit = get_entry("Voulez vous vraiment quitter la partie ?\n1 : oui\n2 : non\n"SELECT);

					if (exit==2)
					{
						quit = 0;
					}
				} while(exit!=1&&exit!=2);
			}
		} while(quit==0);

		current_player = next_player(current_player);

	} while(get_winner(game)==0 && quit!=QUIT);
	
	if (quit==QUIT)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int turn_owner(board game, player current_player, info_player_s Infos_players[], int nb_player)
{
	if((current_player==2 && nb_player==1) || nb_player==0)
	{
		return tour_bot(game, Infos_players, current_player);
	}
	else
	{
		return player_choice(game, current_player, Infos_players);
	}
}