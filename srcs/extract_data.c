/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:48:33 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/09 11:36:06 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			get_power(int nb)
{
	int		power;

	power = 10;
	while (nb > 0)
	{
		if (nb / power == 0)
			return (power);
		power *= 10;
	}
	return (power);
}

double		get_double(char **split)
{
	double	res;
	double	first;
	double	second;
	double	split1;
	double	split2;

	first = ft_atoi(split[0]);
	split1 = (double)ft_atoi(split[1]);
	split2 = get_power((double)ft_atoi(split[1]));
	second = split1 / split2;
	res = first + second;
	return (res);
}

t_vector	vec3_extract(int fd)
{
	t_vector	res;
	int			i;
	char		*line;
	char		**split;
	char		**split2[3];

	i = -1;
	if (get_next_line(fd, &line) <= 0)
		fail(4);
	if (!(split = ft_strsplit(line, ' ')))
		fail(3);
	res.x = vec3_extract_x(split, split2);
	res.y = vec3_extract_y(split, split2);
	res.z = vec3_extract_z(split, split2);
	free_tab(split, 3);
	free(line);
	return (res);
}

t_color		color_extract(int fd)
{
	t_color		res;
	char		*line;
	char		**split;

	if (get_next_line(fd, &line) <= 0)
		fail(4);
	if (!(split = ft_strsplit(line, ' ')))
		fail(3);
	res.r = ft_atoi(split[0]);
	res.g = ft_atoi(split[1]);
	res.b = ft_atoi(split[2]);
	free_tab(split, 3);
	free(line);
	return (res);
}

double		double_extract(int fd)
{
	double		res;
	char		*line;
	char		**split;

	if (get_next_line(fd, &line) <= 0)
		fail(4);
	if (str_isdot(line) == 1)
	{
		if (!(split = ft_strsplit(line, '.')))
			fail(3);
		res = get_double(split);
		free_tab(split, 2);
	}
	else
	{
		res = ft_atoi(line);
		(void)split;
	}
	free(line);
	return (res);
}
