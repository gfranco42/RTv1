/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/03 11:43:41 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <stdio.h>

t_vector	upleft_calc(t_base base)
{
	t_vector	upleft;
/*	t_vector	pos;

	pos.x = pos.x*/

	upleft.x = base.cam.dist * base.cam.forward.x + base.cam.h_view / 2
	* base.cam.vertical.x - base.cam.w_view / 2 * base.cam.right.x;
	printf("x: %lf\n", upleft.x);
	upleft.y = base.cam.dist * base.cam.forward.y + base.cam.h_view / 2
	* base.cam.vertical.y - base.cam.w_view / 2 * base.cam.right.y;
	printf("y: %lf\n", upleft.y);
	upleft.z = base.cam.dist * base.cam.forward.z + base.cam.h_view / 2
	* base.cam.vertical.z - base.cam.w_view / 2 * base.cam.right.z;
	printf("z: %lf\n", upleft.z);
	upleft = nrmz(upleft);
	return (upleft);
}

void		initialize_ray(t_cam cam, t_base *base)
{
	base->ray.origin = vec_add_double(cam.pos, 0);
	base->cam.pos = vec_add_double(cam.pos, 0);
	base->cam.target = vec_add_double(cam.target, 0);
	base->cam.up = vec_add_double(cam.up, 0);
	base->cam.forward = nrmz(vec_sub(base->cam.target, base->cam.pos));
	printf("forward x: %lf || y: %lf || z: %lf\n", base->cam.forward.x, base->cam.forward.y, base->cam.forward.z);
	base->cam.right = nrmz(cross(base->cam.forward, base->cam.up));
	printf("right x: %lf || y: %lf || z: %lf\n", base->cam.right.x, base->cam.right.y, base->cam.right.z);
	base->cam.vertical = nrmz(cross(base->cam.forward, base->cam.right));
	printf("vertical x: %lf || y: %lf || z: %lf\n", base->cam.vertical.x, base->cam.vertical.y, base->cam.vertical.z);
	base->cam.w_view = 0.5;
	base->cam.h_view = 0.5;
	base->cam.dist = 1.0;
}

void		calc_dir(t_vector upleft, t_base *base)
{
	base->ray.dir.x = upleft.x + base->cam.right.x * base->cam.w_view /
	(double)WIDTH * base->tools.x - base->cam.vertical.x * base->cam.h_view /
	(double)HEIGHT * base->tools.y;
	base->ray.dir.y = upleft.y + base->cam.right.y * base->cam.w_view /
	(double)WIDTH * base->tools.x - base->cam.vertical.y * base->cam.h_view /
	(double)HEIGHT * base->tools.y;
	base->ray.dir.z = upleft.z + base->cam.right.z * base->cam.w_view /
	(double)WIDTH * base->tools.x - base->cam.vertical.z * base->cam.h_view /
	(double)HEIGHT * base->tools.y;
	base->ray.dir = nrmz(base->ray.dir);
}

void		find_cam(t_i *i, t_prim *prim)
{
	while (++i->i < i->nb)
		if (prim[i->i].type == CAMERA)
			i->cm = i->i;
}

int			find_light(t_i i, t_prim *prim)
{
	int		j;

	j = -1;
	while (++j < i.nb)
		if (prim[j].type == LIGHT)
			return (j);
	return (j);
}
