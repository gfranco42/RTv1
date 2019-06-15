/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/15 13:18:36 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

// ---------------  initialisation des variables -----------------------------

t_object		initialize_var(t_base *base)
{
	t_object	object;
//	************** FIRST SPHERE *******************
	object.sphere.center.x = WIDTH * 0.3;// creation d'un objet 'sphere'
	object.sphere.center.y = HEIGHT * 0.7;
	object.sphere.center.z = 300;

	object.sphere.radius = 100;

	object.sphere.color.r = 0;// 			COULEUR
	object.sphere.color.g = 0xFF;
	object.sphere.color.b = 0;

//	************** SECOND SPHERE *******************
	object.sphere2.center.x = WIDTH * 0.25;// creation d'un objet 'sphere'
	object.sphere2.center.y = HEIGHT * 0.65;
	object.sphere2.center.z = 100;

	object.sphere2.radius = 20;

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
	object.cone.tip.x = WIDTH * 0.5;//			POSITION POINTE
	object.cone.tip.y = 200;
	object.cone.tip.z = 500;

	object.cone.dir.x = 0;
	object.cone.dir.y = 1;
	object.cone.dir.z = 0;

	object.cone.angle = 0.2;

	object.cone.color.r = 0xFF;// 			COULEUR
	object.cone.color.g = 0;
	object.cone.color.b = 0x10;

//	************** cyl *******************
	object.cyl.center.x = 1000;//		CENTER BASE
	object.cyl.center.y = 0;
	object.cyl.center.z = 1000;

	object.cyl.dir.x = 1;//			DIRECTION
	object.cyl.dir.y = 1;
	object.cyl.dir.z = 0;
	object.cyl.dir = normalize(object.cyl.dir);

	object.cyl.radius = 100;//			RADIUS BASE

	object.cyl.color.r = 0x100;//			COULEUR
	object.cyl.color.g = 0x100;
	object.cyl.color.b = 0;

//	************** LIGHT *******************
	base->light.src.x = 250;//			POSITION SOURCE
	base->light.src.y = 750;
	base->light.src.z = -100;

	base->light.color.r = 0xFF;// 			COULEUR
	base->light.color.g = 0xFF;
	base->light.color.b = 0xFF;

//	************** CAMERA *******************
	base->cam.pos.x = 600;
	base->cam.pos.y = 600;
	base->cam.pos.z = -600;

	base->cam.target.x = 600;//			POINT REGARDÉ
	base->cam.target.y = 600;
	base->cam.target.z = 600;

	base->cam.up.x = 0;//				VECTEUR HAUT
	base->cam.up.y = -1;
	base->cam.up.z = 0;
	//base->cam.up = normalize(base->cam.up);

	base->cam.forward.x = base->cam.target.x - base->cam.pos.x;//	VECTEUR DEVANT
	base->cam.forward.y = base->cam.target.y - base->cam.pos.y;
	base->cam.forward.z = base->cam.target.z - base->cam.pos.z;
	base->cam.forward = normalize(base->cam.forward);

	base->cam.right = cross(base->cam.forward, base->cam.up);//			VECTEUR DROITE
	base->cam.right = normalize(base->cam.right);

	base->cam.vertical = cross(base->cam.right, base->cam.forward);
	base->cam.vertical = normalize(base->cam.vertical);

	base->cam.w_view = 1.0;
	base->cam.h_view = 1.0;
	base->cam.dist = 0.5;


//	************** RAY *******************
	base->ray.origin.x = base->cam.pos.x;
	base->ray.origin.y = base->cam.pos.y;
	base->ray.origin.z = base->cam.pos.z;
	base->ray.cam_dir.x = 0;//la direction se place au tools 0/0 et look straight
	base->ray.cam_dir.y = 0;
	base->ray.cam_dir.z = 1;
	base->ray.cam_dir = normalize(base->ray.cam_dir);

	return (object);
}
