/*
** max_fd.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:24 2012 ulric lefevre
** Last update Sun Jun 24 21:40:48 2012 ulric lefevre
*/

static int	g_max_fd = 0;

void		set_max_fd(int fd)
{
  if (fd > g_max_fd)
    g_max_fd = fd;
}

int		get_max_fd()
{
  return (g_max_fd);
}
