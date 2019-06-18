/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:11:24 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/18 18:20:27 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_sphere			init_sphere(t_sphere sphere)
{
	t_sphere		res;

	res.center = vec_add_double(sphere.center, 0);
	res.color.r = sphere.color.r;
	res.color.g = sphere.color.g;
	res.color.b = sphere.color.b;
	res.radius = sphere.radius;
	return (res);
}

t_plane				init_plane(t_plane plane)
{
	t_plane			res;

	res.normal = vec_add_double(plane.normal, 0);
	res.color.r = plane.color.r;
	res.color.g = plane.color.g;
	res.color.b = plane.color.b;
	res.point = vec_add_double(plane.point, 0);
	return (res);
}

t_cylinder			init_cylinder(t_cylinder cylinder)
{
	t_cylinder		res;

	res.center = vec_add_double(cylinder.center, 0);
	res.dir = vec_add_double(cylinder.dir, 0);
	res.color.r = cylinder.color.r;
	res.color.g = cylinder.color.g;
	res.color.b = cylinder.color.b;
	res.radius = cylinder.radius;
	return (res);
}

t_cone				init_cone(t_cone cone)
{
	t_cone			res;

	res.tip = vec_add_double(cone.tip, 0);
	res.dir = vec_add_double(cone.dir, 0);
	res.color.r = cone.color.r;
	res.color.g = cone.color.g;
	res.color.b = cone.color.b;
	res.angle = cone.angle;
	return (res);
}
