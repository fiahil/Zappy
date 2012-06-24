/*
** protocol.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:17 2012 ulric lefevre
** Last update Sat Jun 23 20:21:52 2012 ulric lefevre
*/

#ifndef		__PROTOCOL_H__
# define	__PROTOCOL_H__

void		protocol_avance(t_list*);
void		protocol_droite(t_list*);
void		protocol_gauche(t_list*);
void		protocol_voir(t_list*);
void		protocol_inventaire(t_list*);
void		protocol_prend_objet(t_list*, t_bool);
void		protocol_pose_objet(t_list*, t_bool);
void		protocol_expulse(t_list*, t_bool);
void		protocol_broadcast(t_list*);
void		protocol_incantation(t_list*);
void		protocol_fork(t_list*);
void		protocol_connect_nbr(t_list*);
void		protocol_mort(t_list*);

#endif		/* !__PROTOCOL_H__ */
