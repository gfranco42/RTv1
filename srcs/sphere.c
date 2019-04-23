/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:33:16 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/23 17:17:22 by gfranco          ###   ########.fr       */
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

void	draw_sphere(t_ray ray, t_sphere sphere, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
	t_vector	light_ray;
	t_vector	normal;
	t_sphere	light_src;
	double		t;

	t = tools.s1 < tools.s2 ? tools.s1 : tools.s2;

	light_src.center.x = WIDTH / 2;// creation d'une lumiere
	light_src.center.y = HEIGHT / 3;
	light_src.center.z = 0;
	light_src.radius = 1;

	inter_p.x = ray.origin.x + ray.direction.x * t;// intersection point
	inter_p.y = ray.origin.y + ray.direction.y * t;
	inter_p.z = ray.origin.z + ray.direction.z * t;

	light_ray.x = inter_p.x - light_src.center.x;	// area of the light spot
	light_ray.y = inter_p.y - light_src.center.y;
	light_ray.z = inter_p.z - light_src.center.z;

	normal = getnormal_sphere(sphere, inter_p);// calcul normal

	//********* normals ************
	t_vector nm = normalize(normal);
	t_vector lr = normalize(light_ray);
	t_vector eye = normalize(ray.direction);
	t_vector half;
	half.x = lr.x + eye.x;
	half.y = lr.y + eye.y;
	half.z = lr.z + eye.z;
	half = normalize(half);

	//********* diffuse ************
	double	di = dot(nm, lr);
	di = di < 0 ? 0 : di;
	//di = di > 1 ? 1 : di;
	di = di / (di + 1);
	t_color	diff_color;
	diff_color.r = 0x00 * di;
	diff_color.g = 0xFF * di;
	diff_color.b = 0x00 * di;

	//********* specular ************
	double	p = 100;//	shininess
	double dot_p = dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = power(dot_p, p);
	//si = si > 1 ? 1 : si;
	si = si / (si + 1);
	t_color	spec_color;
	spec_color.r = 0xFF * si;
	spec_color.g = 0xFF * si;
	spec_color.b = 0xFF * si;

	//********* ambient ************
	t_color	amb_color;
	double	ambient = dot(lr, nm) * 0.8;
	ambient = ambient < 0 ? 0 : ambient;
	amb_color.r = 0x00 * ambient;
	amb_color.g = 0xFF * ambient;
	amb_color.b = 0x00 * ambient;

	//********* final ************
	t_color	final_color;
	final_color.r = diff_color.r + spec_color.r;
	final_color.g = diff_color.g + spec_color.g;
	final_color.b = diff_color.b + spec_color.b;

	//********* color ************
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = final_color.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = final_color.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = final_color.r;
}
