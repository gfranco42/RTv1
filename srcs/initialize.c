/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/18 17:43:40 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		initialize_ray(t_cam cam, t_base *base)
{
	base->ray.origin = vec_add_double(cam.pos, 0);
	base->cam.pos = vec_add_double(cam.pos, 0);
	base->cam.target = vec_add_double(cam.target, 0);
	base->cam.up = vec_add_double(cam.up, 0);
	base->cam.forward = normalize(vec_sub(base->cam.target, base->cam.pos));
	base->cam.right = normalize(cross(base->cam.forward, base->cam.up));
	base->cam.vertical = normalize(cross(base->cam.right, base->cam.forward));
	base->cam.w_view = 1.0;
	base->cam.h_view = 1.0;
	base->cam.dist = 0.5;
}

void		calc_dir(t_vector upleft, t_base *base)
{
	base->ray.dir.x = upleft.x + base->cam.right.x * base->cam.h_view
	/ WIDTH * base->tools.x - base->cam.up.x * base->cam.w_view / HEIGHT
	* base->tools.y;
	base->ray.dir.y = upleft.y + base->cam.right.y * base->cam.h_view
	/ WIDTH * base->tools.x - base->cam.up.y * base->cam.w_view / HEIGHT
	* base->tools.y;
	base->ray.dir.z = upleft.z + base->cam.right.z * base->cam.h_view
	/ WIDTH * base->tools.x - base->cam.up.z * base->cam.w_view / HEIGHT
	* base->tools.y;
	base->ray.dir = normalize(base->ray.dir);
}

void		find_light_cam(t_i *i, t_prim *prim)
{
	while (++i->i < i->nb)
	{
		if (prim[i->i].type == LIGHT)
			i->lt = i->i;
		if (prim[i->i].type == CAMERA)
			i->cm = i->i;
	}
}
