/*
** sig_manager.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  8 14:09:44 2012 ulric lefevre
** Last update Sun Jul  8 14:25:34 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"var_manager.h"
#include	"func_cleaner.h"

void		sig_end()
{
  t_data_serv	ds;

  ds = get_data_serv(NULL);
  clean_all(ds);
  exit(EXIT_FAILURE);
}
