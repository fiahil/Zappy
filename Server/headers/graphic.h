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

void	mn_push(t_list*, char*);
void	mn_out(t_list *);

#endif /* __GRAPHIC_H__ */
