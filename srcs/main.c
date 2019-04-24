/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/24 14:27:47 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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

t_vector	normalize(t_vector v)
{
	double	mg;

	mg = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x / mg;
	v.y = v.y / mg;
	v.z = v.z / mg;
	return (v);
}

//***************** MAIN *****************************************************

int		main()
{
// ---------------  declaration de variables   -------------------------------
	t_mlx		mlx;
	t_base		base;
	t_sphere	sphere;
	t_sphere	sphere2;
	t_plane		plane;
	t_tools		tools;

// ---------------  creation de la fenetre  ----------------------------------
	win_create(&mlx);

// ---------------  initialisation des variables -----------------------------

//	************** FIRST SPHERE *******************
	sphere.center.x = WIDTH / 2;// creation d'un objet 'sphere'
	sphere.center.y = HEIGHT / 2;
	sphere.center.z = 200;

	sphere.radius = 190;

	sphere.color.r = 0;
	sphere.color.g = 0xFF;
	sphere.color.b = 0;

//	************** SECOND SPHERE *******************
	sphere2.center.x = WIDTH * 0.8;// creation d'un objet 'sphere'
	sphere2.center.y = HEIGHT * 0.8;
	sphere2.center.z = 700;

	sphere2.radius = 690;

	sphere2.color.r = 0;
	sphere2.color.g = 200;
	sphere2.color.b = 0xFF;

//	************** PLANE *******************
	plane.point.x = WIDTH / 2;
	plane.point.y = HEIGHT * 0.9;
	plane.point.z = 200;

	plane.normal.x = 0;
	plane.normal.y = HEIGHT / 3;
	plane.normal.z = 100;
	plane.normal = normalize(plane.normal);

	plane.color.r = 0xFF;
	plane.color.g = 0;
	plane.color.b = 0xFF;

//	************** LIGHT *******************
	base.light.src.x = WIDTH * 0.6;
	base.light.src.y = HEIGHT * 0.8;
	base.light.src.z = 0;

//	************** RAY *******************
	base.ray.direction.x = 0;//la direction se place au tools 0/0 et look straight
	base.ray.direction.y = 0;
	base.ray.direction.z = 1;

	base.ray.origin.z = 0;

	tools.y = -1;// y = -1 car incrementation && t= 20000 pour donner un max
// ---------------  debut ----------------------------------------------------
	// balancer un rayon par pixel
	while (++tools.y < HEIGHT)
	{
		tools.x = -1;
		while (++tools.x < WIDTH)
		{
			tools.p = 1000;
			tools.s1 = 20000;
			tools.s2 = 20000;
			base.ray.origin.x = tools.x;// origin prend le tools en cours (x/y)
			base.ray.origin.y = tools.y;
			tools.p = plane_intersect(plane, base.ray, tools.p);//check si intersection avec le plan
			tools.s1 = sphere_intersect(sphere, base.ray, tools.s1);// check si ya un obstacle
			tools.s2 = sphere_intersect(sphere2, base.ray, tools.s2);// check si ya un obstacle
			if (tools.p <= 1000 && tools.s1 == 1000 && tools.s2 == 1000 && tools.p)
				draw_plane(base, plane, mlx, tools);
			else if (tools.s1 < 20000 && tools.p == 20000 && tools.s2 == 20000)
				draw_sphere(base, sphere, mlx, tools);
			else if (tools.s2 < 20000 && tools.s1 == 20000 && tools.p == 20000)
				draw_sphere(base, sphere2, mlx, tools);
			else
			{
				if (tools.p < tools.s1 && tools.p < tools.s2 && tools.p <= 1000)
					draw_plane(base, plane, mlx, tools);
				if (tools.s1 < tools.p && tools.s1 < tools.s2)
					draw_sphere(base, sphere, mlx, tools);
				if (tools.s2 < tools.s1 && tools.s2 < tools.p)
					draw_sphere(base, sphere2, mlx, tools);
			}
		}
	}
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
