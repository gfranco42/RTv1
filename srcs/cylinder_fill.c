/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:57:27 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:43:12 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		cylinder_fill(int fd, t_prim *prim, int index)
{
	prim[index].cyl.center = vec3_extract(fd);
	prim[index].cyl.dir = vec3_extract(fd);
	prim[index].cyl.dir = nrmz(prim[index].cyl.dir);
	prim[index].cyl.color = color_extract(fd);
	prim[index].cyl.color = first_cap(prim[index].cyl.color);
	prim[index].cyl.radius = double_extract(fd);
	prim[index].type = CYLINDER;
}
