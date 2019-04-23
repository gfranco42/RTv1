/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:18:42 by gfranco           #+#    #+#             */
/*   Updated: 2019/04/23 12:34:00 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "macros.h"
# include <math.h>
# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 1200

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vector	normal;
	t_vector	point;
}				t_plane;

typedef struct	s_tools
{
	int		x;
	int		y;
	double	t;
	double	p;
	double	s1;
	double	s2;
}				t_tools;


typedef struct	s_mlx
{
	void	*ptr;
	void	*img;
	int		*win;
	char	*str;
	int		bpp;
	int		s_l;
	int		endian;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		mlx;
	t_tools		tools;
	t_vector	vector;
	t_sphere	sphere;
	t_plane		plane;
	t_ray		ray;
}				t_all;



double		dot(t_vector a, t_vector b);
void		draw_plane(t_ray ray, t_plane plane, t_mlx mlx, t_tools tools);
void		draw_sphere(t_ray ray, t_sphere sphere, t_mlx mlx, t_tools tools);
int			key(int key, void *param);
t_vector	normalize(t_vector v);
int			plane_intersect(t_plane plane, t_ray ray, double t);
double		power(double i, int power_value);
void		put_color(int x, int y, unsigned int *str, double dt);
int			sphere_intersect(t_sphere sphere, t_ray ray, double t);

#endif
