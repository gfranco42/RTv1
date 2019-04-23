/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/23 17:00:58 by gfranco          ###   ########.fr       */
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
	t_ray		ray;
	t_sphere	sphere;
	t_sphere	sphere2;
	t_plane		plane;
	t_tools		tools;

// ---------------  creation de la fenetre  ----------------------------------
	win_create(&mlx);

// ---------------  initialisation des variables -----------------------------

	sphere.center.x = WIDTH / 2;// creation d'un objet 'sphere'
	sphere.center.y = HEIGHT / 2;
	sphere.center.z = 200;
	sphere.radius = 190;

	sphere2.center.x = WIDTH * 0.8;// creation d'un objet 'sphere'
	sphere2.center.y = HEIGHT * 0.8;
	sphere2.center.z = 700;
	sphere2.radius = 690;

	plane.point.x = WIDTH / 2;
	plane.point.y = HEIGHT * 0.9;
	plane.point.z = 200;
	plane.normal.x = 0;
	plane.normal.y = HEIGHT / 3;
	plane.normal.z = 10;
	plane.normal = normalize(plane.normal);

	tools.y = -1;// y = -1 car incrementation && t= 20000 pour donner un max

	ray.direction.x = 0;//la direction se place au tools 0/0 et look straight
	ray.direction.y = 0;
	ray.direction.z = 1;
	ray.origin.z = 0;

// ---------------  debut ----------------------------------------------------
	// balancer un rayon par pixel
	while (++tools.y < HEIGHT)
	{
		tools.x = -1;
		while (++tools.x < WIDTH)
		{
			tools.p = 20000;
			tools.s1 = 20000;
			tools.s2 = 20000;
			ray.origin.x = tools.x;// origin prend le tools en cours (x/y)
			ray.origin.y = tools.y;
			tools.p = plane_intersect(plane, ray, tools.p);//check si intersection avec le plan
			tools.s1 = sphere_intersect(sphere, ray, tools.s1);// check si ya un obstacle
			tools.s2 = sphere_intersect(sphere2, ray, tools.s2);// check si ya un obstacle
			if (tools.p <= 20000 && tools.s1 == 20000 && tools.s2 == 20000 && tools.p)
				draw_plane(ray, plane, mlx, tools);
			else if (tools.s1 < 20000 && tools.p == 20000 && tools.s2 == 20000)
				draw_sphere(ray, sphere, mlx, tools);
			else if (tools.s2 < 20000 && tools.s1 == 20000 && tools.p == 20000)
				draw_sphere(ray, sphere2, mlx, tools);
			else
			{
				if (tools.p < tools.s1 && tools.p < tools.s2 && tools.p <= 20000)
					draw_plane(ray, plane, mlx, tools);
				if (tools.s1 < tools.p && tools.s1 < tools.s2)
					draw_sphere(ray, sphere, mlx, tools);
				if (tools.s2 < tools.s1 && tools.s2 < tools.p)
					draw_sphere(ray, sphere2, mlx, tools);
			}
		}
	}
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
