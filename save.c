#include "definition.h"
#include "save.h"

char *replace(char *char_string)
{
  char *carriage_return = NULL;
  carriage_return = strchr(char_string, '\n');
  if (carriage_return != NULL)
  {
      *carriage_return = '\0';
  }
  else
  {
    while(getchar()!='\n');
  }

  return strdup(char_string);
}

void carriage_return_file(FILE* fichier)
{
  char buff;
  do
  {
    buff = fgetc(fichier);
  } while(buff!='\n'&&buff!=EOF);
}

char *get_player(FILE* fichier, long line, int player_number)
{
  char player[17];

  fseek(fichier, line, SEEK_SET);

  if (player_number == PLAYER_2)
  {
    for (int i = 0; i < 2; i++)
    {
      carriage_return_file(fichier);
    }
  }

  fgets(player, 18, fichier);

  replace(player);

  return strdup(player);
}

int get_player_win(FILE* fichier, long line, int player_number)
{
  int nb_win;

  fseek(fichier, line, SEEK_SET);

  if (player_number == PLAYER_1)
  {
    carriage_return_file(fichier);

    fscanf(fichier, "%d", &nb_win);
  }

  else
  {
    for (int i = 0; i < 3; i++)
    {
      carriage_return_file(fichier);
    }
    fscanf(fichier, "%d", &nb_win);
  }

  return nb_win;
}

long check_versus(FILE* fichier, info_player_s Infos_players[])
{
  char buff[2][17];
  long line=0, end;
  int same=0;

  fseek(fichier, 0,SEEK_END);
  end=ftell(fichier);

  fseek(fichier, 0, SEEK_SET);

  while (line<end&&same!=2)
  {
		same = 0;
    fseek(fichier, line, SEEK_SET);

    strcpy(buff[0],get_player(fichier, line, PLAYER_1));

    strcpy(buff[1],get_player(fichier, line, PLAYER_2));

    fseek(fichier, line, SEEK_SET);

		for (int i = 0; i<2; i++)
		{
			if (same !=2)
			{
				same = 0;
			}

			if (strcmp(buff[i],Infos_players[0].player_name)==0&&same==0)
			{
				same ++;
				
				if (strcmp(buff[(i+1)%2],Infos_players[1].player_name)==0)
				{
					same ++;
				}
			}
		}

    if (same != 2)
    {
      for (int i = 0; i < 4; i++)
      {
        carriage_return_file(fichier);
      }
      line = ftell(fichier);
    }
  }
	fseek(fichier, 0, SEEK_END);
	
  return line;
}

int total_game(FILE* fichier, long line)
{
  int total = 0;

  total += get_player_win(fichier, line, PLAYER_1);
  total += get_player_win(fichier, line, PLAYER_2);

  return total;
}

void display_scoreboard(FILE* fichier)
{
  char buff[2][17];
  long line=0, end;
  int same=0;

	CLEAR();

  fseek(fichier, 0,SEEK_END);
  end=ftell(fichier);

  fseek(fichier, 0, SEEK_SET);

  if (end==0)
	{
		WARNING("Il n'y a pas encore de partie enregistrées\n");
	}
	
	else
	{
		while (line<end&&same==0)
		{
			fseek(fichier, line, SEEK_SET);

			strcpy(buff[0],get_player(fichier, line, PLAYER_1));

			strcpy(buff[1],get_player(fichier, line, PLAYER_2));

			printf(BOLD"%s" BLINK " VS " RESET BOLD"%s\n"RESET, buff[0], buff[1]);
			printf(BOLD"Total de match en opposition"RESET" : %d match(s)\n", total_game(fichier, line));
			printf(BOLD"%s"RESET" : %d victoire(s)\n"BOLD"%s"RESET": %d victoire(s)\n", buff[0], get_player_win(fichier, line, PLAYER_1), buff[1], get_player_win(fichier, line, PLAYER_2));

			fseek(fichier, line, SEEK_SET);

			for (int i = 0; i < 4; i++)
			{
				carriage_return_file(fichier);
			}
			line = ftell(fichier);
			printf("\n");
		}
	}
}

int get_total_match_winner(FILE* fichier, info_player_s Infos_players[], int winner)
{
  int total=0;

  char buff[2][17];
  long line=0, end;

  fseek(fichier, 0,SEEK_END);
  end=ftell(fichier);

  fseek(fichier, 0, SEEK_SET);

  while (line<end)
  {
    fseek(fichier, line, SEEK_SET);

    strcpy(buff[0],get_player(fichier, line, PLAYER_1));

    strcpy(buff[1],get_player(fichier, line, PLAYER_2));

    if (strcmp(buff[0],Infos_players[winner].player_name)==0)
    {
      total += get_player_win(fichier,line,PLAYER_1);
    }

    if (strcmp(buff[1],Infos_players[winner].player_name)==0)
    {
      total += get_player_win(fichier,line,PLAYER_2);
    }

    fseek(fichier, line, SEEK_SET);

    for (int i = 0; i < 4; i++)
    {
      carriage_return_file(fichier);
    }
    line = ftell(fichier);
  }

  return total;
}

void add_in_file(FILE* fichier, info_player_s Infos_players[], long line)
{
  long end;
  fseek(fichier, 0, SEEK_END);
  end = ftell(fichier);
  fseek(fichier, line, SEEK_SET);

  if (end==0)
  {
    fprintf(fichier, "%s\n", Infos_players[0].player_name);
    fputs("0\n", fichier);
    fprintf(fichier, "%s\n", Infos_players[1].player_name);
    fputs("0", fichier);
  }

  else if (end==line)
  {
    fprintf(fichier, "\n%s\n", Infos_players[0].player_name);
    fputs("0\n", fichier);
    fprintf(fichier, "%s\n", Infos_players[1].player_name);
    fputs("0", fichier);
  }
}

void add_win(FILE* fichier, info_player_s Infos_players[], int winner)
{
  char buff[2][17];
  int total;
  long line = check_versus(fichier, Infos_players), line_win;

	strcpy(buff[0],get_player(fichier, line, PLAYER_1));

  strcpy(buff[1],get_player(fichier, line, PLAYER_2));

  fseek(fichier, line, SEEK_SET);

	if (strcmp(buff[0], buff[1])==0)
	{
		if (winner==0)
		{
			carriage_return_file(fichier);

			line_win = ftell(fichier);

			total = get_player_win(fichier,line,PLAYER_1);
		}

		else if (winner==1)
		{
			for (int i = 0; i < 3; i++)
			{
				carriage_return_file(fichier);
			}

			line_win = ftell(fichier);

			total = get_player_win(fichier,line,PLAYER_2);
		}
	}

  else if (strcmp(buff[0],Infos_players[winner].player_name)==0)
  {
    carriage_return_file(fichier);

    line_win = ftell(fichier);

    total = get_player_win(fichier,line,PLAYER_1);
  }

  else if (strcmp(buff[1],Infos_players[winner].player_name)==0)
  {
    for (int i = 0; i < 3; i++)
    {
      carriage_return_file(fichier);
    }

    line_win = ftell(fichier);

    total = get_player_win(fichier,line,PLAYER_2);
  }

  fseek(fichier, line_win, SEEK_SET);
  fprintf(fichier, "%d", total+1);
}

void clear_scoreboard()
{
  FILE *fichier = NULL;
  fichier=fopen("save.txt","w");

  if(fichier!=NULL)
  {
		WARNING("Le scoreboard à été effacé\n");
  }

  fclose(fichier);
}