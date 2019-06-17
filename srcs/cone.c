/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:43 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/17 16:34:34 by gfranco          ###   ########.fr       */
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
	//	printf("cone disc: %lf\n", disc);
		return (t);
	}
	else
	{
		disc = sqrt(disc);
		d[1] = (-r[1] + disc) / (2 * r[0]);
		d[0] = (-r[1] - disc) / (2 * r[0]);
		t = (d[0] < 0) ? d[1] : d[0];
	//	printf("cone t: %lf\n", t);
		return (t);
	}
}

t_vector	getnormal_cone(t_vector	inter_p, t_cone cone, t_ray ray, double t)
{
	t_vector	normal;
	t_vector	vec_minus;
	t_vector	o_center;
	double		m;

	o_center = vec_sub(ray.origin, cone.tip);
	m = dot(ray.dir, cone.dir) * t + dot(o_center, cone.dir);
	normal.x = cone.dir.x * m * (1 + cone.angle * cone.angle);
	normal.y = cone.dir.y * m * (1 + cone.angle * cone.angle);
	normal.z = cone.dir.z * m * (1 + cone.angle * cone.angle);
	vec_minus.x = inter_p.x - cone.tip.x - normal.x;
	vec_minus.y = inter_p.y - cone.tip.y - normal.y;
	vec_minus.z = inter_p.z - cone.tip.z - normal.z;
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
	l_e.ambient = ambient_l(eye, normal, -0.5);
	l_e.diffuse = diffuse_l_alt(normal, base.light.ray, cone.color);
	l_e.specular = specular_l(normal, half, base.light.color, -1.0);
	/*if ((t == tools.s2 && sphere_light_inter(object.sphere, base.light, inter_p) == 1)
		|| (t == tools.s1 && sphere_light_inter(object.sphere2, base.light, inter_p) == 1)
		|| cone_light_inter(object.cone, base.light, inter_p) == 1
		|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}*/
	l_e.effect = light_effect(l_e.diffuse, l_e.specular, l_e.ambient, cone.color);
	print_pixel(mlx, tools, l_e.effect);
}
