/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:48:33 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:35:55 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	vec3_extract(int fd)
{
	t_vector	res;
	char		*line;
	char		**split;

	if (get_next_line(fd, &line) <= 0)
		fail(4);
	split = ft_strsplit(line, ' ');// split la line
	res.x = ft_atoi(split[0]);
	res.y = ft_atoi(split[1]);
	res.z = ft_atoi(split[2]);
	return (res);
}

t_color		color_extract(int fd)
{
	t_color		res;
	char		*line;
	char		**split;

	if (get_next_line(fd, &line) <= 0)
		fail(4);
	split = ft_strsplit(line, ' ');// split la line
	res.r = ft_atoi(split[0]);
	res.g = ft_atoi(split[1]);
	res.b = ft_atoi(split[2]);
	return (res);
}

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

double		double_extract(int fd)
{
	double		res;
	char		*line;

	if (get_next_line(fd, &line) <= 0)
		fail(4);
	if (str_isdot(line) == 1)
	{
		char	**split;
		split = ft_strsplit(line, '.');
		res = get_double(split);
	}
	else
		res = ft_atoi(line);
	return (res);
}
