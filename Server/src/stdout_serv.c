/*
** stdout_serv.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 13:19:18 2012 ulric lefevre
** Last update Mon Jun 25 14:28:49 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"get_arg.h"
#include	"algorithm.h"

void            stdout_logo()
{
  printf("\033[1;31m");
  printf("            ,--,\n");
  printf("      _ ___/ /\\|\n");
  printf("    ;( )__, )\n");
  printf("   ; //   '--;");
  printf("\033[0m  -- Au poney fringant of the death --\n");
  printf("\033[1;31m");
  printf("     \\     |\n");
  printf("      ^    ^\n");
  printf("\033[0m");
}

void            stdout_serv_status(const char *str, int flag)
{
  if (flag)
    printf("\033[1;31m%s\n\033[0m", str);
  else
    printf("\033[1;32m%s\n\033[0m", str);
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
  printf("\t\tClients per team : %d\n", args->nb_per_team);
  printf("\033[0m");
}
