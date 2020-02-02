#include <unistd.h>
#include "definition.h"
#include "board.h"
#include "bot.h"

#define RECUR   5

void bot_init(info_player_s infoPlayers[], int tab_binary_color[], int num_player)
{
	int choiceColorBot;
	int choiceNivBot;

	do
	{
		choiceColorBot = Random(1,6);
	} while(tab_binary_color[choiceColorBot-1]!=1);

	strcpy(infoPlayers[num_player-1].color, choice_color_code(choiceColorBot));//set bot's color

	do
	{
		CLEAR();
		printf("quelle est la difficulté du bot n°%d\n1° easy\n2° medium\n> ", num_player);
		choiceNivBot = get_entry("");
	} while(choiceNivBot!= 1 && choiceNivBot!= 2);

	switch(choiceNivBot)
	{
		case 1:
			strcpy(infoPlayers[num_player-1].player_name, "Le Petit Bot");//set bot's name
			break;
		case 2:
			strcpy(infoPlayers[num_player-1].player_name, "Le Grand Bot");//set bot's name
			break;
	}
}

int tour_bot(board game, info_player_s info[], int current_player)
{
	
	printf("%s%s reflechit ...\n"WHITE, info[current_player-1].color, info[current_player-1].player_name);

	if(strcmp(info[current_player-1].player_name, "Le Petit Bot")==0)
	{
		bot_easy(game, current_player);
	}

	else if(strcmp(info[current_player-1].player_name, "Le Grand Bot")==0)
	{
		bot_medium(game, current_player, info);
	}

	sleep(2);

	return 1;
}


void bot_easy(board game, int current_player)
{
	int bot_choice;
	int rank = 1;

	do
	{
		rank++;
		bot_choice = Random(1, 108);
	} while(make_choice(game, current_player, bot_choice)!=0);

}

void bot_medium(board game, int current_player, info_player_s info[])
{
	int turnNumber=0, test;

	while(1)
	{
		get_best_moove(game, current_player, &turnNumber, info);
		if(make_choice(game, current_player, turnNumber)==0) 
		{
			break;
		}
	}
}


int get_choice(board game, int current_player, int turnNumber, int* turnChoice, int* source_line, int* source_column, int* dest_line, int* dest_column, int* piece_size)
{
  int test=1, rank=1;

	if(turnNumber<=27)
	{
		*turnChoice=2;//place a piece
		for(int i=0;i<3;i++)
		{
			for(int y=0;y<3;y++)
			{
				if(test==0) break;

				*dest_line=i;
				*dest_column=y;
				for(int z=1;z<=3;z++)
				{
					*piece_size=z;
					if(rank==turnNumber)
					{
						test=0;
						break;
					}
					else rank++;
				}
			}
		}
		*source_line=0;
		*source_column=0;
	}

	else
	{
		*turnChoice=1;
		for(int i=0;i<3;i++)
		{
			for(int y=0;y<3;y++)
			{
				if(test==0) break;

				*source_line=i;
				*source_column=y;

				for(int z=0;z<3;z++)
				{
					for(int k=0;k<3;k++)
					{
						if(test==0) break;

						*dest_line=z;
						*dest_column=k;

						if(rank==(turnNumber-27))
						{
								test=0;
								break;
						}

						else 
						{
							rank++;
						}
					}
				}
			}
		}

		*piece_size=0;

		if(get_place_holder(game, *source_line, *source_column)!=current_player)
		{
			return 1;
		}
	}
	return 0;
}

