
#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>

#include	"handle_error.h"

int	my_send(int fd, char *msg)
{
  if (send(fd, msg, strlen(msg), MSG_NOSIGNAL) == -1)
    return (handle_error("my_send", strerror(errno), -1));
  return (0);
}
