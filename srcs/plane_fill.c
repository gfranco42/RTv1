/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:55:08 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:43:25 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		plane_fill(int fd, t_prim *prim, int index)
{
	prim[index].plane.point = vec3_extract(fd);
	prim[index].plane.normal = vec3_extract(fd);
	prim[index].plane.normal = nrmz(prim[index].plane.normal);
	prim[index].plane.color = color_extract(fd);
	prim[index].plane.color = first_cap(prim[index].plane.color);
	prim[index].type = PLANE;
}
