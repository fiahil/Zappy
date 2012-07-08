/*
** func_ctor_dtor.h for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  8 11:52:18 2012 ulric lefevre
** Last update Sun Jul  8 13:13:41 2012 ulric lefevre
*/

#ifndef		__FUNC_CTOR_DTOR_H__
# define	__FUNC_CTOR_DTOR_H__

void		*ctor_team(va_list);

void		dtor_team(void *);
void		dtor_player(void *);
void		dtor_egg(void *);

#endif		/* !__FUNC_CTOR_DTOR_H__ */
