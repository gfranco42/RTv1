/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/06 11:35:25 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plane_light_inter(t_plane plane, t_light light, double t)
{
	t_vector origin_center;

	origin_center.x = plane.point.x - light.src.x;
	origin_center.y = plane.point.y - light.src.y;
	origin_center.z = plane.point.z - light.src.z;

	t = -dot(origin_center, plane.normal) / dot(normalize(light.ray), normalize(plane.normal));
	return (t);
}

int		plane_intersect(t_plane plane, t_ray ray, double t)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	origin_center;
	double	d1;
	double	d2;

// ---------------  initialisation des variables -----------------------------
	origin_center.x = ray.origin.x - plane.point.x;
	origin_center.y = ray.origin.y - plane.point.y;
	origin_center.z = ray.origin.z - plane.point.z;

// ---------------  debut ----------------------------------------------------
	if ((d1 = dot(ray.dir, plane.normal)) == 0)
		return (t);
	d2 = -dot(origin_center, plane.normal);
	t = d2 / d1;
	return (t);
}

void	draw_plane(t_base base, t_object object, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;

	//************* calcul point intersection ***************
	inter_p.x = base.ray.origin.x + base.ray.dir.x * tools.p;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.dir.y * tools.p;
	inter_p.z = base.ray.origin.z + base.ray.dir.z * tools.p;

	//************* calcul ray light ***************
	base.light.ray.x = inter_p.x - base.light.src.x;	// area of the light spot
	base.light.ray.y = inter_p.y - base.light.src.y;
	base.light.ray.z = inter_p.z - base.light.src.z;

	//************* normalisation ***************
	t_vector nm = normalize(object.plane.normal);
	t_vector lr = normalize(base.light.ray);
//	t_vector eye = normalize(base.ray.dir);

	//double	ambient = -dot(eye, nm) * 0.5;

	//*********** diffuse ***********
	double	diffuse = dot(lr, nm) * 2.5;// calcul dot
	diffuse = diffuse < 0 ? 0 : diffuse;

	t_color	plane_color;
	plane_color.r = object.plane.color.r + diffuse;
	plane_color.g = object.plane.color.g + diffuse;
	plane_color.b = object.plane.color.b + diffuse;

	if (sphere_light_inter(object.sphere, base.light, inter_p) == 1
		|| sphere_light_inter(object.sphere2, base.light, inter_p) == 1)
	{
		plane_color.r = 0;
		plane_color.g = 0;
		plane_color.b = 0;
	}

	mlx.str[(tools.y * WIDTH + tools.x) * 4] = plane_color.b;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = plane_color.g;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = plane_color.r;
}
