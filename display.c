#include "board.h"
#include "definition.h"
#include "bot.h"
#include "save.h"

//display the board
void display(board game, info_player_s Infos_players[], player current_player)
{
  CLEAR();	//clear the console
  printf("%s\t\t\t╔═════════════════╗\n"RESET,                    Infos_players[0].color);

  printf(WHITE"\t╔═1═╦═2═╦═3═╗\t%s║ %-16s║\n"RESET,               Infos_players[0].color,\
                                                                  Infos_players[0].player_name);

  printf(WHITE"\t║ %s ║ %s ║ %s ║\t%s║ n°1 ║ n°2 ║ n°3 ║\n"RESET, cl(game, Infos_players, 0, 0),\
                                                                  cl(game, Infos_players, 0, 1),\
                                                                  cl(game, Infos_players, 0, 2),\
                                                                  Infos_players[0].color);\

  printf(WHITE"\t╠═4═╬═5═╬═6═╣\t%s║  %d  ║  %d  ║  %d  ║\n"RESET, Infos_players[0].color,\
                                                                  get_nb_piece_in_house(game,1,1),\
                                                                  get_nb_piece_in_house(game,1,2),\
                                                                  get_nb_piece_in_house(game,1,3));

  printf(WHITE"\t║ %s ║ %s ║ %s ║\t╠═════╩═════╩═════╣\n",        cl(game, Infos_players, 1, 0),\
                                                                  cl(game, Infos_players, 1, 1),\
                                                                  cl(game, Infos_players, 1, 2));

  printf(WHITE"\t╠═7═╬═8═╬═9═╣\t%s║ %-16s║\n"RESET,               Infos_players[1].color,\
                                                                  Infos_players[1].player_name);

  printf(WHITE"\t║ %s ║ %s ║ %s ║\t%s║ n°1 ║ n°2 ║ n°3 ║\n"RESET, cl(game, Infos_players, 2, 0),\
                                                                  cl(game, Infos_players, 2, 1),\
                                                                  cl(game, Infos_players, 2, 2),\
                                                                  Infos_players[1].color);

  printf(WHITE"\t╚═══╩═══╩═══╝\t%s║  %d  ║  %d  ║  %d  ║\n"RESET, Infos_players[1].color,\
                                                                  get_nb_piece_in_house(game,2,1),\
                                                                  get_nb_piece_in_house(game,2,2),\
                                                                  get_nb_piece_in_house(game,2,3));

  printf("%s\t\t\t╚═════╩═════╩═════╝\n"RESET,                    Infos_players[1].color);

  if (get_winner(game)==0)	//display the player's name turn, display = none if there is a winner
  {
    printf("Tour de "BOLD"%s%s"RESET" :\n\n", Infos_players[current_player-1].color, Infos_players[current_player-1].player_name);
  }
}

//displays the winner
void display_winner(board game, info_player_s Infos_players[])
{
	display(game, Infos_players, NO_PLAYER);
	
  printf("\t%s"BLINK"╔════════════════════════════════════╗\n",               Infos_players[get_winner(game)-1].color);

  printf("\t║"RESET WHITE"      La partie est finie !!!%s"BLINK"       ║\n",  Infos_players[get_winner(game)-1].color);

  printf("\t║"RESET WHITE"       c'est ... %s%-19s%s"BLINK"║\n",              Infos_players[get_winner(game)-1].color,\
                                                                              Infos_players[get_winner(game)-1].player_name,\
                                                                              Infos_players[get_winner(game)-1].color);

  printf("\t║"RESET WHITE"           qui gagne !!!%s"BLINK"            ║\n",  Infos_players[get_winner(game)-1].color);

  printf("\t╚════════════════════════════════════╝\n" RESET);

	FILE* fichier = NULL;
	int winner = get_winner(game)-1;
	fichier = fopen("save.txt", "r+");

	long line = check_versus(fichier, Infos_players);

	add_win(fichier, Infos_players, winner);

	printf("Ce match a eu lieu %d fois\n", total_game(fichier, line));

  printf("%s a gagné %d match(s)\n%s a gagné %d match(s)\n", get_player(fichier, line, PLAYER_1), get_player_win(fichier, line, PLAYER_1),get_player(fichier, line, PLAYER_2), get_player_win(fichier, line, PLAYER_2));

  printf("%s a gagné %d partie(s) au total !\n", Infos_players[winner].player_name, get_total_match_winner(fichier, Infos_players, winner));

	fclose(fichier);
	
}

//displays the error sentence of the function get_piece_movement
void display_error(board game, player current_player, info_player_s Infos_players[], int choice, int error_code)
{
  char message[8][60]={ {"Il n'y a pas de pièce sur cette case."},\
                        {"Vous n'avez plus de pièce de cette taille."},\
                        {"Votre pièce est trop petite pour être placée ici."},\
                        {"La case que vous avez entrée n'existe pas."},\
                        {"Vous ne pouvez pas déplacer la pièce d'un adversaire !"},\
                        {"Cette taille n'existe pas."},\
                        {"Ce n'est pas un choix valide."},\
                        {"Retour."}\
											};

  display(game, Infos_players, current_player);

	/*If the players chosed to move a piece and the error is NOPIECE, this condition is mainly used because
	move_piece and place_piece return the same number for a different reason*/
  if (error_code==NOPIECE&&choice==1)	
  {
    WARNING(message[0]);
  }

  else if (error_code!=NOERROR)
  {
    WARNING(message[error_code]);
  }
}
