/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:10:31 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/17 17:30:25 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		camera_fill(int fd, t_prim *prim, int index)
{
	prim[index].cam.pos = vec3_extract(fd);
	prim[index].cam.target = vec3_extract(fd);
	prim[index].cam.target = normalize(prim[index].cam.target);
	prim[index].cam.up = vec3_extract(fd);
	prim[index].cam.up = normalize(prim[index].cam.up);
	prim[index].type = CAMERA;
}
