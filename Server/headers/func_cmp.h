/*
** func_cmp.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:49:13 2012 ulric lefevre
** Last update Mon Jul  9 19:20:40 2012 ulric lefevre
*/

#ifndef		__FUNC_CMP_H__
# define	__FUNC_CMP_H__

int		cmp_player_list(void *, size_t, void *, size_t);
int		cmp_team(void *, size_t, void *, size_t);
int		cmp_incant(void *, size_t, void *, size_t);
int		cmp_action(void *, size_t, void *, size_t);
int		cmp_noghost(void *, size_t);
char		cmp_time(t_timeval, t_timeval);

#endif		/* !__FUNC_CMP_H__ */
