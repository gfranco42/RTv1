/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:46:18 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//***************** METTRE LA COULEUR ****************************************

t_vector	reflect(t_vector nm, t_vector lr)
{
	t_vector	res;
	/*lr.x *= -1;
	lr.y *= -1;
	lr.z *= -1;*/

	res.x = 2.0 * dot(nm, lr) * nm.x - lr.x;
	res.y = 2.0 * dot(nm, lr) * nm.y - lr.y;
	res.z = 2.0 * dot(nm, lr) * nm.z - lr.z;
	return (res);
}

//***************** METTRE LA COULEUR ****************************************

void	put_color(int x, int y, unsigned int *str, double dt)
{
		str[y * WIDTH + x] = 0x89D8F9 * dt;
}

//***************** METTRE LA COULEUR ****************************************

double	power(double i, int power_value)
{
	double	tmp = i;
	while (power_value-- > 0)
		i *= tmp;
	return (i);
}

//***************** PRODUIT SCALAIRE *****************************************

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//***************** CREATION FENETRE *****************************************

void	win_create(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "FRACTOL GFRANCO");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->str = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->s_l),
	&(mlx->endian));
}

//***************** normaliser un vecteur  ***********************************

double	norm(t_vector v)
{
	double	res;

	v.x = v.x * v.x;
	v.y = v.y * v.y;
	v.z = v.z * v.z;

	res = v.x + v.y + v.z;
	res = sqrt(res);

	return (res);
}

//***************** normaliser un vecteur  ***********************************

t_vector	normalize(t_vector v)
{
	double	mg;

	mg = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x / mg;
	v.y = v.y / mg;
	v.z = v.z / mg;
	return (v);
}

void		fail(int i)
{
	if (i == 1)
	{
		write(1, "incorrect file\n", 15);
		exit(0);
	}
	else if (i == 2)
	{
		write(1, "usage: ./rtv1 <file>\n", 21);
		exit(0);
	}
	else if (i == 2)
	{
		write(1, "usage: ./rtv1 <file>\n", 21);
		exit(0);
	}
	else if (i == 3)
	{
		write(1, "fail to malloc obj tab\n", 23);
		exit(0);
	}
	else if (i == 4)
	{
		write(1, "ERROR: problem occurs during data procurement\n", 46);
		exit(0);
	}
}

//***************** MAIN *****************************************************

