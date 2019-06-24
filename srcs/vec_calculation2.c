/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calculation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:05:24 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/24 21:04:21 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		vec_add_double(t_vector a, double b)
{
	t_vector	vec;

	vec.x = a.x + b;
	vec.y = a.y + b;
	vec.z = a.z + b;
	return (vec);
}

t_vector		vec_sub_double(t_vector a, double b)
{
	t_vector	vec;

	vec.x = a.x - b;
	vec.y = a.y - b;
	vec.z = a.z - b;
	return (vec);
}

t_vector		vec_mult_d(t_vector a, double b)
{
	t_vector	vec;

	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return (vec);
}

t_vector		vec_div_double(t_vector a, double b)
{
	t_vector	vec;

	vec.x = a.x / b;
	vec.y = a.y / b;
	vec.z = a.z / b;
	return (vec);
}
