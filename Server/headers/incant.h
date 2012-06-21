#ifndef __INCANT_H__
#define __INCANT_H__

size_t	check_players(t_list *, int);
void	level_up(t_square);
void	fill_hashcode(t_hash, t_square);
t_bool	incant_is_ok(t_incant);
t_bool	init_incant(t_incant, t_player, t_square, int);
void	iter_incant(void *, size_t);
int	incant_cleaner(void *, size_t);

#endif