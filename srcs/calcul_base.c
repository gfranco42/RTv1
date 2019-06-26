/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:23 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/26 13:52:39 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

t_vector	nrmz(t_vector v)
{
	double	mg;

	mg = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x / mg;
	v.y = v.y / mg;
	v.z = v.z / mg;
	return (v);
}

double		norm(t_vector v)
{
	double	res;

	v.x = v.x * v.x;
	v.y = v.y * v.y;
	v.z = v.z * v.z;
	res = v.x + v.y + v.z;
	res = sqrt(res);
	return (res);
}

double		power(double i, int power_value)
{
	double	tmp;

	tmp = i;
	while (power_value-- > 0)
		i *= tmp;
	return (i);
}

double		dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
