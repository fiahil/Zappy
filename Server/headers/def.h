/*
 * Texan
 * 05.06.2012
 */

#ifndef __DEF_H__
#define __DEF_H__

#include	<sys/select.h>
#include	<netinet/in.h>
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

typedef struct s_select_manager* t_select_manager;
typedef struct s_sockLayer*	t_sockLayer;
typedef struct s_clientManager*	t_clientManager;

typedef struct s_select_manager	t_u_select_manager;
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

typedef struct s_data_serv	t_u_data_serv;
typedef struct s_data_serv*	t_data_serv;

typedef struct s_time_attrib	t_u_time_attrib;

/*
 * Enum typedef
 */

#define BUFFER_SIZE (4096)

typedef enum
{
  FOOD,
  LINEMATE,
  DERAUMERE,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME,
  LAST
} t_resource;

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

typedef enum
{
  NORTH,
  EAST,
  SOUTH,
  WEST
} t_dir;

/*
 * Ptrfunc
 */

typedef t_bool	(*procFunc)(t_player, char *);

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
  t_bool	status;
  int		resources[LAST];
};

struct s_square
{
  t_list	client;
  t_u_inventory	inv;
};

struct s_pos
{
  int		x;
  int		y;
};

struct s_player_action
{
  procFunc	action;
  t_u_timeval	time;
  t_player	player;
};

struct s_parse_elem
{
  int		size;
  char const	*cmd;
  procFunc	func;
};

struct s_time_attrib
{
  procFunc	func;
  double	timer;
};

struct s_sockLayer
{
  int		fd;
  struct sockaddr_in	addr;
};

struct s_clientManager
{
  char		stock[BUFFER_SIZE];
  t_u_sockLayer	sock;
  t_list	*in;
  t_list	*out;
  t_splitMode	mode;
  t_bool	online;
  t_bool	is_processing;
};

struct s_player
{
  int		lvl;
  char		*team;
  t_u_pos	pos;
  t_dir		dir;
  t_u_inventory	inv;
  t_bool	dead;
  t_bool	welcome;
  t_u_clientManager	cm;
};

struct s_data_serv
{
  t_u_sockLayer	sock;
  t_list	*player;
  t_list	*action;
  t_list	*send_q;
};

struct s_select_manager
{
  int		max_fd;
  fd_set	rds;
  t_u_timeval	timeout;
};

#endif /* __DEF_H__ */
