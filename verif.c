#include <ctype.h>
#include "board.h"
#include "definition.h"

//to change the color of the terminal font
char *cl(board game, info_player_s Infos_players[], int column, int line)
{
  char buff[TAILLE], size[2];
  int player = get_place_holder(game, column, line);

  if (player==NONE)//if there is no player in the box
  {
    strcpy(buff, " \0");
  }
  else
  {
    strcpy(buff,Infos_players[player-1].color);//get player's color
    sprintf(size, "%d", get_piece_size(game, column, line));//get piece size
    strcat(buff, BOLD);//copy the font decoration's code of bold in buff
    strcat(buff, size);//copy the piece size in buff
    strcat(buff, RESET WHITE);//copy the reset and white code in buff
  }
  return strdup(buff);//return buff
}

//permit to get the terminal code color in terms of player choice.
char *choice_color_code(int num_color)
{
  char buff[TAILLE];

  switch(num_color)
  {
    case 1:
      strcpy(buff,RED);
    break;
    case 2:
      strcpy(buff,GREEN);
    break;
    case 3:
      strcpy(buff,ORANGE);
    break;
    case 4:
      strcpy(buff,BLUE);
    break;
    case 5:
      strcpy(buff,PURPLE);
    break;
    case 6:
      strcpy(buff,CYAN);
    break;
  }
  return strdup(buff);
}

//a security int entry.
int get_entry(char sentence[])
{
  char *endPtr = NULL, choice[3];
  int is_not_int=1;
	long value;
	printf("%s", sentence);//print the entry sentence in parameter
	while(is_not_int)
	{
		fgets(choice, 3, stdin);

		char *endPtr = NULL;
		endPtr = strchr(choice, '\n');//get the @ of a possible \n in sentence
		
		if (endPtr != NULL)	//if there is a \n in sentence
		{
			*endPtr = '\0';	//changes the \n to a \0

			endPtr = NULL;

			long value = strtol(choice, &endPtr, 10 );

			if ((*endPtr=='\0'&&value!=0) || strcmp(endPtr,"q")==0)
			{
				is_not_int = 0;
				
				if (strcmp(endPtr,"q")==0)
				{
					return -1;
				}
			}

			else if (endPtr == choice || *endPtr!='\0' || value==0)
			{
				WARNING("Saisie non valide");
				printf(SELECT);
			}
		}
		else
		{
			while(getchar()!='\n');	//empty the buffer if there is a memory overflow
			WARNING("Saisie non valide");
			printf(SELECT);
		}
	}
 
  return atoi(choice);//return choice.
}

//get the line and column value of the box number. 
void get_destination(int *line, int *column, int dest)
{
  switch (dest)
  {
    case QUIT:
      *line = QUIT;
      break;
    case 1:
      *line = 0;
      *column = 0;
      break;
    case 2:
      *line = 0;
      *column = 1;
      break;
    case 3:
      *line = 0;
      *column = 2;
      break;
    case 4:
      *line = 1;
      *column = 0;
      break;
    case 5:
      *line = 1;
      *column = 1;
      break;
    case 6:
      *line = 1;
      *column = 2;
      break;
    case 7:
      *line = 2;
      *column = 0;
      break;
    case 8:
      *line = 2;
      *column = 1;
      break;
    case 9:
      *line = 2;
      *column = 2;
      break;
    default :
      *line = 3;
      *column = 3;
      break;
  }
}
