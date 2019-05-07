/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:58:05 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/07 13:03:25 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			name_obj(char *line)
{
	int		i;
	int		len;
	const char	*obj_name[] = {"sphere", "plane", "cone", "cylinder", "light"};

	i = -1;
	len = sizeof(obj_name) / sizeof(char *);

	while (++i < len)
		if (ft_strcmp(obj_name[i], line) == 0)
			return (i);
	return (-1);
}

void		jojo(char *file)
{
	int		i;
	int		fd;
	char	*line;
	typedef void (*check)(int);
	const check prim_obj[] = {&sphere_ch, &plane_ch, &cone_ch, &cylinder_ch,
	&light_ch};

	if ((fd = open(file, O_RDONLY)) < 0)
		fail(1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
			continue ;
		if ((i = name_obj(line)) != -1)
			prim_obj[i](fd);
		else
		{
			free(line);
			fail(1);
		}
		free(line);
	}
}
