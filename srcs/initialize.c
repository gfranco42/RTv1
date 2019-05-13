/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/13 11:54:06 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

// ---------------  initialisation des variables -----------------------------

t_object		initialize_var(t_base *base)
{
	t_object	object;
//	************** FIRST SPHERE *******************
	object.sphere.center.x = WIDTH * 0.3;// creation d'un objet 'sphere'
	object.sphere.center.y = HEIGHT * 0.3;
	object.sphere.center.z = 1200;

	object.sphere.radius = 100;

	object.sphere.color.r = 0;// 			COULEUR
	object.sphere.color.g = 0xFF;
	object.sphere.color.b = 0;

//	************** SECOND SPHERE *******************
	object.sphere2.center.x = WIDTH * 0.8;// creation d'un objet 'sphere'
	object.sphere2.center.y = HEIGHT * 0.7;
	object.sphere2.center.z = 100;

	object.sphere2.radius = 100;

	object.sphere2.color.r = 0;// 			COULEUR
	object.sphere2.color.g = 0x50;
	object.sphere2.color.b = 0xFF;

//	************** PLANE *******************
	object.plane.point.x = WIDTH / 2;//		POINT SUR LA PLAN
	object.plane.point.y = HEIGHT * 0.9;
	object.plane.point.z = 0;

	object.plane.normal.x = 0;//			NORMALE DU PLAN
	object.plane.normal.y = HEIGHT * 0.20;
	object.plane.normal.z = 100;
	object.plane.normal = normalize(object.plane.normal);

	object.plane.color.r = 0;// 			COULEUR
	object.plane.color.g = 0xFF;
	object.plane.color.b = 0xFB;

//	************** CONE *******************
	object.cone.tip.x = WIDTH * 0.1;//			POSITION POINTE
	object.cone.tip.y = 200;
	object.cone.tip.z = 500;

	object.cone.b_center.x = WIDTH * 0.1;//		CENTRE BASE
	object.cone.b_center.y = HEIGHT - 200;
	object.cone.b_center.z = 1000;

	object.cone.b_radius = 0.14;

	object.cone.color.r = 0xFF;// 			COULEUR
	object.cone.color.g = 0;
	object.cone.color.b = 0x10;

//	************** cyl *******************
	object.cyl.center.x = 1000;//		CENTER BASE
	object.cyl.center.y = 0;
	object.cyl.center.z = 1000;

	object.cyl.dir.x = 1;//			DIRECTION
	object.cyl.dir.y = 1;
	object.cyl.dir.z = 10;
	object.cyl.dir = normalize(object.cyl.dir);

	object.cyl.radius = 50;//			RADIUS BASE

	object.cyl.color.r = 0x100;//			COULEUR
	object.cyl.color.g = 0x100;
	object.cyl.color.b = 0;

//	************** LIGHT *******************
	base->light.src.x = WIDTH / 2;//			POSITION SOURCE
	base->light.src.y = 0;
	base->light.src.z = -200;

	base->light.color.r = 0xFF;// 			COULEUR
	base->light.color.g = 0xFF;
	base->light.color.b = 0xFF;

//	************** RAY *******************
	base->ray.origin.x = 600;
	base->ray.origin.y = 600;
	base->ray.origin.z = -500;
	base->ray.dir.x = 0;//la direction se place au tools 0/0 et look straight
	base->ray.dir.y = 0;
	base->ray.dir.z = 0;
	return (object);
}
