/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/17 17:11:12 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	win_create(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "FRACTOL GFRANCO");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->str = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->s_l),
	&(mlx->endian));
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
	else if (i == 5)
	{
		write(1, "ERROR: Wrong camera settings\n", 29);
		exit(0);
	}
}

int		main(int ac, char **av)
{
	t_mlx		mlx;
	t_vector	upleft;
	t_base		base;
	t_object	object;
	t_prim		*prim;
	double		tmp;
	int			nb_obj;
	int			cam;
	int			i = -1;
	int			j;

	if (ac != 2)
		fail(2);
	object = initialize_var(&base);
	upleft = upleft_calc(base);
	cam = 0;
	nb_obj = lexer(av[1], 0, &cam);
	if (cam != 1)
		fail(1);
	prim = create_tab(nb_obj);
	prim = parser(av[1], nb_obj, prim);
	while (++i < nb_obj)
	{
		if (prim[i].type == LIGHT)
		{
			base.light.src.x = prim[i].light.src.x;
			base.light.src.y = prim[i].light.src.y;
			base.light.src.z = prim[i].light.src.z;
			base.light.color.r = prim[i].light.color.r;
			base.light.color.g = prim[i].light.color.g;
			base.light.color.b = prim[i].light.color.b;
		}
		if (prim[i].type == CAMERA)
		{
			base.cam.pos.x = prim[i].cam.pos.x;
			base.cam.pos.y = prim[i].cam.pos.y;
			base.cam.pos.z = prim[i].cam.pos.z;
			base.cam.target.x = prim[i].cam.target.x;
			base.cam.target.y = prim[i].cam.target.y;
			base.cam.target.z = prim[i].cam.target.z;
			base.cam.up.x = prim[i].cam.up.x;
			base.cam.up.y = prim[i].cam.up.y;
			base.cam.up.z = prim[i].cam.up.z;
			prim[i].cam.forward = normalize(vec_sub(prim[i].cam.target, prim[i].cam.pos));
			prim[i].cam.right = normalize(cross(prim[i].cam.forward, prim[i].cam.up));
			prim[i].cam.vertical = normalize(cross(prim[i].cam.right, prim[i].cam.forward));
			prim[i].cam.w_view = 1.0;
			prim[i].cam.h_view = 1.0;
			prim[i].cam.dist = 0.5;
			base.cam.forward.x = prim[i].cam.forward.x;
			base.cam.forward.y = prim[i].cam.forward.y;
			base.cam.forward.z = prim[i].cam.forward.z;
			base.cam.right.x = prim[i].cam.right.x;
			base.cam.right.y = prim[i].cam.right.y;
			base.cam.right.z = prim[i].cam.right.z;
			base.cam.vertical.x = prim[i].cam.vertical.x;
			base.cam.vertical.y = prim[i].cam.vertical.y;
			base.cam.vertical.z = prim[i].cam.vertical.z;
			base.cam.w_view = 1.0;
			base.cam.h_view = 1.0;
			base.cam.dist = 0.5;
		}
	}
	i = -1;

	win_create(&mlx);

	base.tools.y = -1;
	while (++base.tools.y < HEIGHT)
	{
		base.tools.x = -1;
		while (++base.tools.x < WIDTH)
		{

		/*	tools.p = 20000;
			tools.s1 = 20000;
			tools.s2 = 20000;
			tools.c = 20000;
			tools.cy = 20000;*/
			base.tools.t = 20000;
			tmp = 20000;
			base.ray.dir.x = upleft.x + base.cam.right.x * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.x * base.cam.w_view / HEIGHT * base.tools.y;
			base.ray.dir.y = upleft.y + base.cam.right.y * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.y * base.cam.w_view / HEIGHT * base.tools.y;
			base.ray.dir.z = upleft.z + base.cam.right.z * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.z * base.cam.w_view / HEIGHT * base.tools.y;

			base.ray.dir = normalize(base.ray.dir);
			//if (base.tools.y == 10 && base.tools.x == 20)
			//	exit(0);

			while (++i < nb_obj)
			{
				if (prim[i].type == CAMERA && prim[i].type == LIGHT)
					continue ;
				tmp = intersect_prim(prim, i, base, base.tools.t);
				if (tmp < base.tools.t)
				{
					base.tools.t = tmp;
					j = i;
				}
			}
			i = -1;
			if (base.tools.t < 20000)
				draw_prim(prim, base, mlx, j);
/*			tools.p = plane_intersect(object.plane, base.ray, tools.p);//check si intersection avec le plan
			tools.s1 = sphere_intersect(object.sphere, base.ray, tools.s1);// check si ya un obstacle
			tools.s2 = sphere_intersect(object.sphere2, base.ray, tools.s2);// check si ya un obstacle
			tools.c = cone_intersect(object.cone, base.ray, tools.c);
			tools.cy = cylinder_intersect(object.cyl, base.ray, tools.cy);*/
			/*if (tools.p < tools.s1 && tools.p < tools.s2 && tools.p <= 100000
				&& tools.p < tools.c && tools.p < tools.cy)
				draw_plane(base, object, mlx, tools);
			if (tools.s1 < tools.p && tools.s1 < tools.s2
				&& tools.s1 < tools.c && tools.s1 < tools.cy)
				draw_sphere(base, object.sphere, mlx, tools);
			if (tools.s2 < tools.s1 && tools.s2 < tools.p
				&& tools.s2 < tools.c && tools.s2 < tools.cy)
				draw_sphere(base, object.sphere, mlx, tools);
			if (tools.c < tools.s1 && tools.c < tools.p
				&& tools.c < tools.s2 && tools.c < tools.cy)
				draw_cone(base, object, mlx, tools);
			if (tools.cy < tools.s1 && tools.cy < tools.p
				&& tools.cy < tools.c && tools.cy < tools.s2)
				draw_cylinder(base, object, mlx, tools);*/
		}
	}
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