int get_best_moove(board game, int current_player, int* turnNumber, info_player_s info[])
{

	int bestRank=-10, rank=0, rankB=0, turnChoice, source_line, dest_line, source_column, dest_column, piece_size, return_value;

	for(int i=1; i<=108; i++)
	{
		return_value = get_choice(game, current_player, i, &turnChoice, &source_line, &source_column, &dest_line, &dest_column, &piece_size);
		if(return_value==0)
		{
			if(turnChoice==2)
			{

				if(place_possible(game, current_player, dest_line, dest_column, piece_size)==0)
				{
					rank = get_case_rank(game, current_player, dest_line, dest_column);

					if(rank>bestRank)
					{
						bestRank=rank;
						*turnNumber=i;
					}
					else if(rank==bestRank)
					{
						int test = Random(1,6);
						if(test==1)
						{
							bestRank=rank;
							*turnNumber=i;
						}
					}
					printf("choix n°%d : (line: %d, column: %d, size: %d)= %d\n", i, dest_line, dest_column, piece_size, rank);
				}
				if(*turnNumber==i)
				{
					if(piece_size==2)
					{
						(*turnNumber)-=1;
					}
					else if(piece_size==3)
					{
						(*turnNumber)-=2;
					}
					if(bestRank>=14)
					{
						for(int y=3; y>=0; y--)
						{
							if(get_nb_piece_in_house(game, current_player, y)!=0)
							{
								piece_size=y;
								break;
							}
						}
					}
					else
					{
						for(int y=1; y<=3; y++)
						{
							if(get_nb_piece_in_house(game, current_player, y)!=0)
							{
								if(get_piece_size(game, dest_line, dest_column)<y)
								{
									piece_size=y;
									break;
								}

							}
						}
					}
					(*turnNumber)+= (piece_size-1);
				}
			}
			else if(turnChoice==1)
			{
				if(moove_possible(game, current_player, source_line, source_column, dest_line, dest_column)==0)
				{
					rank = get_case_rank(game, current_player, dest_line, dest_column);
          board game_2 = malloc(sizeof(struct board_s));
        	game_2 = copy_game(game);

        	if(make_choice(game_2, current_player, i)==0)
         	{
						/*printf("prevision");
						display(game_2, info, current_player);
						printf("prevision");*/
            rankB = -1 * get_best_rank(game_2, next_player(current_player));

						if(get_winner(game_2)==next_player(current_player)) 
						{
							rankB=-300;
						}
						
						else if(get_winner(game_2)==current_player) 
						{
							rankB=400;
						}

            if(rankB==-10) 
						{
							rankB=0;
						}
          }

        	destroy_game(game_2);

					if((rank+rankB)>bestRank)
					{
						bestRank=rank+rankB;
						*turnNumber=i;
					}

					else if((rank+rankB)==bestRank)
					{
						int test = Random(1,2);
						if(test==1)
						{
							bestRank=rank+rankB;
							*turnNumber=i;
						}
					}
					printf("choix n°%d : (line1: %d, column1: %d,line2: %d, column2: %d) = %d+%d = %d\n", i, source_line, source_column, dest_line, dest_column, rank, rankB, rank+rankB);
				}
			}
		}
	}

	if(bestRank==-10)
  {
    return Random(1,108);
  }
	else return bestRank;
}

