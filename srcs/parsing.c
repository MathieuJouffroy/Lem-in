/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:08:48 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 22:00:54 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		gnl_exit(char *line)
{
	ft_strdel(&line);
	return (0);
}

int		success_exit(char *line)
{
	ft_strdel(&line);
	return (1);
}

void	add_line_and_delete(t_lemin *lemin, char *line)
{
	add_line_to_str(lemin, line);
	ft_strdel(&line);
}

int		is_data_sufficient(t_lemin *lemin)
{
	if (!(lemin->state & S_LINKS) || !(lemin->state & S_START)
	|| !(lemin->state & S_END) || !lemin->nb_ants)
	{
		ft_printf("{red}ERROR:{reset} not enough data : ");
		ft_printf("missing source, sink, links or ants\n");
		return (0);
	}
	return (1);
}

int		parsing(t_lemin *lemin)
{
	char		*line;

	line = NULL;
	while (get_next_line(FD, &line) == 1)
	{
		if (is_command(line))
			add_command_to_state(lemin, line);
		else if (is_comment(line))
			add_line_and_delete(lemin, line);
		else if (ft_str_is_digit(line) && !lemin->nb_ants)
		{
			if (!get_ants(lemin, line))
				return (0);
		}
		else if (links_formatting(lemin, line))
		{
			if (!parse_links(lemin, line))
				return (0);
		}
		else if (!(lemin->state & S_LINKS) && (lemin->nb_ants))
		{
			if (!parse_room(lemin, line))
				return (0);
		}
		else
			ft_strdel(&line);
	}
	return (is_data_sufficient(lemin));
}
