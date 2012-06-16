
static int g_max_fd = 0;

void		set_max_fd(int fd)
{
  if (fd > g_max_fd)
    g_max_fd = fd;
}

int		get_max_fd()
{
  return (g_max_fd);
}
