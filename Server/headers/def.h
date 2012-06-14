/*
 * Texan
 * 05.06.2012
 */

#ifndef __DEF_H__
#define __DEF_H__

#include	<sys/epoll.h>
#include	<netinet/in.h>		// IPPROTO_TCP
#include	<sys/time.h>
#include	"c_lists.h"

/*
 * System typedef
 */

typedef struct sockaddr*	t_sockAddr;
typedef struct sockaddr		t_u_sockAddr;

typedef struct sockaddr_in*	t_sockAddrIn;
typedef struct sockaddr_in	t_u_sockAddrIn;

/*
 * Struct typedef
 */

typedef struct s_epoll_manager*	t_epoll_manager;
typedef struct s_sockLayer*	t_sockLayer;
typedef struct s_clientManager*	t_clientManager;

typedef struct s_epoll_manager	t_u_epoll_manager;
typedef struct s_sockLayer	t_u_sockLayer;
typedef struct s_clientManager	t_u_clientManager;

typedef struct s_parse_elem	t_u_parse_elem;

typedef struct s_pos		t_u_pos;

typedef struct s_inventory	t_u_inventory;
typedef struct s_inventory*	t_inventory;

typedef struct s_player		t_u_player;
typedef struct s_player*	t_player;

typedef struct s_player_action	t_u_player_action;
typedef struct s_player_action*	t_player_action;

typedef struct s_square		t_u_square;
typedef struct s_square*	t_square;

typedef struct s_map		t_u_map;
typedef struct s_map*		t_map;

typedef struct timeval		t_u_timeval;
typedef struct timeval*		t_timeval;

/*
 * Enum typedef
 */

#define BUFFER_SIZE (4096)

typedef enum
{
  FALSE,
  TRUE
} t_bool;

typedef enum
{
  CRLF,
  LF,
  UNKNOW
} t_splitMode;

/*
 * Ptrfunc
 */

typedef t_bool	(*procFunc)(t_clientManager, char *);

/*
 * Struct definition
 */

struct s_map
{
  int		size_x;
  int		size_y;
  t_square	**map;
};

struct s_inventory
{
  t_list	*steak;
  t_list	*lin;
  t_list	*der;
  t_list	*sib;
  t_list	*men;
  t_list	*phi;
  t_list	*thy;
};

struct s_square
{
  t_list	client;
  t_u_inventory	inv;
};

struct	s_pos
{
  int	x;
  int	y;
};

struct s_player
{
  int		lvl;
  char		*team;
  t_u_pos	pos;
  t_u_inventory	inv;
};

struct s_player_action
{
  void		(*player_action_ptr)(void); // TODO typedef
  //t_u_timer	time;
  t_player	player;
};

struct s_parse_elem
{
  int		size;
  char const	*cmd;
  procFunc	func;
};

struct s_sockLayer
{
  int		fd;
  struct sockaddr_in	addr;
};

struct s_clientManager
{
  char		stock[BUFFER_SIZE];
  t_sockLayer	sock;
  t_u_player	player;
  t_list	*in; // queue d'entree
  t_list	*out; // queue de sortie
  t_splitMode	mode;
  t_bool	online;
  t_bool	dead;
  t_bool	is_processing;
};

struct s_epoll_manager
{
  int			efd;
  struct epoll_event	event;
  struct epoll_event	*ev;
};

#endif /* __DEF_H__ */
