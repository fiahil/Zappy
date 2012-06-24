/*
** incant.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:20:17 2012 ulric lefevre
** Last update Sun Jun 24 21:31:50 2012 ulric lefevre
*/

#ifndef		__INCANT_H__
# define	__INCANT_H__

size_t	check_players(t_list *, int);
void	level_up(t_incant);
void	fill_hashcode(t_hash, t_square);
t_bool	incant_is_ok(t_incant);
t_bool	init_incant(t_incant, t_player, t_square, int);

#endif		/* !__INCANT_H__ */
