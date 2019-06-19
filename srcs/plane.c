/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/19 12:49:16 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plane_light_inter(t_plane plane, t_light light)
{
	t_vector	o_center;
	int			t;

	o_center = vec_sub(plane.point, light.src);
	t = -dot(o_center, plane.normal) / dot(normalize(light.ray),
	normalize(plane.normal));
	return (t);
}

int		plane_intersect(t_plane plane, t_ray ray, double t)
{
	t_vector	o_center;
	double		xv;
	double		dv;

	o_center = vec_sub(ray.origin, plane.point);
	o_center = vec_mult_double(o_center, -1);
	xv = dot(o_center, plane.normal);
	if ((dv = dot(ray.dir, plane.normal)) <= 0)
		return (t);
	t = xv / dv;
	if (t > 0)
		return (t);
	return (20000);
}

void	draw_plane(t_base base, t_prim *prim, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector 	half;
	t_vector	eye;
	t_l_eff		l_e;
	t_plane		plane;

	plane = init_plane(prim[tools.i].plane);
	inter_p = vec_add(base.ray.origin, vec_mult_double(base.ray.dir, tools.t));
	eye = normalize(base.ray.dir);
	half = normalize(vec_add(vec_mult_double(base.light.ray, -1), eye));
	base.light.ray = normalize(vec_sub(inter_p, base.light.src));
	l_e.ambient = ambient_l(eye, plane.normal, 0.5);
	l_e.diffuse = diffuse_l_alt(plane.normal, base.light.ray, plane.color);
	/*if (shadow(prim, base.tools.i, base, inter_p) == 0)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}*/
	l_e.effect = light_effect(l_e.diffuse, rgb_value(l_e.specular, 0, 0, 0),
	l_e.ambient, plane.color);
	print_pixel(mlx, tools, l_e.effect);
}
