/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:33:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/24 14:31:17 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//***************** CHECK INTERSECTION ***************************************
int		sphere_intersect(t_sphere sphere, t_ray ray, double t)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	origin_center;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;

// ---------------  initialisation des variables -----------------------------
	origin_center.x = ray.origin.x - sphere.center.x;
	origin_center.y = ray.origin.y - sphere.center.y;
	origin_center.z = ray.origin.z - sphere.center.z;

	b = dot(origin_center, normalize(ray.direction));
	c = dot(origin_center, origin_center) - sphere.radius * sphere.radius;
	disc = b * b - 4 * c;

// ---------------  debut ----------------------------------------------------
	if (disc < 0)
		return (t);
	else
	{
		disc = sqrt(disc);
		t0 = -b - disc;
		t1 = -b + disc;
		t = (t0 < 0) ? t1 : t0;
		return (t);
	}
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

void	draw_sphere(t_base base, t_sphere sphere, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	normal;
	double		t;
	double		ambient;

	t = tools.s1 < tools.s2 ? tools.s1 : tools.s2;

	inter_p.x = base.ray.origin.x + base.ray.direction.x * t;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.direction.y * t;
	inter_p.z = base.ray.origin.z + base.ray.direction.z * t;

	base.light.ray.x = inter_p.x - base.light.src.x;// area of the light spot
	base.light.ray.y = inter_p.y - base.light.src.y;
	base.light.ray.z = inter_p.z - base.light.src.z;

	normal = getnormal_sphere(sphere, inter_p);// calcul normal
	ambient = -dot(base.ray.direction, normal) * 0.2;

	//********* normals ************
	t_vector nm = normalize(normal);
	t_vector lr = normalize(base.light.ray);
	t_vector eye = normalize(base.ray.direction);
	t_vector half;
	half.x = lr.x + eye.x;
	half.y = lr.y + eye.y;
	half.z = lr.z + eye.z;
	half = normalize(half);

	//********* diffuse ************
	double	di = dot(nm, lr);
	di = di < ambient ? ambient : di;
	di = di / (di + 1);
	t_color	diff_color;
	diff_color.r = sphere.color.r * di;
	diff_color.g = sphere.color.g * di;
	diff_color.b = sphere.color.b * di;

	//********* specular ************
	double	p = 200;//	shininess
	double dot_p = dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = power(dot_p, p);
	si = si < 0 ? 0 : si;
	si = si / (si + 1);
	t_color	spec_color;
	spec_color.r = sphere.color.r * si;
	spec_color.g = sphere.color.g * si;
	spec_color.b = sphere.color.b * si;

	//********* final ************
	t_color	final_color;
	final_color.r = diff_color.r + spec_color.r;
	final_color.g = diff_color.g + spec_color.g;
	final_color.b = diff_color.b + spec_color.b;

	//********* color ************
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = final_color.b/*amb_color.b*/;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = final_color.g/*amb_color.g*/;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = final_color.r/*amb_color.r*/;
}
