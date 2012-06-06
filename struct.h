typedef struct s_sockLayer t_sockLayer;
typedef struct s_clientManager t_clientManager; // Pointeur sur sockLayer + queue pour contenir des buffer (string) + bool pour le parsing sur /r /n

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

struct s_sockLayer
{
  int	fd;
  struct sockaddr ;
};

struct s_clientManager
{
  char		*current;
  t_sockLayer	*sock;
  t_list	in; // queue d'entree
  t_list	out; // queue de sortie
  t_splitMode	mode;
};
