#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "def.h"

void	pnw(t_list *, t_player);
void	ppo(t_list *, t_player);
void	plv(t_list *, int, int);
void	pin(t_list *, t_player);
void	pex(t_list *, int);

void	sbp(t_list*);
void	suc(t_list*);
void	smg(t_list*, char const*);
void	seg(t_list*, int);
void	edi(t_list*, int);
void	ebo(t_list*, int);
void	eht(t_list*, int);
void	enw(t_list*, int, int, t_pos);

void	msz(t_graphic, size_t, size_t);
void	tna(t_graphic, t_list*);

void	mn_push(t_list*, char*);
void	mn_out(t_list *);
void	mn_rep(t_graphic, char*);

#endif /* __GRAPHIC_H__ */
