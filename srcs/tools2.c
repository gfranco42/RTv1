/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:13:41 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/25 15:14:02 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		color_add(t_color c1, t_color c2)
{
	t_color		color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}
