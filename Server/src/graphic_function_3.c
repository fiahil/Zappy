void		pbc(t_list *mn, int id, char *msg)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pbc #%d %s\n", id, msg);
  mn_push(mn, str);
  free(str);
}

void		pic(t_list *mn, t_incant inc, t_list *player)
{
  char		*str;
  char		*tmp;
  t_iter	*it;

  str = NULL;
  tmp = NULL;
  asprintf(&str, "pic %d %d %d #%d", inc->pos.x, inc->pos.y, inc->incantor->lvl, inc->incantor->id);
  while (it)
    {
      if ((*(t_player*)(it->data))->id != inc->incantor->id)
	{
	  asprintf(&tmp, " #%d", (*(t_player*)(it->data))->id);
	  str = strcat(str, tmp);
	}
      it = it->next;
    }
  str = strcat(str, "\n");
  mn_push(mn, str);
  free(str);
}

void		pie(t_list *mn, t_incant inc)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pie %d %d %d\n", inc->pos.x, inc->pos.y, inc->status);
  mn_push(mn, str);
  free(str);
}

void		pfk(t_list *mn, int id)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pfk #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void		pdr(t_list *mn, int id, int res)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pdr #%d %d\n", id, res);
  mn_push(mn, str);
  free(str);
}