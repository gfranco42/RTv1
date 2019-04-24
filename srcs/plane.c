/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/24 14:16:40 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plane_intersect(t_plane plane, t_ray ray, double t)
{
// ---------------  declaration de variables   -------------------------------
	t_vector	origin_center;

// ---------------  initialisation des variables -----------------------------
	origin_center.x = ray.origin.x - plane.point.x;
	origin_center.y = ray.origin.y - plane.point.y;
	origin_center.z = ray.origin.z - plane.point.z;

// ---------------  debut ----------------------------------------------------
	t = -dot(origin_center, plane.normal) / dot(ray.direction, plane.normal);
	return (t);
}

void	draw_plane(t_base base, t_plane plane, t_mlx mlx, t_tools tools)
{
	t_vector	inter_p;

	inter_p.x = base.ray.origin.x + base.ray.direction.x * tools.p;// intersection point
	inter_p.y = base.ray.origin.y + base.ray.direction.y * tools.p;
	inter_p.z = base.ray.origin.z + base.ray.direction.z * tools.p;

	base.light.ray.x = inter_p.x - base.light.src.x;	// area of the light spot
	base.light.ray.y = inter_p.y - base.light.src.y;	// area of the light spot
	base.light.ray.z = inter_p.z - base.light.src.z;	// area of the light spot

	double	ambient = 0.2;

	//*********** diffuse ***********
	t_vector lr = normalize(base.light.ray);
	t_vector nm = normalize(plane.normal);
	double	diffuse = dot(lr, nm);// calcul dot
	diffuse = diffuse < ambient ? ambient : diffuse;
	diffuse = diffuse / (diffuse + 1);
	t_color	plane_color;
	plane_color.r = plane.color.r * diffuse * 2;
	plane_color.g = plane.color.g * diffuse * 2;
	plane_color.b = plane.color.b * diffuse * 2;

	mlx.str[(tools.y * WIDTH + tools.x) * 4] = plane_color.b/* / tools.p*/;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = plane_color.g/* / tools.p*/;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = plane_color.r/* / tools.p*/;
}
