/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:49:29 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:43:23 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_prim		*create_tab(int nb_obj)
{
	t_prim	*prim;
	printf("nb_obj: %d\n", nb_obj);

	if (!(prim = (t_prim*)malloc(sizeof(*prim) * nb_obj)))
		fail(3);
	return (prim);
}

t_prim			*parser(char *file, int number, t_prim *prim)
{
	int		i;
	int		fd;
	char	*line;
	typedef void	(*t_check)(int, t_prim*, int);
	const t_check prim_obj[] = {&sphere_fill, &plane_fill, &cone_fill,
	&cylinder_fill, &light_fill};

	if ((fd = open(file, O_RDONLY)) < 0)
		fail(1);
	while (get_next_line(fd, &line) > 0)
	{
		printf("GOOOOOOOO\n");
		if (ft_strcmp(line, "") == 0)
			continue ;
		if ((i = name_obj(line, &number)) != -1)
		{

			printf("i: %d\n", i);
			prim_obj[i](fd, prim, i);
		}
		else
		{
			free(line);
			fail(1);
		}
		free(line);
		printf("x: %lf, y: %lf, z: %lf\n", prim[i].sphere.center.x, prim[i].sphere.center.y, prim[i].sphere.center.z);
		printf("radius: %lf\n", prim[i].sphere.radius);
		printf("r: %d, g: %d, b: %d\n", prim[i].sphere.color.r, prim[i].sphere.color.g, prim[i].sphere.color.b);
	}
	return (prim);
}