int		main(int ac, char **av)
{
	if (ac != 2)
		fail(2);
// ---------------  declaration de variables   -------------------------------
	t_mlx		mlx;
	t_base		base;
	t_tools		tools;
	t_object	object;
	t_prim		*prim;
	int			nb_obj;

	nb_obj = lexer(av[1], 0);
	prim = create_tab(nb_obj);
	prim = parser(av[1], nb_obj, prim);
// ---------------  creation de la fenetre  ----------------------------------
	win_create(&mlx);

// ---------------  initialisation des variables -----------------------------

//	************** FIRST SPHERE *******************
	object.sphere.center.x = WIDTH * 0.3;// creation d'un objet 'sphere'
	object.sphere.center.y = HEIGHT * 0.45;
	object.sphere.center.z = 1200;

	object.sphere.radius = 100;

	object.sphere.color.r = prim[0].sphere.color.r;// 			COULEUR
	object.sphere.color.g = prim[0].sphere.color.g;
	object.sphere.color.b = prim[0].sphere.color.b;

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
	object.plane.point.z = 200;

	object.plane.normal.x = 0;//			NORMALE DU PLAN
	object.plane.normal.y = HEIGHT * 0.20;
	object.plane.normal.z = 100;
	object.plane.normal = normalize(object.plane.normal);

	object.plane.color.r = 0xB3;// 			COULEUR
	object.plane.color.g = 0xFF;
	object.plane.color.b = 0xFB;

//	************** CONE *******************
	object.cone.tip.x = WIDTH / 2;//			POSITION POINTE
	object.cone.tip.y = 200;
	object.cone.tip.z = 500;

	object.cone.b_center.x = WIDTH / 2;//		CENTRE BASE
	object.cone.b_center.y = HEIGHT - 200;
	object.cone.b_center.z = 500;

	object.cone.b_radius = 0.14;

	object.cone.color.r = 0xFF;// 			COULEUR
	object.cone.color.g = 0x20;
	object.cone.color.b = 0;

//	************** cyl *******************
	object.cyl.center.x = 100;//		CENTER BASE
	object.cyl.center.y = HEIGHT;
	object.cyl.center.z = 100;

	object.cyl.dir.x = 10;//			DIRECTION
	object.cyl.dir.y = 1;
	object.cyl.dir.z = 1;

	object.cyl.radius = 50;//			RADIUS BASE

	object.cyl.color.r = 0;//			COULEUR
	object.cyl.color.g = 0x50;
	object.cyl.color.b = 0x50;

//	************** LIGHT *******************
	base.light.src.x = WIDTH / 2;//			POSITION SOURCE
	base.light.src.y = 0;
	base.light.src.z = -1000;

	base.light.color.r = 0xFF;// 			COULEUR
	base.light.color.g = 0xFF;
	base.light.color.b = 0xFF;

//	************** RAY *******************
	base.ray.origin.x = 600;
	base.ray.origin.y = 600;
	base.ray.origin.z = -1500;

	base.ray.dir.x = 0;//la direction se place au tools 0/0 et look straight
	base.ray.dir.y = 0;
	base.ray.dir.z = 0;

	tools.y = -1;// y = -1 car incrementation && t= 20000 pour donner un max
// ---------------  debut ----------------------------------------------------
	// balancer un rayon par pixel

	while (++tools.y < HEIGHT)
	{
		tools.x = -1;
		while (++tools.x < WIDTH)
		{
			tools.p = 200000;
			tools.s1 = 200000;
			tools.s2 = 200000;
			tools.c = 200000;
			tools.cy = 200000;
			base.ray.dir.x = tools.x - base.ray.origin.x;// origin prend le tools en cours (x/y)
			base.ray.dir.y = tools.y - base.ray.origin.y;
			base.ray.dir.z = 0 - base.ray.origin.z;
			base.ray.dir = normalize(base.ray.dir);
			tools.p = plane_intersect(object.plane, base.ray, tools.p);//check si intersection avec le plan
			tools.s1 = sphere_intersect(object.sphere, base.ray, tools.s1);// check si ya un obstacle
			tools.s2 = sphere_intersect(object.sphere2, base.ray, tools.s2);// check si ya un obstacle
			tools.c = cone_intersect(object.cone, base.ray, tools.c);
			tools.cy = cylinder_intersect(object.cyl, base.ray, tools.cy);
			if (tools.p < 5000 && tools.s1 == 200000 && tools.s2 == 200000
				&& tools.c == 200000 && tools.cy == 200000)
				draw_plane(base, object, mlx, tools);
			else if (tools.s1 < 200000 && tools.p == 2000 && tools.s2 == 200000
				&& tools.c == 200000 && tools.cy == 200000)
				draw_sphere(base, object, mlx, tools);
			else if (tools.s2 < 200000 && tools.s1 == 200000 && tools.p == 5000
				&& tools.c == 200000 && tools.cy == 200000)
				draw_sphere(base, object, mlx, tools);
			else if (tools.c < 200000 && tools.s1 == 200000 && tools.p == 5000
				&& tools.s2 == 200000 && tools.cy == 200000)
				draw_cone(base, object, mlx, tools);
			else if (tools.cy < 200000 && tools.s1 == 200000 && tools.p == 5000
				&& tools.s2 == 200000 && tools.c == 200000)
				draw_cylinder(base, object, mlx, tools);
			else
			{
				if (tools.p < tools.s1 && tools.p < tools.s2 && tools.p <= 5000
					&& tools.p < tools.c && tools.p < tools.cy)
					draw_plane(base, object, mlx, tools);
				if (tools.s1 < tools.p && tools.s1 < tools.s2
					&& tools.s1 < tools.c && tools.s1 < tools.cy)
					draw_sphere(base, object, mlx, tools);
				if (tools.s2 < tools.s1 && tools.s2 < tools.p
					&& tools.s2 < tools.c && tools.s2 < tools.cy)
					draw_sphere(base, object, mlx, tools);
				if (tools.c < tools.s1 && tools.c < tools.p
					&& tools.c < tools.s2 && tools.c < tools.cy)
					draw_cone(base, object, mlx, tools);
				if (tools.cy < tools.s1 && tools.cy < tools.p
					&& tools.cy < tools.c && tools.cy < tools.s2)
					draw_cylinder(base, object, mlx, tools);
			}
		}
	}
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
