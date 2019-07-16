/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:56:28 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:43:46 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		cone_fill(int fd, t_prim *prim, int index)
{
	prim[index].cone.tip = vec3_extract(fd);
	prim[index].cone.dir = vec3_extract(fd);
	prim[index].cone.dir = nrmz(prim[index].cone.dir);
	prim[index].cone.color = color_extract(fd);
	prim[index].cone.color = first_cap(prim[index].cone.color);
	prim[index].cone.angle = double_extract(fd);
	prim[index].type = CONE;
}
