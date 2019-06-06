/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:26:25 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/06 12:37:19 by gfranco          ###   ########.fr       */
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
