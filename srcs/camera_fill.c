/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:10:31 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/06 12:13:15 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		camera_fill(int fd, t_prim *prim, int index)
{
	prim[index].camera.pos = vec3_extract(fd);
	prim[index].camera.target = vec3_extract(fd);
	prim[index].camera.up = vec3_extract(fd);
	prim[index].type = 5;
}
