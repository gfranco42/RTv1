/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_prim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:50:07 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/17 17:12:28 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		intersect_prim(t_prim *prim, int i, t_base base, double t)
{
	if (prim[i].type == SPHERE)
		t = sphere_intersect(prim[i].sphere, base.ray, t);
	else if (prim[i].type == PLANE)
		t = plane_intersect(prim[i].plane, base.ray, t);
	else if (prim[i].type == CONE)
		t = cone_intersect(prim[i].cone, base.ray, t);
	else if (prim[i].type == CYLINDER)
		t = cylinder_intersect(prim[i].cyl, base.ray, t);
	return (t);
}

void	draw_prim(t_prim *prim, t_base base, t_mlx mlx, int i)
{
	if (prim[i].type == SPHERE)
		draw_sphere(base, prim[i].sphere, mlx, base.tools);
	if (prim[i].type == PLANE)
		draw_plane(base, prim[i].plane, mlx, base.tools);
	if (prim[i].type == CONE)
		draw_cone(base, prim[i].cone, mlx, base.tools);
	if (prim[i].type == CYLINDER)
		draw_cyl(base, prim[i].cyl, mlx, base.tools);
}
/*
	Pour chaque objet du tableau, check intersection garder la distance
	la plus courte et l'objet associé.

	Si intersection
		draw le pixel de l'objet en question

*/
