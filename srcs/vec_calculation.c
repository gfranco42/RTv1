/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:37:02 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/11 15:20:20 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		vec_add(t_vector a, t_vector b)
{
	t_vector	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return(vec);
}

t_vector		vec_sub(t_vector a, t_vector b)
{
	t_vector	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return(vec);
}

t_vector		vec_mult(t_vector a, t_vector b)
{
	t_vector	vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	return(vec);
}

t_vector		vec_div(t_vector a, t_vector b)
{
	t_vector	vec;

	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
	return(vec);
}

t_vector	upleft_calc(t_base base)
{
	t_vector	upleft;

	upleft.x = base.cam.dist * base.cam.forward.x + base.cam.h_view / 2
	* base.cam.up.x - base.cam.w_view / 2 * base.cam.right.x;
	upleft.y = base.cam.dist * base.cam.forward.y + base.cam.h_view / 2
	* base.cam.up.y - base.cam.w_view / 2 * base.cam.right.y;
	upleft.z = base.cam.dist * base.cam.forward.z + base.cam.h_view / 2
	* base.cam.up.z - base.cam.w_view / 2 * base.cam.right.z;
	upleft = normalize(upleft);
	return (upleft);
}
