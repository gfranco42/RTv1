/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:18:42 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:43:38 by gfranco          ###   ########.fr       */
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

//*************  STRUCTURES  ****************
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

typedef struct	s_light
{
	t_vector	src;
	t_vector	ray;
	t_color		color;
}				t_light;

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	dir;
}				t_ray;

typedef struct s_sphere
{
	t_vector	center;
	t_color		color;
	double		radius;
}				t_sphere;

typedef struct	s_cone
{
	t_vector	tip;
	t_color		color;
	t_vector	b_center;
	double		b_radius;
}				t_cone;

typedef struct s_plane
{
	t_vector	normal;
	t_color		color;
	t_vector	point;
}				t_plane;

typedef struct	s_cylinder
{
	t_vector	center;
	t_vector	dir;
	t_color		color;
	double		radius;
}				t_cylinder;

typedef struct	s_object
{
	t_sphere	sphere;
	t_sphere	sphere2;
	t_plane		plane;
	t_cone		cone;
	t_cylinder	cyl;
}				t_object;

typedef struct	s_tools
{
	int		x;
	int		y;
	double	t;
	double	p;
	double	s1;
	double	s2;
	double	cy;
	double	c;
}				t_tools;

typedef struct	s_base
{
	t_light		light;
	t_ray		ray;
}				t_base;


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

//************* ENUM ****************
typedef enum	e_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	LIGHT
}				t_type;

//************* STRUCTURE UNION ****************
typedef	struct	s_prim
{
	t_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cone		cone;
		t_cylinder	cyl;
		t_light		light;
	};
}				t_prim;

//*************  FUNCTIONS ****************
int			check_vec3(char *line);
t_color		color_extract(int fd);
void		cone_ch(int fd);
void		cone_fill(int fd, t_prim *prim, int index);
int			cone_intersect(t_cone cone, t_ray ray, double t);
void		cylinder_ch(int fd);
void		cylinder_fill(int fd, t_prim *prim, int index);
int			cylinder_intersect(t_cylinder cyl, t_ray ray, double t);
double		dot(t_vector a, t_vector b);
double		double_extract(int fd);
void		draw_cone(t_base base, t_object object, t_mlx mlx, t_tools tools);
void		draw_cylinder(t_base base, t_object object, t_mlx mlx, t_tools tools);
void		draw_plane(t_base base, t_object object, t_mlx mlx, t_tools tools);
void		draw_sphere(t_base base, t_object object, t_mlx mlx, t_tools tools);
void		fail(int i);
int			key(int key, void *param);
int			lexer(char *file, int number);
void		light_ch(int fd);
void		light_fill(int fd, t_prim *prim, int index);
int			name_obj(char *line, int *number);
double		norm(t_vector v);
t_vector	normalize(t_vector v);
void		plane_ch(int fd);
void		plane_fill(int fd, t_prim *prim, int index);
int			plane_intersect(t_plane plane, t_ray ray, double t);
t_prim		*parser(char *file, int number, t_prim *prim);
double		power(double i, int power_value);
t_prim		*create_tab(int nb_obj);
void		put_color(int x, int y, unsigned int *str, double dt);
t_vector	reflect(t_vector n, t_vector i);
void		sphere_ch(int fd);
void		sphere_fill(int fd, t_prim *prim, int index);
int			sphere_intersect(t_sphere sphere, t_ray ray, double t);
int			sphere_light_inter(t_sphere sphere, t_light light, t_vector inter_p);
int			str_isdigit(char *str);
int			str_isdot(char *str);
int			str_isdouble(char *str);
t_vector	vec3_extract(int fd);

#endif
