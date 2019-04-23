/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:26:54 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/22 16:24:56 by gfranco          ###   ########.fr       */
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

void	draw_plane(t_ray ray, t_plane plane, t_mlx mlx, t_tools tools)
{
	(void)ray;
	t_vector	inter_p;
	t_vector	light_ray;
	t_sphere	light_src;
	double		dt;

	light_src.center.x = WIDTH / 2;// creation d'une lumiere
	light_src.center.y = 0;
	light_src.center.z = 0;
	light_src.radius = 1;

	inter_p.x = ray.origin.x + ray.direction.x * tools.p;// intersection point
	inter_p.y = ray.origin.y + ray.direction.y * tools.p;
	inter_p.z = ray.origin.z + ray.direction.z * tools.p;

	light_ray.x = inter_p.x - light_src.center.x;	// area of the light spot
	light_ray.y = inter_p.y - light_src.center.y;	// area of the light spot
	light_ray.z = inter_p.z - light_src.center.z;	// area of the light spot

	double	ambient = 0.652;

	double	diffuse = dot(normalize(light_ray), normalize(plane.normal));// calcul dot
	diffuse = diffuse < 0 ? 0 : diffuse;

	dt = ambient + diffuse;

	mlx.str[(tools.y * WIDTH + tools.x) * 4] = 0xFF * dt/* / tools.p*/;// Color the pixel
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 1] = 0x00 * dt/* / tools.p*/;
	mlx.str[(tools.y * WIDTH + tools.x) * 4 + 2] = 0xFF * dt/* / tools.p*/;
}
