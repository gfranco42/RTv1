/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:21:36 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plane_light_inter(t_plane plane, t_light light)
{
	t_vector	o_center;
	int			t;

	o_center.x = plane.point.x - light.src.x;
	o_center.y = plane.point.y - light.src.y;
	o_center.z = plane.point.z - light.src.z;
	t = -dot(o_center, plane.normal) / dot(nrmz(light.ray),
	nrmz(plane.normal));
	if (t >= 0 && t <= 1)
		return (1);
	return (0);
}

int		plane_intersect(t_plane plane, t_ray ray, double t)
{
	t_vector	o_center;
	double		xv;
	double		dv;

	o_center = vec_sub(ray.origin, plane.point);
	o_center = vec_mult_d(o_center, -1);
	xv = dot(o_center, plane.normal);
	if ((dv = dot(ray.dir, plane.normal)) <= 0)
		return (t);
	t = xv / dv;
	if (t > 0)
		return (t);
	return (20000);
}

void	draw_plane(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	t_vector	inter_p;
	t_l_eff		l_e;

	inter_p = vec_add(base.ray.origin, vec_mult_d(base.ray.dir,
	base.tools.t));
	l_e.a = ambient_l(nrmz(base.ray.dir),
	prim[base.tools.i].plane.normal, 0.5);
	l_e.effect = multi_l_p(prim, base, prim[base.tools.i].plane.color, i);
	i.j = 0;
	i.lt = 0;
	i.i = base.tools.i;
	print_pixel(mlx, base.tools, l_e.effect);
}
