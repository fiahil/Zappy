/*
 * Texan
 * 05.06.2012
 */

#ifndef __DEF_H__
#define __DEF_H__

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

typedef struct s_sockLayer*	t_sockLayer;
typedef struct s_clientManager*	t_clientManager;

typedef struct s_sockLayer	t_u_sockLayer;
typedef struct s_clientManager	t_u_clientManager;

// Pointeur sur sockLayer + queue pour contenir des buffer (string) + bool pour le parsing sur /r /n

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
  LF
} t_splitMode;

/*
 * Struct definition
 */

struct s_sockLayer
{
  int		fd;
  t_u_sockAddrIn	addr;
};

struct s_clientManager
{
  char		stock[BUFFER_SIZE];
  t_sockLayer	sock;
  //t_list	in; // queue d'entree
  //t_list	out; // queue de sortie
  t_splitMode	mode;
};

#endif /* __DEF_H__ */
