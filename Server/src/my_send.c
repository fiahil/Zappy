
#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"handle_error.h"

int	my_send(int fd, char *msg)
{
  if (send(fd, msg, strlen(msg), 0) == -1)
    return (handleError("send", strerror(errno), -1));
  return (0);
}
