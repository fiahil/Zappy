/*
** stdout_serv.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 13:19:18 2012 ulric lefevre
** Last update Tue Jun 26 12:06:03 2012 ulric lefevre
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"get_arg.h"
#include	"algorithm.h"

void            stdout_logo()
{
  char		str[85];
  FILE		*logo;

  if ((logo = fopen("logo", "r")) != NULL)
    {
      printf("\033[1;31m");
      while (fgets(str, 84, logo) != NULL)
	printf("%s", str);
      printf("\n\n\033[0m");
    }
}

void            stdout_serv_status(const char *str, int flag)
{
  if (flag)
    {
      printf("\033[1;35m");
      printf("%d\t\tServer : %s", (int)time(NULL), str);
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;33m");
      printf("%d\t\tServer : %s", (int)time(NULL), str);
      printf("\033[0m");
    }
}

static void	print_list(void *data, size_t size)
{
  (void)size;
  printf("\t\tname : %s -> size : %d\n",
         ((t_team)data)->name, ((t_team)data)->remaining);
}

void            stdout_data_serv(t_arg *args)
{
  printf("\033[1;33m");
  printf("Server Infos :\n");
  printf("\t\tPort : %d\n", args->port);
  printf("\t\tExecution time : %d\n", args->exec_time);
  printf("World Infos : \n");
  printf("\t\tWidth : %d\n", args->width);
  printf("\t\tHeight : %d\n", args->height);
  printf("Teams Infos : \n");
  list_for_each(args->teams, &print_list);
  printf("\t\tClients per team : %d\n\n", args->nb_per_team);
  printf("\033[0m");
}
