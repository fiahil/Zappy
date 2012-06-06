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
  t_sockLayer * ;
  list<char *> ; // queue d'entree
  list<char *> ; // queue de sortie
  splitMode ;
};
