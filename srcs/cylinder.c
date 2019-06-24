/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:43:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/24 21:03:45 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			cyl_light_inter(t_cylinder cyl, t_light light, t_vector inter_p)
{
	t_vector	o_center;
	t_vector	lr;
	double		r[3];
	double		t[3];
	double		disc;

	o_center = vec_sub(inter_p, cyl.center);
	lr = vec_sub(light.src, inter_p);
	r[0] = dot(lr, lr) - dot(lr, cyl.dir) * dot(lr, cyl.dir);
	r[1] = 2 * (dot(lr, o_center) - dot(lr, cyl.dir)
	* dot(o_center, cyl.dir));
	r[2] = dot(o_center, o_center) - dot(o_center, cyl.dir)
	* dot(o_center, cyl.dir) - cyl.radius * cyl.radius;
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

int			cylinder_intersect(t_cylinder cyl, t_ray ray, double t)
{
	t_vector	o_center;
	double		r[3];
	double		d[2];
	double		disc;

	o_center = vec_sub(ray.origin, cyl.center);
	r[0] = dot(ray.dir, ray.dir) - dot(ray.dir, cyl.dir)
	* dot(ray.dir, cyl.dir);
	r[1] = 2 * (dot(ray.dir, o_center) - dot(ray.dir, cyl.dir)
	* dot(o_center, cyl.dir));
	r[2] = dot(o_center, o_center) - dot(o_center, cyl.dir)
	* dot(o_center, cyl.dir) - cyl.radius * cyl.radius;
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

t_vector	getnm_cyl(t_cylinder cyl, t_vector inter_p, t_ray ray, double t)
{
	t_vector	normal;
	t_vector	o_center;
	double		m;

	o_center.x = ray.origin.x - cyl.center.x;
	o_center.y = ray.origin.y - cyl.center.y;
	o_center.z = ray.origin.z - cyl.center.z;
	m = dot(ray.dir, cyl.dir) * t + dot(o_center, cyl.dir);
	normal.x = inter_p.x - cyl.center.x - cyl.dir.x * m;
	normal.y = inter_p.y - cyl.center.y - cyl.dir.y * m;
	normal.z = inter_p.z - cyl.center.z - cyl.dir.z * m;
	return (normal);
}

void		draw_cyl(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	t_vector	tab[4];
	t_l_eff		l_e;
	t_cylinder	cylinder;

	i.i = find_light(i, prim);
	cylinder = init_cylinder(prim[base.tools.i].cyl);
	inter_p = vec_add(base.ray.origin, vec_mult_d(base.ray.dir,
	base.tools.t));
	tab[1] = normalize(getnm_cyl(prim[base.tools.i].cyl, tab[0], base.ray,
	base.tools.t));
	eye = normalize(base.ray.dir);
	half = normalize(vec_add(vec_mult_d(prim[i.i].light.ray, -1), eye));
	prim[i.i].light.ray = normalize(vec_sub(prim[i.i].light.src, inter_p));
	l_e.ambient = ambient_l(eye, normal, -0.5);
	l_e.diffuse = diffuse_l_alt(normal, prim[i.i].light.ray,
	prim[base.tools.i].cyl.color);
	l_e.specular = specular_l(normal, half, prim[i.i].light.color, -1.0);
	if (shadow(prim, i, prim[i.i].light, inter_p) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}
	l_e.effect = light_effect(l_e.diffuse, l_e.specular, l_e.ambient,
	prim[base.tools.i].cyl.color);
	print_pixel(mlx, base.tools, l_e.effect);
}
