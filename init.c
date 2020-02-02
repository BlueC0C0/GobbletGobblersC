#include "definition.h"
#include "bot.h"
#include "save.h"

//get player's informations
void add_info_player(info_player_s Infos_players[], int nb_player)
{
	int choiceColor, boolean;
	char name[17], *carriage_return=NULL;
	int tab_binary_color[6]={1,1,1,1,1,1};
 	char tab_color[6][8]={{"Rouge"},{"Vert"},{"Orange"},{"Bleu"},{"Violet"},{"Cyan"}};//the color available

	CLEAR();

	for (int num_player = 1; num_player<=NB_PLAYERS; num_player++)
	{
		if((num_player==1 || (num_player==2 && nb_player == 2)) && nb_player!=0)//for player customization
		{
			get_choice_name(Infos_players, nb_player, num_player);
			CLEAR();
			get_choice_color(Infos_players, nb_player, num_player, tab_binary_color);
			CLEAR();
		}
		else //for bot customization
		{
			bot_init(Infos_players, tab_binary_color, num_player);
			CLEAR();
		}
	}
}


//Initialize the game
player init_game(info_player_s Infos_players[], int* nb_player)
{
	int choice;
	long line;
	FILE* fichier = NULL;

	fichier = fopen("save.txt", "r+");

	if (fichier == NULL)
	{
		clear_scoreboard();
		fichier = fopen("save.txt", "r+");
	}

	CLEAR();

	do
	{	
		choice = get_entry("1 : scoreboard\n2 : jouer\n" SELECT);
		if(choice==1)
		{
			CLEAR();
			display_scoreboard(fichier);

			do
			{
				choice = get_entry("1 : retourner au menu\n2 : réinitialiser le scoreboard\n" SELECT);
			}while(choice!=1&&choice!=2);

			CLEAR();

			if(choice==2)
			{
				clear_scoreboard();
			}

			choice=1;
		}

		else
		{
			CLEAR();
		}
	}while(choice!=2);

	*nb_player = get_nb_player();
	player current_player;
	add_info_player(Infos_players, *nb_player);
	
	current_player = Random(1,NB_PLAYERS);	//Get a random player
  	
	switch (current_player)
	{
 		case 1:
   		current_player = PLAYER_1;
			break;
		case 2:
			current_player = PLAYER_2;
	  	break;
		default :
			current_player = 0;
			break;
  }
	
	line = check_versus(fichier, Infos_players);

	add_in_file(fichier, Infos_players, line);
	
	fclose(fichier);

	return current_player;	//returns the first player who can play
}

int get_nb_player()
{
	int nb_player;

	while(1)
	{
		CLEAR();
		nb_player = get_entry(BOLD"Combien de joueur(s) ?"RESET"\n1 : 2 bots\n2 : 1 joueur et 1 bot\n3 : 2 joueurs\n"SELECT);
		
		if(nb_player == 1 || nb_player == 2 || nb_player == 3 ) break;
	}

	return (nb_player-1);
}

void get_choice_name(info_player_s Infos_players[], int nb_player, int num_player)
{
  char name[17], *carriage_return=NULL;
	int boolean = 1;
	
	while(boolean)
	{
		//CLEAR();
		printf("Nom du joueur n°%d (dans la limite de 15 caracteres):\n" SELECT,num_player);//get the player's name

		fgets(name,17,stdin);

		carriage_return = NULL;
		carriage_return = strchr(name, '\n');// delete the \n of the player's name

		if (carriage_return != NULL)
		{
			*carriage_return = '\0';
		}
		else
		{
			while(getchar()!='\n');
		}
		if(strlen(name)<=15&&strlen(name)>0&& (num_player-1)!=0)
		{
			printf("num player : %d\n", num_player);
			for (int k=0; k<num_player-1; k++)
			{
				if (strcmp(name,Infos_players[k].player_name)==0)//to compare if players have the same name
				{
					boolean = 1;
				}
				else
				{
					boolean = 0;
				}
			}

			if (boolean == 1)
			{
				CLEAR();
				WARNING("Vous ne pouvez pas avoir le même nom qu'un autre joueur.");
			}
		}

		else if(strlen(name)>15)
		{
			CLEAR();
			WARNING("Votre nom possede trop de caracteres.");
		}

		else if(strlen(name)==0)
		{
			CLEAR();
			WARNING("Votre n'avez entré aucun caractère.");
		}

		else
		{
			boolean = 0;
		}
	}

	strcpy(Infos_players[num_player-1].player_name,name);
}


void get_choice_color(info_player_s Infos_players[], int nb_player, int num_player, int tab_binary_color[])
{
	int boolean = 1;
	int choiceColor;
	char tab_color[6][8]={{"Rouge"},{"Vert"},{"Orange"},{"Bleu"},{"Violet"},{"Cyan"}};//the color available

	while(boolean)
	{
		printf(BOLD"%s"RESET", choisissez une couleur :\n", Infos_players[num_player-1].player_name);
		printf(WHITE"╔════════════╗\n"RESET);
		for(int y=0;y<6;y++)
		{
			if(tab_binary_color[y])
			{
				printf(WHITE"║%s%d° - %-7s"WHITE"║\n"RESET, choice_color_code(y+1), y+1, tab_color[y]);
			}//to display the colors which are availables 
		}
		printf(WHITE"╚════════════╝\n"RESET);

		choiceColor = get_entry(SELECT);
		for(int y=0;y<6;y++)// to verify if the color is available
		{
			if(tab_binary_color[y]==1 && choiceColor == y+1)
			{
				boolean=0;
			}
		}

		CLEAR();
		WARNING("La couleur demandée n'est pas disponible.");
	}
	
	tab_binary_color[choiceColor-1]=0;
	strcpy(Infos_players[num_player-1].color, choice_color_code(choiceColor));
}



    
