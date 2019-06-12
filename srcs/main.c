/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/12 14:50:26 by gfranco          ###   ########.fr       */
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
	t_tools		tools;
	t_object	object;
	t_prim		*prim;
/*	double		t;
	double		tmp;*/
	int			nb_obj;
	int			cam;

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
	int	i = -1;
	while (++i < nb_obj)
		printf("%d\n", prim[i].type);
	i = -1;

	win_create(&mlx);

	tools.y = -1;
	while (++tools.y < HEIGHT)
	{
		tools.x = -1;
		while (++tools.x < WIDTH)
		{
			tools.p = 20000;
			tools.s1 = 20000;
			tools.s2 = 20000;
			tools.c = 20000;
			tools.cy = 20000;
			base.ray.dir.x = upleft.x + base.cam.right.x * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.x * base.cam.w_view / HEIGHT * tools.y;
			base.ray.dir.y = upleft.y + base.cam.right.y * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.y * base.cam.w_view / HEIGHT * tools.y;
			base.ray.dir.z = upleft.z + base.cam.right.z * base.cam.h_view
			/ WIDTH * tools.x - base.cam.up.z * base.cam.w_view / HEIGHT * tools.y;

			base.ray.dir = normalize(base.ray.dir);

		/*	while (++i < nb_obj)
			{
				tmp = t;
				tools.t = intersect_prim(prim, i, base) < tmp ?
			}*/
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
				draw_sphere(base, object.sphere, mlx, tools);
			if (tools.s2 < tools.s1 && tools.s2 < tools.p
				&& tools.s2 < tools.c && tools.s2 < tools.cy)
				draw_sphere(base, object.sphere, mlx, tools);
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
