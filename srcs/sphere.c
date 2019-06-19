/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:33:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/19 17:17:08 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			sphere_light_int(t_sphere sphere, t_light light, t_vector inter_p)
{
	t_vector	o_center;
	t_vector	lr;
	double		r[3];
	double		t[3];
	double		disc;

	o_center = vec_sub(inter_p, sphere.center);
	lr = vec_sub(light.src, inter_p);
	r[0] = dot(lr, lr);
	r[1] = 2 * dot(o_center, lr);
	r[2] = dot(o_center, o_center) - sphere.radius * sphere.radius;
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

int			sphere_intersect(t_sphere sphere, t_ray ray, double t)
{
	t_vector	o_center;
	double		r[3];
	double		d[2];
	double		disc;

	o_center = vec_sub(ray.origin, sphere.center);
	r[0] = dot(ray.dir, ray.dir);
	r[1] = 2 * dot(ray.dir, o_center);
	r[2] = dot(o_center, o_center) - sphere.radius * sphere.radius;
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

t_vector	getnormal_sphere(t_sphere sphere, t_vector inter_p)
{
	t_vector	normal;

	normal.x = sphere.center.x - inter_p.x;
	normal.y = sphere.center.y - inter_p.y;
	normal.z = sphere.center.z - inter_p.z;
	normal = normalize(normal);
	return (normal);
}

t_vector	get_r(t_vector normal, t_vector light)
{
	t_vector	r;

	r.x = 2 * dot(normalize(light), normalize(normal)) * (normal.x - light.x);
	r.y = 2 * dot(normalize(light), normalize(normal)) * (normal.y - light.y);
	r.z = 2 * dot(normalize(light), normalize(normal)) * (normal.z - light.z);
	return (r);
}

void		draw_sphere(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	t_vector	tab[4];
	t_l_eff		l_e;
	t_sphere	sphere;

	i.i = find_light(i, prim);
	sphere = init_sphere(prim[base.tools.i].sphere);
	tab[0] = vec_add(base.ray.origin, mult_double(base.ray.dir,
	base.tools.t));
	tab[1] = getnormal_sphere(sphere, tab[0]);
	tab[2] = normalize(base.ray.dir);
	tab[3] = normalize(vec_add(mult_double(prim[i.i].light.ray, -1), tab[2]));
	prim[i.i].light.ray = normalize(vec_sub(prim[i.i].light.src, tab[0]));
	l_e.ambient = ambient_l(tab[2], tab[1], 0.5);
	l_e.diffuse = diffuse_l(tab[1], prim[i.i].light.ray, sphere.color);
	l_e.specular = specular_l(tab[1], tab[3], prim[i.i].light.color, 1.0);
	if (shadow(prim, i, prim[i.i].light, tab[0]) == 1)
	{
		l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
	}
	l_e.effect = \
		light_effect(l_e.diffuse, l_e.specular, l_e.ambient, sphere.color);
	print_pixel(mlx, base.tools, l_e.effect);
}
