/*
** graphic.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:20:25 2012 ulric lefevre
** Last update Fri Jul  6 16:18:01 2012 ulric lefevre
*/

#ifndef		__GRAPHIC_H__
# define	__GRAPHIC_H__

#include	"def.h"

void	graphic_routine_input(t_data_serv, t_graphic);
void	iter_graphic_rds(void *, size_t);

void	msz_process(t_graphic, char *, t_data_serv);
void	bct_process(t_graphic, char *, t_data_serv);
void	mct_process(t_graphic, char *, t_data_serv);
void	tna_process(t_graphic, char *, t_data_serv);
void	ppo_process(t_graphic, char *, t_data_serv);
void	plv_process(t_graphic, char *, t_data_serv);
void	pin_process(t_graphic, char *, t_data_serv);
void	sgt_process(t_graphic, char *, t_data_serv);
void	sst_process(t_graphic, char *, t_data_serv);

void    welcome_graphic(t_data_serv, t_player);
void	drop_graphic(t_list *, t_player, t_square, int);
void	take_graphic(t_list *, t_player, t_square, int);
void	expulse_graphic(t_list *, t_player, t_list *);
void	monitor_graphic(t_graphic, t_data_serv, t_player);
void	player_graphic(t_list *, t_player);
void	incend_graphic(t_data_serv, t_incant);

void	ppo_general(t_list *, t_player);
void	pin_general(t_list *, t_player);
void	bct_general(t_list *, t_square, t_pos);
void	plv_general(t_list *, int, int);

void	pnw(t_list *, t_player);
void	ppo(t_graphic, t_player);
void	plv(t_graphic, int, int);
void	pin(t_graphic, t_player);
void	pex(t_list *, int);
void	pbc(t_list *, int, char *);
void	pic(t_list *, t_incant, t_list *);
void	pie(t_list *, t_incant);
void	pfk(t_list *, int);
void	pdr(t_list *, int, int);
void	pgt(t_list *, int, int);
void	pdi(t_list *, int);

void	sbp(t_list*);
void	suc(t_list*);
void	smg(t_list*, char const*);
void	edi(t_list*, int);
void	ebo(t_list*, int);
void	eht(t_list*, int);
void	enw(t_list*, int, int, t_pos);

void	sgt(t_graphic, int);
void	msz(t_graphic, size_t, size_t);
void	tna(t_graphic, t_list*);
void	bct(t_graphic, t_square, t_pos);
void	bct_all(t_graphic, t_map);

void	mn_push(t_list*, char*);
void	mn_out(t_list *);
void	mn_rep(t_graphic, char*);

#endif		/* __GRAPHIC_H__ */
