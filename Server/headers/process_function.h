/*
** process_function.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:23 2012 ulric lefevre
** Last update Sun Jun 24 21:30:31 2012 ulric lefevre
*/

#ifndef		__PROCESS_FUNCTION_H__
# define	__PROCESS_FUNCTION_H__

t_bool	move_process(t_player, char *, t_data_serv);
t_bool	right_process(t_player, char *, t_data_serv);
t_bool	left_process(t_player, char *, t_data_serv);
t_bool	look_process(t_player, char *, t_data_serv);
t_bool	inventory_process(t_player, char *, t_data_serv);
t_bool	take_process(t_player, char *, t_data_serv);
t_bool	drop_process(t_player, char *, t_data_serv);
t_bool	expulse_process(t_player, char *, t_data_serv);
t_bool	broadcast_process(t_player, char *, t_data_serv);
t_bool	incantation_process(t_player, char *, t_data_serv);
t_bool	fork_process(t_player, char *, t_data_serv);
t_bool	connect_nbr_process(t_player, char *, t_data_serv);
char	*get_look(t_player, t_map);
void	message(t_player, t_player, char*);
int	cmp_player_list(void *, size_t, void *, size_t);

#endif		/* __PROCESS_FUNCTION_H__ */
