/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:26:25 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/09 11:36:46 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		rgb_value(t_color color, double r, double g, double b)
{
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void		print_pixel(t_mlx mlx, t_tools tools, t_color color)
{
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = color.b;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = color.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = color.r;
}

double		vec3_extract_x(char **split, char ***split2)
{
	t_vector	res;

	if (str_isdot(split[0]) == 1)
	{
		if (!(split2[0] = ft_strsplit(split[0], '.')))
			fail(3);
		res.x = get_double(split2[0]);
		free_tab(split2[0], 2);
	}
	else
		res.x = ft_atoi(split[0]);
	return (res.x);
}

double		vec3_extract_y(char **split, char ***split2)
{
	t_vector	res;

	if (str_isdot(split[1]) == 1)
	{
		if (!(split2[1] = ft_strsplit(split[1], '.')))
			fail(3);
		res.y = get_double(split2[1]);
		free_tab(split2[1], 2);
	}
	else
		res.y = ft_atoi(split[1]);
	return (res.y);
}

double		vec3_extract_z(char **split, char ***split2)
{
	t_vector res;

	if (str_isdot(split[2]) == 1)
	{
		if (!(split2[2] = ft_strsplit(split[2], '.')))
			fail(3);
		res.z = get_double(split2[2]);
		free_tab(split2[2], 2);
	}
	else
		res.z = ft_atoi(split[2]);
	return (res.z);
}
