/*
** stdout.h for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 13:04:01 2012 ulric lefevre
** Last update Mon Jun 25 14:45:07 2012 ulric lefevre
*/

#ifndef		__STDOUT_H__
# define	__STDOUT_H__

#include	"get_arg.h"

void		stdout_logo();
void		stdout_serv_status(const char *, int);
void		stdout_data_serv(t_arg*);
void		stdout_player_status(const char *, int);
void		stdout_player_input(char *, int);
void		stdout_player_output(char *, int);
void		stdout_player_action(const char *, int);
void		stdout_map();

#endif		/* !__STDOUT_H__ */
