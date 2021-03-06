/*
** stdout_serv.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 13:19:18 2012 ulric lefevre
** Last update Fri Jul 13 16:27:49 2012 ulric lefevre
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<arpa/inet.h>

#include	"def.h"
#include	"get_arg.h"
#include	"algorithm.h"
#include	"var_manager.h"

void            stdout_logo()
{
  char		str[85];
  FILE		*logo;
  t_data_serv	ds;

  ds = get_data_serv(NULL);
  if (ds->verbose)
    {
      if ((logo = fopen("/usr/share/zappy/logo", "r")) != NULL
          || (logo = fopen("logo", "r")) != NULL)
	{
	  printf("\033[1;31m");
	  while (fgets(str, 84, logo) != NULL)
	    printf("%s", str);
	  printf("\033[0m\n\n");
	  fclose(logo);
	}
    }
}

void            stdout_serv_status(const char *str, int flag)
{
  t_data_serv	ds;

  ds = get_data_serv(NULL);
  if (ds->verbose)
    {
      if (flag)
	{
	  printf("\033[1;35m");
	  printf("%d\t\tServeur : %s", (int)time(NULL), str);
	  printf("\033[0m");
	}
      else
	{
	  printf("\033[1;33m");
	  printf("%d\t\tServeur : %s", (int)time(NULL), str);
	  printf("\033[0m");
	}
    }
}

static void	print_list(void *data, size_t size)
{
  (void)size;
  printf("\t\tNom : %s -> taille : %d\n",
         ((t_team)data)->name, ((t_team)data)->remaining);
}

void            stdout_data_serv(t_arg *args, t_data_serv ds)
{
  if (ds->verbose)
    {
      printf("\033[1;33m");
      printf("\nInfos du Serveur :\n");
      printf("\t\tIP : %s\n", inet_ntoa(ds->sock.addr.sin_addr));
      printf("\t\tPort : %d\n", args->port);
      printf("\t\tTemps d'execution : %d\n", args->exec_time);
      printf("Infos sur la map : \n");
      printf("\t\tLargeur : %d\n", args->width);
      printf("\t\tHauteur : %d\n", args->height);
      printf("Infos sur les equipes: \n");
      list_for_each(ds->teams, &print_list);
      printf("\t\tClients par equipe : %d\033[0m\n\n", args->nb_per_team);
    }
}
