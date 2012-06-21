
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"player.h"

static int	g_id_egg = 0;

void		init_egg(t_egg egg)
{
  egg->status = FALSE;
  egg->id = g_id_egg++;
  egg->fetus = create_player();
  egg->timeout.tv_usec = 0; // TODO
  egg->timeout.tv_sec = 3; // TODO
}
