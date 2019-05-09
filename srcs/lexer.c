/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:11:46 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/07 17:48:54 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			name_obj(char *line, int *number)
{
	int		i;
	const char	*obj_name[] = {"sphere", "plane", "cone", "cylinder", "light"};

	i = -1;
	*number = sizeof(obj_name) / sizeof(char *);

	while (++i < *number)
		if (ft_strcmp(obj_name[i], line) == 0)
			return (i);
	return (-1);
}

int			lexer(char *file, int number)
{
	int		i;
	int		fd;
	char	*line;
	typedef void	(*t_check)(int);
	const t_check prim_obj[] = {&sphere_ch, &plane_ch, &cone_ch, &cylinder_ch,
	&light_ch};

	number = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		fail(1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
			continue ;
		if ((i = name_obj(line, &number)) != -1)
			prim_obj[i](fd);
		else
		{
			free(line);
			fail(1);
		}
		free(line);
	}
	return (number);
}
