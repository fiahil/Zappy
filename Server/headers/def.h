/*
 * Texan
 * 05.06.2012
 */

#ifndef		__DEF_H__
# define	__DEF_H__

#include	<sys/select.h>
#include	<netinet/in.h>
#include	<sys/time.h>
#include	"c_lists.h"
#include	"pqueue.h"

/*
 * System typedef
 */

typedef struct sockaddr*	t_sock_addr;
typedef struct sockaddr		t_u_sock_addr;

typedef struct sockaddr_in*	t_sock_addr_in;
typedef struct sockaddr_in	t_u_sock_addr_in;

/*
 * Struct typedef
 */

typedef struct s_hash*		t_hash;
typedef struct s_hash		t_u_hash;

typedef struct s_incant*	t_incant;
typedef struct s_incant		t_u_incant;

typedef struct s_egg*		t_egg;
typedef struct s_egg		t_u_egg;

typedef struct s_select_manager* t_select_manager;
typedef struct s_sock_layer*	t_sock_layer;
typedef struct s_client_manager*	t_client_manager;

typedef struct s_select_manager	t_u_select_manager;
typedef struct s_sock_layer	t_u_sock_layer;
typedef struct s_client_manager	t_u_client_manager;

typedef struct s_parse_elem	t_u_parse_elem;

typedef struct s_pos		t_u_pos;

typedef struct s_inventory	t_u_inventory;
typedef struct s_inventory*	t_inventory;

typedef struct s_player		t_u_player;
typedef struct s_player*	t_player;

typedef struct s_graphic	t_u_graphic;
typedef struct s_graphic*	t_graphic;

typedef struct s_player_action	t_u_player_action;
typedef struct s_player_action*	t_player_action;

typedef struct s_square		t_u_square;
typedef struct s_square*	t_square;

typedef struct s_map		t_u_map;
typedef struct s_map*		t_map;

typedef struct timeval		t_u_timeval;
typedef struct timeval*		t_timeval;

typedef struct s_team		t_u_team;
typedef struct s_team*		t_team;

typedef struct s_data_serv	t_u_data_serv;
typedef struct s_data_serv*	t_data_serv;

typedef struct s_time_attrib	t_u_time_attrib;

/*
 * Enum typedef
 */

#define BUFFER_SIZE	(4096)

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

typedef t_bool	(*t_proc_func)(t_player, char *, t_data_serv);

/*
 * Struct definition
 */

struct			s_map
{
  int			size_x;
  int			size_y;
  t_square		**map;
};

struct			s_inventory
{
  t_bool		status;
  int			cur_life;
  int			resources[LAST];
};

struct			s_square
{
  t_list		*players;
  t_u_inventory		inv;
};

struct			s_pos
{
  int			x;
  int			y;
};

struct			s_player_action
{
  t_proc_func		action;
  t_u_timeval		time;
  t_player		player;
  char			*param;
  t_bool		done;
};

struct			s_parse_elem
{
  int			size;
  char const		*cmd;
  t_proc_func		func;
};

struct			s_time_attrib
{
  t_proc_func		func;
  double		timer;
};

struct			s_sock_layer
{
  int			fd;
  t_u_sock_addr_in	addr;
};

struct			s_client_manager
{
  char			stock[BUFFER_SIZE];
  t_u_sock_layer	sock;
  t_list		*in;
  t_list		*out;
  t_splitMode		mode;
  t_bool		online;
  t_bool		is_processing;
};

struct			s_player
{
  int			id;
  int			lvl;
  char			*team;
  t_u_pos		pos;
  t_dir			dir;
  t_u_inventory		inv;
  t_bool		dead;
  t_bool		deleted;
  t_bool		welcome;
  t_u_client_manager	cm;
};

struct			s_graphic
{
  t_bool		welcome;
  t_u_client_manager	cm;
};

struct			s_egg
{
  int			id;
  t_player		fetus;
  t_u_timeval		timeout;
};

struct			s_hash
{
  int			nb_play;
  int			linemate;
  int			deraumere;
  int			sibur;
  int			mendiane;
  int			phiras;
  int			thystame;
};

struct			s_incant
{
  t_u_hash		hashcode;
  t_u_pos		pos;
  t_player		incantor;
  t_bool		status;
  t_u_timeval		timeout;
};

struct			s_data_serv
{
  t_u_sock_layer	sock;
  int			t;
  t_list		*monitor;
  t_list		*player;
  int			nb_per_team;
  t_list		*teams;
  t_pqueue		*action;
  t_list		*send_q;
  t_pqueue		*incant;
  t_list		*egg;
};

struct			s_team
{
  char			*name;
  int			remaining;
};

struct			s_select_manager
{
  int			max_fd;
  fd_set		rds;
  fd_set		wds;
  t_u_timeval		timeout;
};

#endif /* __DEF_H__ */
