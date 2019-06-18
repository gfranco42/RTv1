/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/18 15:29:43 by gfranco          ###   ########.fr       */
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
	t_prim		*prim;
	double		tmp;
	int			nb_obj;
	int			cam;
	int			idx[4];

	if (ac != 2)
		fail(2);
	cam = 0;
	nb_obj = lexer(av[1], 0, &cam);
	if (cam != 1)
		fail(1);
	prim = create_tab(nb_obj);
	prim = parser(av[1], nb_obj, prim);
	while (++idx[0] < nb_obj)
	{
		if (prim[idx[0]].type == LIGHT)
			idx[2] = idx[0];
		if (prim[idx[0]].type == CAMERA)
			idx[3] = idx[0];
	}
	upleft = upleft_calc(base);
	initialize_ray(prim[idx[3]], base);
	idx[0] = -1;
	win_create(&mlx);
	base.tools.y = -1;
	while (++base.tools.y < HEIGHT)
	{
		base.tools.x = -1;
		while (++base.tools.x < WIDTH)
		{
			base.tools.t = 20000;
			tmp = 20000;
			base.ray.dir.x = upleft.x + base.cam.right.x * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.x * base.cam.w_view / HEIGHT * base.tools.y;
			base.ray.dir.y = upleft.y + base.cam.right.y * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.y * base.cam.w_view / HEIGHT * base.tools.y;
			base.ray.dir.z = upleft.z + base.cam.right.z * base.cam.h_view
			/ WIDTH * base.tools.x - base.cam.up.z * base.cam.w_view / HEIGHT * base.tools.y;
			base.ray.dir = normalize(base.ray.dir);
			while (++idx[0] < nb_obj)
			{
				if (prim[idx[0]].type == CAMERA && prim[idx[0]].type == LIGHT)
					continue ;
				tmp = intersect_prim(prim, idx[0], base, base.tools.t);
				if (tmp < base.tools.t)
				{
					base.tools.t = tmp;
					idx[1] = idx[0];
				}
			}
			idx[0] = -1;
			if (base.tools.t < 20000)
				draw_prim(prim, base, mlx, idx[1]);
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
	free(prim);
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
