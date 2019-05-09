/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:32:50 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:41:57 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		sphere_fill(int fd, t_prim *prim, int index)
{
	prim[index].sphere.center = vec3_extract(fd);
	prim[index].sphere.radius = double_extract(fd);
	prim[index].sphere.color = color_extract(fd);
}
