/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:32:50 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:42:57 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <stdio.h>

void		sphere_fill(int fd, t_prim *prim, int index)
{
	prim[index].sphere.center = vec3_extract(fd);
	prim[index].sphere.radius = double_extract(fd);
	prim[index].sphere.color = color_extract(fd);
	prim[index].sphere.color = first_cap(prim[index].sphere.color);
	prim[index].type = SPHERE;
}
