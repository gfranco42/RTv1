/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/24 15:34:51 by gfranco          ###   ########.fr       */
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
	//o_center = vec_sub(plane.point, light.src);
	t = -dot(o_center, plane.normal) / dot(normalize(light.ray),
	normalize(plane.normal));
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

void 	draw_plane(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	t_vector	inter_p;
//	t_vector 	half;
//	t_vector	eye;
	t_l_eff		l_e;
	t_plane		plane;

	inter_p = vec_add(base.ray.origin, vec_mult_d(base.ray.dir,
	base.tools.t));
	l_e.ambient = ambient_l(normalize(base.ray.dir),
	prim[base.tools.i].plane.normal, 0.5);
	//l_e.ambient = ambient_l(eye, plane.normal, 0.5);
	//eye = normalize(base.ray.dir);
	//half = normalize(vec_add(vec_mult_d(prim[i.i].light.ray, -1), eye));
	//prim[i.i].light.ray = normalize(vec_sub(inter_p, prim[i.i].light.src));
	//l_e.diffuse = diffuse_l_alt(plane.normal, prim[i.i].light.ray, plane.color);
	/*if (shadow(prim, i, prim[i.i].light, inter_p) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}
	l_e.effect = light_effect(l_e.diffuse, rgb_value(l_e.specular, 0, 0, 0),
	l_e.ambient, plane.color);*/
	plane = init_plane(prim[base.tools.i].plane);
	l_e.effect = multi_l_p(prim, base, prim[base.tools.i].plane.color, i);
	i.j = 0;
	i.lt = 0;
	i.i = base.tools.i;
	while (++i.j < i.nb)
	{
		if (prim[i.j].type == LIGHT && shadow(prim, i, prim[i.j].light,
		inter_p) == 0)
			i.lt++;
	}
	if (i.lt == 0)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
		l_e.effect = light_effect(l_e.diffuse, l_e.specular, l_e.ambient,
		prim[base.tools.i].plane.color);
	}
	print_pixel(mlx, base.tools, l_e.effect);
}
