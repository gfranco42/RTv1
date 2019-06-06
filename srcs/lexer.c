/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:11:46 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/06 14:08:45 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		check_camera(int i, int *cam)
{
	if (i == 5)
	{
		*cam += 1;
		if (*cam != 1)
			fail(1);
	}
}

int			name_obj(char *line)
{
	int			i;
	int			number;
	const char	*obj_name[] = {"sphere", "plane", "cone", "cylinder", "light",
								"camera"};

	i = -1;
	number = sizeof(obj_name) / sizeof(char *);
	while (++i < number)
		if (ft_strcmp(obj_name[i], line) == 0)
			return (i);
	return (-1);
}

int			lexer(char *file, int number, int *cam)
{
	int				i;
	int				fd;
	char			*line;
	typedef void	(*t_check)(int);
	const t_check	prim_obj[] = {&sphere_ch, &plane_ch, &cone_ch, &cylinder_ch,
	&light_ch, &camera_ch};

	if ((fd = open(file, O_RDONLY)) < 0)
		fail(1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
			continue ;
		if ((i = name_obj(line)) != -1)
			prim_obj[i](fd);
		check_camera(i, cam);
		if (i == -1)
		{
			free(line);
			fail(1);
		}
		free(line);
		number++;
	}
	return (number);
}
