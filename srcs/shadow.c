/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:45:27 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/19 11:49:17 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		shadow(t_prim *prim, int i, t_base base, t_vector inter_p)
{
	int		t;

	t = 0;
	if (prim[i].type == SPHERE && t == 0)
		t = sphere_light_int(prim[i].sphere, base.light, inter_p);
	if (prim[i].type == PLANE && t == 0)
		t = plane_light_inter(prim[i].plane, base.light);
	if (prim[i].type == CONE && t == 0)
		t = cone_light_inter(prim[i].cone, base.light, inter_p);
	if (prim[i].type == CYLINDER && t == 0)
		t = cyl_light_inter(prim[i].cyl, base.light, inter_p);
	return (t);
}
