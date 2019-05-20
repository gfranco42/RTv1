/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/20 18:32:24 by gfranco          ###   ########.fr       */
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

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
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

	t_vector	upleft;

//-------------- INITIALISATION VARIABLES ----------------------------------

	object = initialize_var(&base);

	// * * * * * UP LEFT * * * * *
	upleft.x = base.cam.dist * base.cam.forward.x + base.cam.h_view / 2
	* base.cam.up.x - base.cam.w_view / 2 * base.cam.right.x;
	upleft.y = base.cam.dist * base.cam.forward.y + base.cam.h_view / 2
	* base.cam.up.y - base.cam.w_view / 2 * base.cam.right.y;
	upleft.z = base.cam.dist * base.cam.forward.z + base.cam.h_view / 2
	* base.cam.up.z - base.cam.w_view / 2 * base.cam.right.z;
	upleft = normalize(upleft);

//-------------- CREATION TABLEAU STRUCTURES ----------------------------------
	nb_obj = lexer(av[1], 0);
	prim = create_tab(nb_obj);
	prim = parser(av[1], nb_obj, prim);

// ---------------  creation de la fenetre  ----------------------------------
	win_create(&mlx);

// ---------------  debut ----------------------------------------------------
	// balancer un rayon par pixel

	tools.y = -1;// y = -1 car incrementation && t= 20000 pour donner un max
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

			base.ray.dir.x = upleft.x + base.cam.right.x * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.x * base.cam.w_view / HEIGHT * tools.y;
			base.ray.dir.y = upleft.y + base.cam.right.y * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.y * base.cam.w_view / HEIGHT * tools.y;
			base.ray.dir.z = upleft.z + base.cam.right.z * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.z * base.cam.w_view / HEIGHT * tools.y;


			base.ray.dir.x = base.ray.origin.x - base.ray.dir.x;
			base.ray.dir.y = base.ray.origin.y - base.ray.dir.y;
			base.ray.dir = normalize(base.ray.dir);

		//	printf("%lf|", base.ray.dir.x);


			/*base.ray.dir.x = upleft.x + right.x * 0.35 / WIDTH * tools.x - up.x * 0.5 / HEIGHT * tools.y;
			base.ray.dir.y = upleft.y + right.y * 0.35 / WIDTH * tools.x - up.y * 0.5 / HEIGHT * tools.y;
			base.ray.dir.z = upleft.z + right.z * 0.35 / WIDTH * tools.x - up.z * 0.5 / HEIGHT * tools.y;*/
			//printf("%lf|", base.ray.dir.x);

			/*base.ray.dir.x = -1 * WIDTH / 2 + tools.x
			* base.ray.cam_dir.z;
			base.ray.dir.y = (base.ray.origin.y - HEIGHT / 2 + tools.y)
			- base.ray.origin.y;
			base.ray.dir.z = 1000 * base.ray.cam_dir.z + tools.x
			* base.ray.cam_dir.x + tools.y * base.ray.cam_dir.y;*/
		/*	printf("x: %lf|", base.ray.dir.x);
			printf("y: %lf|", base.ray.dir.y);
			printf("z: %lf|", base.ray.dir.z);*/
			tools.p = plane_intersect(object.plane, base.ray, tools.p);//check si intersection avec le plan
			tools.s1 = sphere_intersect(object.sphere, base.ray, tools.s1);// check si ya un obstacle
			tools.s2 = sphere_intersect(object.sphere2, base.ray, tools.s2);// check si ya un obstacle
			tools.c = cone_intersect(object.cone, base.ray, tools.c);
			tools.cy = cylinder_intersect(object.cyl, base.ray, tools.cy);
			if (tools.p < tools.s1 && tools.p < tools.s2 && tools.p <= 100000
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
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
