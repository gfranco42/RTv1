/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_prim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:50:07 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/18 18:32:02 by gfranco          ###   ########.fr       */
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

void		draw_prim(t_prim *prim, t_base base, t_mlx mlx, int i)
{
	printf("tools: %d\n", base.tools.i);
	printf("i: %d\n", i);
	if (prim[i].type == SPHERE)
		draw_sphere(base, prim[i].sphere, mlx, base.tools);
	if (prim[i].type == PLANE)
	{
		draw_plane(base, prim, mlx, base.tools);
	}
	if (prim[i].type == CONE)
		draw_cone(base, prim[i].cone, mlx, base.tools);
	if (prim[i].type == CYLINDER)
		draw_cyl(base, prim[i].cyl, mlx, base.tools);
}

void		main_algo(t_base base, t_prim *prim, t_mlx mlx, t_i i)
{
	while (++base.tools.y < HEIGHT)
	{
		base.tools.x = -1;
		while (++base.tools.x < WIDTH)
		{
			base.tools.t = 20000;
			i.tmp = 20000;
			calc_dir(base.upleft, &base);
			while (++i.i < i.nb)
			{
				if (prim[i.i].type == CAMERA && prim[i.i].type == LIGHT)
					continue ;
				i.tmp = intersect_prim(prim, i.i, base, base.tools.t);
				if (i.tmp < base.tools.t)
				{
					base.tools.t = i.tmp;
					base.tools.i = i.i;
				}
			}
			i.i = -1;
			if (base.tools.t < 20000)
				draw_prim(prim, base, mlx, base.tools.i);
		}
	}
	free(prim);
}
