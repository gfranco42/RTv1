/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:45:27 by gfranco           #+#    #+#             */
/*   Updated: 2019/09/04 11:23:22 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				shadow(t_prim *prim, t_i i, t_base base, t_vector inter_p)
{
	int		t;

	t = 0;
	i.tmp = -1;
	while (++i.tmp < i.nb)
	{
		if (prim[i.tmp].type == SPHERE && t == 0 && base.tools.i != i.tmp)
			t = sphere_light_int(prim[i.tmp].sphere, prim[i.j].light, inter_p);
		else if (prim[i.tmp].type == PLANE && t == 0 && base.tools.i != i.tmp)
			t = plane_light_inter(prim[i.tmp].plane, prim[i.j].light);
		else if (prim[i.tmp].type == CONE && t == 0 && base.tools.i != i.tmp)
			t = cone_light_inter(prim[i.tmp].cone, prim[i.j].light, inter_p);
		else if (prim[i.tmp].type == CYLINDER && t == 0
				&& base.tools.i!= i.tmp)
			t = cyl_light_inter(prim[i.tmp].cyl, prim[i.j].light, inter_p);
	}
	return (t);
}

t_color			first_cap(t_color color)
{
	color.r = color.r > 255 ? 255 : color.r;
	color.g = color.g > 255 ? 255 : color.g;
	color.b = color.b > 255 ? 255 : color.b;
	color.r = color.r < 0 ? 0 : color.r;
	color.g = color.g < 0 ? 0 : color.g;
	color.b = color.b < 0 ? 0 : color.b;
	return (color);
}
