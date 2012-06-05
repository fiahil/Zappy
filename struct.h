typedef struct s_sockLayer t_sockLayer;
typedef struct s_clientManager t_clientManager; // Pointeur sur sockLayer + queue pour contenir des buffer (string) + bool pour le parsing sur /r /n

enum	bool
  {
    FALSE,
    TRUE
  }

enum	splitMode		
  {
    CRLF,
    LF
  }

struct s_sockLayer
{
  int	fd; // client
  struct sockaddr ; // truc qu'on recoit quand on fait un accept
};

struct s_clientManager
{
  t_sockLayer * ;
  list<char *> ; // queue d'entree
  list<char *> ; // queue de sortie
  splitMode ;
};
