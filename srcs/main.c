/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:09:17 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/20 21:41:29 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		free_tab(char **tab, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
}

void		win_create(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "RTv1");
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

int			main(int ac, char **av)
{
	t_mlx		mlx;
	t_base		base;
	t_prim		*prim;
	t_i			i;
	int			cam;

	if (ac != 2)
		fail(2);
	cam = 0;
	i.nb = lexer(av[1], 0, &cam);
	if (cam != 1)
		fail(1);
	prim = create_tab(i.nb);
	prim = parser(av[1], i.nb, prim);
	i.i = -1;
	find_cam(&i, prim);
	initialize_ray(prim[i.cm].cam, &base);
	base.upleft = upleft_calc(base);
	i.i = -1;
	win_create(&mlx);
	main_algo(base, prim, mlx, i);
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, key, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}
