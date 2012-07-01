/*
** func_cleaner.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:20:33 2012 ulric lefevre
** Last update Sun Jul  1 14:23:44 2012 ulric lefevre
*/

#ifndef		__FUNC_CLEANER_H__
# define	__FUNC_CLEANER_H__

int		del_player_action(void *, size_t);
t_player	get_current(t_player);
int		action_cleaner(void *, size_t);
int		player_cleaner(void *, size_t);
int		egg_cleaner(void *, size_t);
int		incant_cleaner(void *, size_t);
void		clean_all(t_data_serv);

#endif		/* !__FUNC_CLEANER_H__ */
