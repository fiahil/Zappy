
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"clock.h"
#include	"player.h"

static int	g_id_egg = 0;

void		init_egg(t_egg egg, t_player this, int t)
{
  egg->id = g_id_egg++;
  egg->fetus = create_player();
  egg->fetus->team = strdup(this->team);
  egg->fetus->pos.x = this->pos.x;
  egg->fetus->pos.y = this->pos.y;
  get_current_time(&egg->timeout);
  egg->timeout.tv_usec = 0;
  egg->timeout.tv_sec += 360 / t;
}
