/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:43 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/15 16:28:23 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			cone_light_inter(t_cone cone, t_light light, t_vector inter_p)
{
	t_vector	o_tip;
	t_vector	lr;
	double		r[3];
	double		t[3];
	double		disc;

	o_tip = vec_sub(inter_p, cone.tip);
	lr = vec_sub(light.src, inter_p);

	r[0] = dot(lr, lr) - (1 + cone.angle * cone.angle)
	* dot(lr, cone.dir) * dot(lr, cone.dir);
	r[1] = 2 * (dot(lr, o_tip) - (1 + cone.angle * cone.angle)
	* dot(lr, cone.dir) * dot(o_tip, cone.dir));
	r[2] = dot(o_tip, o_tip) - (1 + cone.angle * cone.angle)
	* dot(o_tip, cone.dir) * dot(o_tip, cone.dir);
	disc = r[1] * r[1] - 4.0 * r[0] * r[2];

	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	t[2] = (-r[1] + disc) / (2 * r[0]);
	t[1] = (-r[1] - disc) / (2 * r[0]);
	t[0] = (t[1] < 0) ? t[2] : t[1];
	if (t[0] >= 0 && t[0] <= 1)
		return (1);
	return (0);
}

int			cone_intersect(t_cone cone, t_ray ray, double t)
{
	t_vector	o_tip;
	double		r[3];
	double		d[2];
	double		disc;

	/*printf("ray.o: %lf | %lf | %lf\n", ray.origin.x, ray.origin.y, ray.origin.z);
	printf("ray.d: %lf | %lf | %lf\n", ray.dir.x, ray.dir.y, ray.dir.z);
	printf("cone.d: %lf | %lf | %lf\n", cone.dir.x, cone.dir.y, cone.dir.z);
	printf("cone angle: %lf\n", cone.angle);*/
	o_tip = vec_sub(ray.origin, cone.tip);
	r[0] = dot(ray.dir, ray.dir) - (1 + cone.angle * cone.angle)
	* dot(ray.dir, cone.dir) * dot(ray.dir, cone.dir);
	r[1] = 2 * (dot(ray.dir, o_tip) - (1 + cone.angle * cone.angle)
	* dot(ray.dir, cone.dir) * dot(o_tip, cone.dir));
	r[2] = dot(o_tip, o_tip) - (1 + cone.angle * cone.angle)
	* dot(o_tip, cone.dir) * dot(o_tip, cone.dir);
	disc = r[1] * r[1] - 4.0 * r[0] * r[2];
	if (disc < 0)
	{

		return (t);
	}
	else
	{
		disc = sqrt(disc);
		d[1] = (-r[1] + disc) / (2 * r[0]);
		d[0] = (-r[1] - disc) / (2 * r[0]);
		t = (d[0] < 0) ? d[1] : d[0];
		return (t);
	}
}

t_vector	getnormal_cone(t_vector	inter_p, t_cone cone, t_ray ray, double t)
{
	t_vector	normal;
	t_vector	vec_minus;
	t_vector	o_center;
	double		tmp;
	double		m;

	o_center = vec_sub(ray.origin, cone.tip);
	m = dot(ray.dir, cone.dir) * t + dot(o_center, cone.dir);
	tmp = m * (1 * cone.angle * cone.angle);
	normal = vec_mult_double(cone.dir, tmp);
	vec_minus = vec_sub(inter_p, vec_sub(cone.tip, normal));
	normal = normalize(vec_minus);
	if (dot(ray.dir, normal) > 0.0001)
		normal = vec_mult_double(normal, -1);
	return (normal);
}

void		draw_cone(t_base base, t_cone cone, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	normal;
	t_vector	half;
	t_vector	eye;
	t_l_eff		l_e;

	inter_p = vec_add(base.ray.origin, vec_mult_double(base.ray.dir, tools.t));
	base.light.ray = normalize(vec_sub(base.light.src, inter_p));
	normal = getnormal_cone(inter_p, cone, base.ray, tools.t);
	eye = normalize(base.ray.dir);
	half = normalize(vec_add(vec_mult_double(base.light.ray, -1), eye));
	l_e.ambient = ambient_l(eye, normal);
	l_e.diffuse = diffuse_l(normal, base.light.ray, cone.color);
	l_e.specular = specular_l(normal, half, base.light.color);
	/*if ((t == tools.s2 && sphere_light_inter(object.sphere, base.light, inter_p) == 1)
		|| (t == tools.s1 && sphere_light_inter(object.sphere2, base.light, inter_p) == 1)
		|| cone_light_inter(object.cone, base.light, inter_p) == 1
		|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}*/
	l_e.effect = light_effect(l_e.diffuse, l_e.specular, l_e.ambient, cone.color);
	//printf("");
	print_pixel(mlx, tools, l_e.effect);
/*
	double	ambient = -dot(eye, nm) * 0.5;

	double	di = dot(nm, lr) * 2.5;
	di = di < 0 ? 0 : di;
	di *= di;

	t_color	diff_color;
	diff_color.r = object.cone.color.r * di;
	diff_color.g = object.cone.color.g * di;
	diff_color.b = object.cone.color.b * di;

	double	p = 100;//	shininess
	double dot_p = -dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = 3 * power(dot_p, p);

	t_color	spec_color;
	spec_color.r = base.light.color.r * si;
	spec_color.g = base.light.color.g * si;
	spec_color.b = base.light.color.b * si;

	if (sphere_light_inter(object.sphere2, base.light, inter_p) == 1
		|| sphere_light_inter(object.sphere, base.light, inter_p) == 1
		|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	{
		spec_color.r = 0;
		spec_color.g = 0;
		spec_color.b = 0;
		diff_color.r = 0;
		diff_color.g = 0;
		diff_color.b = 0;
	}

	t_color effects;
	effects.r = diff_color.r + spec_color.r + ambient * object.cone.color.r;
	effects.g = diff_color.g + spec_color.g + ambient * object.cone.color.g;
	effects.b = diff_color.b + spec_color.b + ambient * object.cone.color.b;
	effects.r = (effects.r / 255.0) / ((effects.r / 255.0) + 1) * 255.0;
	effects.g = (effects.g / 255.0) / ((effects.g / 255.0) + 1) * 255.0;
	effects.b = (effects.b / 255.0) / ((effects.b / 255.0) + 1) * 255.0;

	mlx.str[(tools.y * WIDTH + tools.x) * 4] = effects.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = effects.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = effects.r;*/
}
