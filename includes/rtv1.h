/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:18:42 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/20 18:51:10 by pchambon         ###   ########.fr       */
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
	t_vector	cam_dir;
}				t_ray;

typedef struct	s_cam
{
	t_vector	pos;
	t_vector	target;
	t_vector	up;
	t_vector	vertical;
	t_vector	right;
	t_vector	forward;
	double		w_view;
	double		h_view;
	double		dist;
}				t_cam;

typedef struct	s_l_eff
{
	t_color		specular;
	t_color		diffuse;
	t_color		effect;
	double		ambient;
}				t_l_eff;

typedef struct	s_sphere
{
	t_vector	center;
	t_color		color;
	double		radius;
}				t_sphere;

typedef struct	s_cone
{
	t_vector	tip;
	t_color		color;
	t_vector	dir;
	double		angle;
}				t_cone;

typedef struct	s_plane
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
	int		i;
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
	t_cam		cam;
	t_vector	upleft;
	t_tools		tools;
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

typedef enum	e_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	LIGHT,
	CAMERA
}				t_type;

typedef struct	s_i
{
	int		i;
	int		cm;
	int		lt;
	int		nb;
	int		tmp;
}				t_i;

typedef	struct	s_prim
{
	t_type				type;
	t_sphere			sphere;
	t_plane				plane;
	t_cone				cone;
	t_cylinder			cyl;
	t_light				light;
	t_cam				cam;
}				t_prim;

void			fail(int i);
void			cone_ch(int fd);
void			plane_ch(int fd);
void			light_ch(int fd);
double			norm(t_vector v);
void			sphere_ch(int fd);
void			camera_ch(int fd);
void			cylinder_ch(int fd);
int				name_obj(char *line);
t_vector		vec3_extract(int fd);
int				str_isdot(char *str);
t_color			color_extract(int fd);
t_vector		normalize(t_vector v);
t_cone			init_cone(t_cone cone);
double			double_extract(int fd);
int				check_vec3(char *line);
int				str_isdigit(char *str);
int				str_isdouble(char *str);
t_prim			*create_tab(int nb_obj);
t_vector		upleft_calc(t_base base);
double			get_double(char **split);
t_plane			init_plane(t_plane plane);
int				key(int key, void *param);
double			dot(t_vector a, t_vector b);
t_sphere		init_sphere(t_sphere sphere);
void			free_tab(char **tab, int len);
t_vector		cross(t_vector a, t_vector b);
void			find_cam(t_i *i, t_prim *prim);
t_vector		reflect(t_vector n, t_vector i);
int				find_light(t_i i, t_prim *prim);
t_vector		vec_add(t_vector a, t_vector b);
t_vector		vec_sub(t_vector a, t_vector b);
t_vector		vec_div(t_vector a, t_vector b);
double			power(double i, int power_value);
t_vector		vec_mult(t_vector a, t_vector b);
t_vector		mult_double(t_vector a, double b);
t_cylinder		init_cylinder(t_cylinder cylinder);
void			free_prim(t_prim ***prim, int len);
t_vector		vec_div_double(t_vector a, double b);
t_vector		vec_add_double(t_vector a, double b);
t_vector		vec_sub_double(t_vector a, double b);
int				lexer(char *file, int number, int *cam);
void			calc_dir(t_vector upleft, t_base *base);
void			initialize_ray(t_cam cam, t_base *base);
void			cone_fill(int fd, t_prim *prim, int index);
void			light_fill(int fd, t_prim *prim, int index);
void			plane_fill(int fd, t_prim *prim, int index);
double			vec3_extract_x(char **split, char ***split2);
double			vec3_extract_y(char **split, char ***split2);
double			vec3_extract_z(char **split, char ***split2);
void			camera_fill(int fd, t_prim *prim, int index);
void			sphere_fill(int fd, t_prim *prim, int index);
t_prim			*parser(char *file, int number, t_prim *prim);
void			cylinder_fill(int fd, t_prim *prim, int index);
int				plane_light_inter(t_plane plane, t_light light);
int				cone_intersect(t_cone cone, t_ray ray, double t);
int				plane_intersect(t_plane plane, t_ray ray, double t);
void			print_pixel(t_mlx mlx, t_tools tools, t_color color);
void			draw_cyl(t_base base, t_prim *prim, t_mlx mlx, t_i i);
void			put_color(int x, int y, unsigned int *str, double dt);
int				sphere_intersect(t_sphere sphere, t_ray ray, double t);
t_color			rgb_value(t_color color, double r, double g, double b);
void			main_algo(t_base base, t_prim *prim, t_mlx mlx, t_i i);
t_color			diffuse_l(t_vector normal, t_vector lr, t_color color);
void			draw_prim(t_prim *prim, t_base base, t_mlx mlx, t_i i);
void			draw_cone(t_base base, t_prim *prim, t_mlx mlx, t_i i);
int				cylinder_intersect(t_cylinder cyl, t_ray ray, double t);
void			draw_plane(t_base base, t_prim *prim, t_mlx mlx, t_i i);
void			draw_sphere(t_base base, t_prim *prim, t_mlx mlx, t_i i);
double			intersect_prim(t_prim *prim, int i, t_base base, double t);
t_color			diffuse_l_alt(t_vector normal, t_vector lr, t_color color);
double			ambient_l(t_vector eye, t_vector normal, double intensity);
int				cyl_light_inter(t_cylinder cyl, t_light light, t_vector i_p);
int				shadow(t_prim *prim, t_i i, t_light light, t_vector inter_p);
t_color			specular_l(t_vector norm, t_vector half, t_color c, int sign);
int				sphere_light_int(t_sphere sphere, t_light light, t_vector ip);
t_color			light_effect(t_color diff, t_color spe, double amb, t_color c);
int				cone_light_inter(t_cone cone, t_light light, t_vector inter_p);

#endif
