/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_prim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:50:07 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/12 12:40:18 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		intersect_prim(t_prim *prim, int i, t_base base)
{
	double		t;

	if (prim[i].type == SPHERE)
		t = sphere_intersect(prim[i].sphere, base.ray, 20000);
	else if (prim[i].type == PLANE)
		t = plane_intersect(prim[i].plane, base.ray, 20000);
	else if (prim[i].type == CONE)
		t = cone_intersect(prim[i].cone, base.ray, 20000);
	else if (prim[i].type == CYLINDER)
		t = cylinder_intersect(prim[i].cyl, base.ray, 20000);
	return (t);
}

void	draw_prim(t_prim *prim, t_base base, t_mlx mlx, int i)
{
	if (prim[i].type == 0)
		draw_sphere(base, prim[i].sphere, mlx, base.t)


}