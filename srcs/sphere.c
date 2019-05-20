/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:33:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/15 12:47:21 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		sphere_light_inter(t_sphere sphere, t_light light, t_vector inter_p)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	o_center;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;
	double		t;

// --------------- initialisation des variables ------------------------------
	o_center.x = inter_p.x - sphere.center.x;
	o_center.y = inter_p.y - sphere.center.y;
	o_center.z = inter_p.z - sphere.center.z;

	t_vector	lr;
	lr.x = light.src.x - inter_p.x;
	lr.y = light.src.y - inter_p.y;
	lr.z = light.src.z - inter_p.z;

	a = dot(lr, lr);
	b = 2 * dot(o_center, lr);
	c = dot(o_center, o_center) - sphere.radius * sphere.radius;
	disc = b * b - 4.0 * a * c;
// ---------------  debut ----------------------------------------------------
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	t1 = (-b + disc) / (2 * a);
	t0 = (-b - disc) / (2 * a);
	t = (t0 < 0) ? t1 : t0;
	if (t >= 0/* && t <= 1*/)
		return (1);
	return (0);
}

//***************** CHECK INTERSECTION ***************************************
int		sphere_intersect(t_sphere sphere, t_ray ray, double t)
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
	o_center.x = ray.origin.x - sphere.center.x;
	o_center.y = ray.origin.y - sphere.center.y;
	o_center.z = ray.origin.z - sphere.center.z;

// ---------------  debut ----------------------------------------------------
	a = dot(ray.dir, ray.dir);
	b = 2 * dot(ray.dir, o_center);
	c = dot(o_center, o_center) - sphere.radius * sphere.radius;
	disc = b * b - 4.0 * a * c;

	if (disc < 0)
		return (t);
	else
	{
		disc = sqrt(disc);
		t1 = (-b + disc) / (2 * a);
		t0 = (-b - disc) / (2 * a);
		t = (t0 < 0) ? t1 : t0;
		if (t > 0)
			return (t);
	}
	return (t);
}

t_vector	getnormal_sphere(t_sphere sphere, t_vector inter_p)
{
	t_vector	normal;

	normal.x = (sphere.center.x - inter_p.x);
	normal.y = (sphere.center.y - inter_p.y);
	normal.z = (sphere.center.z - inter_p.z);
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

void	draw_sphere(t_base base, t_object object, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	normal;
	t_sphere	sphere;
	double		t;
	double		ambient;

	t = tools.s1 < tools.s2 ? tools.s1 : tools.s2;
	if (t == tools.s2)
		sphere = object.sphere2;
	else
		sphere = object.sphere;

	//	************* calcul point intersection ***************
	inter_p.x = base.ray.origin.x + base.ray.dir.x * t;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.dir.y * t;
	inter_p.z = base.ray.origin.z + base.ray.dir.z * t;

	//	************* calcul ray light ***************
	base.light.ray.x = base.light.src.x - inter_p.x;// area of the light spot
	base.light.ray.y = base.light.src.y - inter_p.y;
	base.light.ray.z = base.light.src.z - inter_p.z;

	//********* normals ************
	normal = getnormal_sphere(sphere, inter_p);// calcul normal
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
	diff_color.r = sphere.color.r * di;
	diff_color.g = sphere.color.g * di;
	diff_color.b = sphere.color.b * di;

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
	effects.r = diff_color.r + spec_color.r + ambient * sphere.color.r;
	effects.g = diff_color.g + spec_color.g + ambient * sphere.color.g;
	effects.b = diff_color.b + spec_color.b + ambient * sphere.color.b;
	effects.r = (effects.r / 255.0) / ((effects.r / 255.0) + 1) * 255.0;
	effects.g = (effects.g / 255.0) / ((effects.g / 255.0) + 1) * 255.0;
	effects.b = (effects.b / 255.0) / ((effects.b / 255.0) + 1) * 255.0;

	//*********** SHADOWS ************
	if ((t == tools.s2 && sphere_light_inter(object.sphere, base.light, inter_p) == 1)
		|| (t == tools.s1 && sphere_light_inter(object.sphere2, base.light, inter_p) == 1)
		|| cone_light_inter(object.cone, base.light, inter_p) == 1
		|| cylinder_light_inter(object.cyl, base.light, inter_p) == 1)
	{
		effects.r = 0;
		effects.g = 0;
		effects.b = 0;
	}

	//********* color ************
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = effects.b/*final_color.b*/;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = effects.g/*final_color.g*/;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = effects.r/*final_color.r*/;
}
