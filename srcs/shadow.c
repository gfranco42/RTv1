/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:45:27 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/19 15:57:44 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		shadow(t_prim *prim, t_i i, t_light light, t_vector inter_p)
{
	int		t;

	t = 0;
	i.tmp = -1;
	while (++i.tmp < i.nb)
	{
		if (prim[i.tmp].type == SPHERE && t == 0 && i.i != i.tmp)
			t = sphere_light_int(prim[i.tmp].sphere, light, inter_p);
		else if (prim[i.tmp].type == PLANE && t == 0 && i.i != i.tmp)
			t = plane_light_inter(prim[i.tmp].plane, light);
		else if (prim[i.tmp].type == CONE && t == 0 && i.i != i.tmp)
			t = cone_light_inter(prim[i.tmp].cone, light, inter_p);
		else if (prim[i.tmp].type == CYLINDER && t == 0 && i.i != i.tmp)
			t = cyl_light_inter(prim[i.tmp].cyl, light, inter_p);
	}
	return (t);
}
