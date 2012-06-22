
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"clock.h"
#include	"player.h"

static int	g_id_egg = 0;

void		init_egg(t_egg egg, int t)
{
  egg->status = FALSE;
  egg->id = g_id_egg++;
  egg->fetus = create_player();
  get_current_time(&egg->timeout);
  egg->timeout.tv_usec = 0;
  egg->timeout.tv_sec += 360 / t;
}
