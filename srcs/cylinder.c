/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:43:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/17 17:11:41 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		cyl_light_inter(t_cylinder cyl, t_light light, t_vector inter_p)
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

int		cylinder_intersect(t_cylinder cyl, t_ray ray, double t)
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
	{
	//	printf("cyl disc: %lf\n", disc);

		return (t);
	}
	else
	{
		disc = sqrt(disc);
		d[1] = (-r[1] + disc) / (2 * r[0]);
		d[0] = (-r[1] - disc) / (2 * r[0]);
		t = (d[0] < 0) ? d[1] : d[0];
	//	printf("cyl t: %lf\n", t);
		return (t);
	}
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

void	draw_cyl(t_base base, t_cylinder cyl, t_mlx mlx, t_tools tools)
{
/*	t_vector	inter_p;
	t_vector	normal;
	t_vector	half;
	t_vector	eye;
	t_l_eff		l_e;

	inter_p = vec_add(base.ray.origin, vec_mult_double(base.ray.dir, tools.t));
	base.light.ray = normalize(vec_sub(base.light.src, inter_p));
	normal = normalize(getnm_cyl(cyl, inter_p, base.ray, tools.t));
	eye = normalize(base.ray.dir);
	half = normalize(vec_add(vec_mult_double(base.light.ray, -1), eye));

	l_e.ambient = ambient_l(eye, normal, -0.5);
	l_e.diffuse = diffuse_l_alt(normal, base.light.ray, cyl.color);
	l_e.specular = specular_l(normal, half, base.light.color, -1.0);

	//if ((t == tools.s2 && sphere_light_inter(object.sphere, base.light, inter_p) == 1)
	//	|| (t == tools.s1 && sphere_light_inter(object.sphere2, base.light, inter_p) == 1)
	//	|| cone_light_inter(object.cone, base.light, inter_p) == 1
	//	|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	//{
	//	l_e.specular = rgb_value(l_e.specular, 0, 0, 0);
//		l_e.diffuse = rgb_value(l_e.diffuse, 0, 0, 0);
//	}
	l_e.effect = light_effect(l_e.diffuse, l_e.specular, l_e.ambient, cyl.color);
	print_pixel(mlx, tools, l_e.effect);*/

		t_vector	inter_p;
	t_vector	normal;
	double		ambient;

	inter_p.x = base.ray.origin.x + base.ray.dir.x * tools.t;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.dir.y * tools.t;
	inter_p.z = base.ray.origin.z + base.ray.dir.z * tools.t;
/*	printf("inter_p: %lf || %lf || %lf\n", inter_p.x, inter_p.y, inter_p.z);
	printf("ray origin: %lf || %lf || %lf\n", base.ray.origin.x, base.ray.origin.y, base.ray.origin.z);
	printf("ray dir: %lf || %lf || %lf\n", base.ray.dir.x, base.ray.dir.y, base.ray.dir.z);
	printf("t: %lf\n", tools.t);*/

	base.light.ray.x = base.light.src.x - inter_p.x;// area of the light spot
	base.light.ray.y = base.light.src.y - inter_p.y;
	base.light.ray.z = base.light.src.z - inter_p.z;

	normal = getnm_cyl(cyl, inter_p, base.ray, tools.t);// calcul normal
	t_vector nm = normalize(normal);
	//printf("nm: %lf || %lf || %lf\n", nm.x, nm.y, nm.z);
	t_vector lr = normalize(base.light.ray);
//	printf("lr: %lf || %lf || %lf\n", lr.x, lr.y, lr.z);
	t_vector eye = normalize(base.ray.dir);
	t_vector half;
	half.x = -lr.x + eye.x;
	half.y = -lr.y + eye.y;
	half.z = -lr.z + eye.z;
	half = normalize(half);

	ambient = -dot(eye, nm) * 0.5;
//	printf("ambient: %lf\n", ambient);

	double	di = dot(nm, lr) * 2.5;
	di = di < 0 ? 0 : di;
	di *= di;

	t_color	diff_color;
	diff_color.r = cyl.color.r * di;
	diff_color.g = cyl.color.g * di;
	diff_color.b = cyl.color.b * di;

	double	p = 80;//	shininess
	double dot_p = -dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = 3 * power(dot_p, p);

	t_color	spec_color;
	spec_color.r = base.light.color.r * si;
	spec_color.g = base.light.color.g * si;
	spec_color.b = base.light.color.b * si;

	//if (sphere_light_inter(object.sphere, base.light, inter_p) == 1
//		|| sphere_light_inter(object.sphere2, base.light, inter_p) == 1
//		|| cone_light_inter(object.cone, base.light, inter_p) == 1)
	//{
	//	spec_color.r = 0;
	//	spec_color.g = 0;
	//	spec_color.b = 0;
	//	diff_color.r = 0;
	//	diff_color.g = 0;
	//	diff_color.b = 0;
//	}

	t_color effects;
	effects.r = diff_color.r + spec_color.r + ambient * cyl.color.r;
	effects.g = diff_color.g + spec_color.g + ambient * cyl.color.g;
	effects.b = diff_color.b + spec_color.b + ambient * cyl.color.b;
	effects.r = (effects.r / 255.0) / ((effects.r / 255.0) + 1) * 255.0;
	effects.g = (effects.g / 255.0) / ((effects.g / 255.0) + 1) * 255.0;
	effects.b = (effects.b / 255.0) / ((effects.b / 255.0) + 1) * 255.0;

	mlx.str[(tools.y * WIDTH + tools.x) * 4] = effects.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = effects.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = effects.r;
}
