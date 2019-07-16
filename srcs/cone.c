/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:43 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/16 14:21:25 by gfranco          ###   ########.fr       */
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
		return (t);
	else
	{
		disc = sqrt(disc);
		d[1] = (-r[1] + disc) / (2 * r[0]);
		d[0] = (-r[1] - disc) / (2 * r[0]);
		t = (d[0] < 0) ? d[1] : d[0];
		if (t > 0)
			return (t);
	}
	return (20000);
}

t_vector	getnm_co(t_vector inter_p, t_cone cone, t_ray ray, double t)
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
	normal = nrmz(vec_minus);
	if (dot(ray.dir, normal) > 0.0001)
		normal = vec_mult_d(normal, -1);
	return (normal);
}

void		draw_cone(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	t_vector	inter_p;
	t_l_eff		l_e;

	inter_p = vec_add(base.ray.origin, vec_mult_d(base.ray.dir, base.tools.t));
	l_e.a = ambient_l(nrmz(base.ray.dir), getnm_co(inter_p,
	prim[base.tools.i].cone, base.ray, base.tools.t),
	-0.5);
	l_e.effect = multi_l_co(prim, base, prim[base.tools.i].cone.color, i);
	i.j = 0;
	i.lt = 0;
	i.i = base.tools.i;
	print_pixel(mlx, base.tools, l_e.effect);
}
