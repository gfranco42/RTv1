/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:43:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/06 12:27:11 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		cylinder_intersect(t_cylinder cyl, t_ray ray, double t)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	o_center;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;

// ---------------  initialisation des variables -----------------------------
	o_center.x = ray.origin.x - cyl.center.x;
	o_center.y = ray.origin.y - cyl.center.y;
	o_center.z = ray.origin.z - cyl.center.z;

// ---------------  debut ----------------------------------------------------
	a = dot(ray.dir, ray.dir) - dot(ray.dir, cyl.dir) * dot(ray.dir, cyl.dir);
	b = 2 * dot(ray.dir, o_center) - dot(ray.dir, cyl.dir)
	* dot(o_center, cyl.dir);
	c = dot(o_center, o_center) - dot(o_center, cyl.dir)
	* dot(o_center, cyl.dir) - cyl.radius * cyl.radius;
	disc = b * b - 4.0 * a * c;

	if (disc < 0)
		return (t);
	else
	{
		disc = sqrt(disc);
		t1 = (-b + disc) / (2 * a);
		t0 = (-b - disc) / (2 * a);
		t = (t0 < 0) ? t1 : t0;
		return (t);
	}
}

t_vector	getnormal_cylinder(t_cylinder cyl, t_vector inter_p, t_ray ray, double t)
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

void	draw_cylinder(t_base base, t_object object, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	normal;
	double		ambient;

	//	************* calcul point intersection ***************
	inter_p.x = base.ray.origin.x + base.ray.dir.x * tools.cy;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.dir.y * tools.cy;
	inter_p.z = base.ray.origin.z + base.ray.dir.z * tools.cy;

	//	************* calcul ray light ***************
	base.light.ray.x = base.light.src.x - inter_p.x;// area of the light spot
	base.light.ray.y = base.light.src.y - inter_p.y;
	base.light.ray.z = base.light.src.z - inter_p.z;

	//********* normals ************
	normal = getnormal_cylinder(object.cyl, inter_p, base.ray, tools.cy);// calcul normal
	t_vector nm = normalize(normal);
	t_vector lr = normalize(base.light.ray);
	t_vector eye = normalize(base.ray.dir);
	t_vector half;
	half.x = -lr.x + eye.x;
	half.y = -lr.y + eye.y;
	half.z = -lr.z + eye.z;
	half = normalize(half);

	//********* ambient ************
	ambient = dot(eye, nm) * 0.5;

	//********* diffuse ************
	double	di = -dot(nm, lr) * 2.5;
	di = di < 0 ? 0 : di;
	di *= di;

	t_color	diff_color;
	diff_color.r = object.cyl.color.r * di;
	diff_color.g = object.cyl.color.g * di;
	diff_color.b = object.cyl.color.b * di;

	//********* specular ************
	double	p = 100;//	shininess
	double dot_p = dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = 3 * power(dot_p, p);

	t_color	spec_color;
	spec_color.r = base.light.color.r * si;
	spec_color.g = base.light.color.g * si;
	spec_color.b = base.light.color.b * si;

	//********* all effects ************
	t_color effects;
	effects.r = diff_color.r + spec_color.r + ambient * object.sphere.color.r;
	effects.g = diff_color.g + spec_color.g + ambient * object.sphere.color.g;
	effects.b = diff_color.b + spec_color.b + ambient * object.sphere.color.b;
	effects.r = (effects.r / 255.0) / ((effects.r / 255.0) + 1) * 255.0;
	effects.g = (effects.g / 255.0) / ((effects.g / 255.0) + 1) * 255.0;
	effects.b = (effects.b / 255.0) / ((effects.b / 255.0) + 1) * 255.0;

	//********* color ************
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = effects.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = effects.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = effects.r;
}
