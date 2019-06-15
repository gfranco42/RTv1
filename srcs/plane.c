/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/14 15:33:16 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plane_light_inter(t_plane plane, t_light light, double t)
{
	t_vector o_center;

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
	return (t);
}

void	draw_plane(t_base base, t_plane plane, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	normal;
	t_vector 	half;
	t_vector	eye;
	t_l_eff		l_e;

	inter_p = vec_add(base.ray.origin, vec_mult_double(base.ray.dir, tools.t));
	base.light.ray = normalize(vec_sub(base.light.src, inter_p));
	normal = normalize(plane.normal);
	eye = normalize(base.ray.dir);
	half = normalize(vec_add(vec_mult_double(base.light.ray, -1), eye));
	l_e.ambient = ambient_l(eye, normal);
	l_e.diffuse = diffuse_l(normal, base.light.ray, plane.color);
	l_e.effect.r = l_e.diffuse.r + l_e.ambient * plane.color.r;
	l_e.effect.g = l_e.diffuse.g + l_e.ambient * plane.color.g;
	l_e.effect.b = l_e.diffuse.b + l_e.ambient * plane.color.b;
	l_e.effect.r = (l_e.effect.r / 255.0) / ((l_e.effect.r / 255.0) + 1) * 255.0;
	l_e.effect.g = (l_e.effect.g / 255.0) / ((l_e.effect.g / 255.0) + 1) * 255.0;
	l_e.effect.b = (l_e.effect.b / 255.0) / ((l_e.effect.b / 255.0) + 1) * 255.0;
	/*if (sphere_light_inter(object.sphere, base.light, inter_p) == 1
		|| sphere_light_inter(object.sphere2, base.light, inter_p) == 1
		|| cone_light_inter(object.cone, base.light, inter_p) == 1
		|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}*/
	print_pixel(mlx, tools, l_e.effect);
}