int get_case_rank(board game, int player, int line, int column)
{
	int other_player = next_player(player);
	int rankDiag1=0, rankDiag2  = 0, rankHor=0, rankVer=0, rank=0;
	int rankDiag1_2=0, rankDiag2_2 = 0, rankHor2=0, rankVer2=0;
	if(line==column)
	{
		for(int i=0;i<3;i++)
		{
			if(get_place_holder(game, i, i)==other_player)
			{
					rankDiag1_2--;
			}
			else if(get_place_holder(game, i, i)==player)
			{
				rankDiag1++;
			}
		}
	}

	if(line==2-column)
	{
		for(int i=0;i<3;i++)
		{
			if(get_place_holder(game, i, 2-i)==other_player)
			{
				rankDiag2_2--;
			}
			else if(get_place_holder(game, i, 2-i)==player)
			{
				rankDiag2++;
			}
		}
	}


	for(int i=0;i<3;i++)
	{
		if(get_place_holder(game, i, column)==other_player)
		{
			rankVer2--;
		}
		else if(get_place_holder(game, i, column)==player)
		{
			rankVer++;
		}
		if(get_place_holder(game, line, i)==other_player)
		{
			rankHor2--;
		}
		else if(get_place_holder(game, line, i)==player)
		{
			rankHor++;
		}
	}

	if(rankVer!=2) rankVer+=rankVer2;
	else if(rankVer2!=-2) rankVer+=rankVer2;

	if(rankHor!=2) rankHor+=rankHor2;
	else if(rankHor2!=-2) rankHor+=rankHor2;

	if(rankDiag1!=2) rankDiag1+=rankDiag1_2;
	else if(rankDiag1_2!=-2) rankDiag1+=rankDiag1_2;

	if(rankDiag2!=2) rankDiag2+=rankDiag2_2;
	else if(rankDiag2_2!=-2) rankDiag2+=rankDiag2_2;

	int tab_rank[4];
	tab_rank[0]=rankDiag1;
	tab_rank[1]=rankDiag2;
	tab_rank[2]=rankHor;
	tab_rank[3]=rankVer;


	for(int i =0; i<4; i++)
	{
		if(tab_rank[i]==-2)
		{
			if(get_piece_size(game, line, column)!=3)
			{
				rank+=15;
        if(get_place_holder(game, line, column)==other_player) rank+=5;
			}
			else rank+=0;
		}
		else if(tab_rank[i]==-1)
		{
			if(get_piece_size(game, line, column)!=3)
			{
				rank+=4;
			}
			else rank+=0;
		}
		else if(tab_rank[i]==0)
		{
			rank+=0;
		}
		else if(tab_rank[i]==1)
		{
			if(get_place_holder(game, line, column)!=player && get_piece_size(game, line, column)!=3)
			{
				rank+=6;
			}
			else rank+=0;
		}
		else if(tab_rank[i]==2)
		{
			if(get_place_holder(game, line, column)!=player && get_piece_size(game, line, column)!=3)
			{
				rank+=60;
			}
			else rank+=0;
		}
	}

	if(rank>4 && rank <= 12 && get_place_holder(game, line, column)!=player && get_piece_size(game, line, column)!=3)
	{
		rank=6;
	}

	return rank;
}

int moove_possible(board game,int current_player, int source_line, int source_column, int dest_line, int dest_column)
{
	int return_value;
	board game_2 = malloc(sizeof(struct board_s));
	game_2 = copy_game(game);

	if(move_piece(game_2, source_line, source_column, dest_line, dest_column)==0) return_value = 0;
	else return_value = 1;

	destroy_game(game_2);

	return return_value;
}

int place_possible(board game, int current_player, int line, int column, int piece_size)
{
	board game_2 = malloc(sizeof(struct board_s));
	game_2 = copy_game(game);
	int return_value = place_piece(game_2, current_player, piece_size, line, column);

	destroy_game(game_2);

	return return_value;
}


int make_choice(board game, int current_player, int turnNumber)
{
	int return_value=0;

	int turnChoice, source_line, source_column, dest_line, dest_column, piece_size;

	if(get_choice(game, current_player, turnNumber, &turnChoice, &source_line, &source_column, &dest_line, &dest_column, &piece_size)!=0) return_value=1;

	if(turnChoice==1 && return_value==0)
	{
		return_value = move_piece(game, source_line, source_column, dest_line, dest_column);
	}
	else if(turnChoice==2 && return_value==0)
	{
		return_value = place_piece(game, current_player, piece_size, dest_line, dest_column);
	}

	return return_value;
}

int get_best_rank(board game, int player)
{
  int rank=0, bestRank=0;
  for(int i=0; i<3; i++)
  {
    for(int y=0; y<3; y++)
    {
      rank = get_case_rank(game, player, i, y);
      if(rank>bestRank) bestRank = rank;
    }
  }

  return bestRank;
}