/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:43 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/06 19:02:45 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			cone_light_inter()
{

}

int			cone_intersect(t_cone cone, t_ray ray, double t)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	o_tip;
	t_vector	height;
	t_vector	h;
	double		n_height;
	double		m;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;


// ---------------  initialisation des variables -----------------------------
	o_tip.x = ray.origin.x - cone.tip.x;//		distance pointe - origine
	o_tip.y = ray.origin.y - cone.tip.y;
	o_tip.z = ray.origin.z - cone.tip.z;

	height.x = cone.b_center.x - cone.tip.x;//	hauteur cone
	height.y = cone.b_center.y - cone.tip.y;
	height.z = cone.b_center.z - cone.tip.z;
	n_height = norm(height);

	h.x = height.x / n_height;//		axis???
	h.y = height.y / n_height;
	h.z = height.z / n_height;

	m = cone.b_radius * cone.b_radius / n_height * n_height;//	???

	a = dot(ray.dir, ray.dir) - m * dot(ray.dir, h)
		* dot(ray.dir, h) - dot(ray.dir, h) * dot(ray.dir, h);
	b = 2 * (dot(ray.dir, o_tip) - m * dot(ray.dir, h)
		* dot(o_tip, h) - dot(ray.dir, h) * dot(o_tip, h));
	c = dot(o_tip, o_tip) - m * dot(o_tip, h) * dot(o_tip, h) - dot(o_tip, h)
		* dot(o_tip, h);
	disc = b * b - 4.0 * a * c;

// ---------------  debut ----------------------------------------------------
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

t_vector	getnormal_cone(t_vector	inter_p)
{
	t_vector	normal;

	inter_p.y *= -1;

	normal = normalize(inter_p);
	return (normal);
}

void		draw_cone(t_base base, t_object object, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;
//	************* calcul point intersection ***************
	inter_p.x = base.ray.origin.x + base.ray.dir.x * tools.c;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.dir.y * tools.c;
	inter_p.z = base.ray.origin.z + base.ray.dir.z * tools.c;

//	************* calcul ray light ***************
	base.light.ray.x = base.light.src.x - inter_p.x;	// area of the light spot
	base.light.ray.y = base.light.src.y - inter_p.y;
	base.light.ray.z = base.light.src.z - inter_p.z;

//	************* normalisation ***************
	t_vector nm = getnormal_cone(inter_p);
	t_vector lr = normalize(base.light.ray);
	t_vector eye = normalize(base.ray.dir);
	t_vector half;
	half.x = -lr.x + eye.x;
	half.y = -lr.y + eye.y;
	half.z = -lr.z + eye.z;
	half = normalize(half);

	double	ambient = dot(eye, nm) * 0.5;

//	********* diffuse ************
	double	di = dot(nm, lr) * 2.5;
	di = di < 0 ? 0 : di;
	di *= di;

	t_color	diff_color;
	diff_color.r = object.cone.color.r * di;
	diff_color.g = object.cone.color.g * di;
	diff_color.b = object.cone.color.b * di;

//	********* specular ************
	double	p = 100;//	shininess
	double dot_p = dot(nm, half);
	dot_p = dot_p < 0 ? 0 : dot_p;
	double si = 3 * power(dot_p, p);

	t_color	spec_color;
	spec_color.r = base.light.color.r * si;
	spec_color.g = base.light.color.g * si;
	spec_color.b = base.light.color.b * si;

//	********* all effects ************
	t_color effects;
	effects.r = diff_color.r + spec_color.r + ambient * object.cone.color.r;
	effects.g = diff_color.g + spec_color.g + ambient * object.cone.color.g;
	effects.b = diff_color.b + spec_color.b + ambient * object.cone.color.b;
	effects.r = (effects.r / 255.0) / ((effects.r / 255.0) + 1) * 255.0;
	effects.g = (effects.g / 255.0) / ((effects.g / 255.0) + 1) * 255.0;
	effects.b = (effects.b / 255.0) / ((effects.b / 255.0) + 1) * 255.0;

	//********* color ************
	mlx.str[(tools.y * WIDTH + tools.x) * 4] = effects.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = effects.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = effects.r;
}
