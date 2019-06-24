/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:18:42 by gfranco           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/24 11:25:52 by gfranco          ###   ########.fr       */
=======
/*   Updated: 2019/06/21 03:18:54 by pchambon         ###   ########.fr       */
>>>>>>> b9daabd7e66dd3a019b7c1bdac02ae51a838f0fb
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "macros.h"
# include "../libft/libft.h"
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
	int		j;
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

<<<<<<< HEAD
double		ambient_l(t_vector eye, t_vector normal, double intensity);
void		calc_dir(t_vector upleft, t_base *base);
void		camera_ch(int fd);
void		camera_fill(int fd, t_prim *prim, int index);
t_color		cap(t_color color);
int			check_vec3(char *line);
t_color		color_extract(int fd);
void		cone_ch(int fd);
void		cone_fill(int fd, t_prim *prim, int index);
int			cone_intersect(t_cone cone, t_ray ray, double t);
int			cone_light_inter(t_cone cone, t_light light, t_vector inter_p);
t_prim		*create_tab(int nb_obj);
t_vector	cross(t_vector a, t_vector b);
void		cylinder_ch(int fd);
void		cylinder_fill(int fd, t_prim *prim, int index);
int			cylinder_intersect(t_cylinder cyl, t_ray ray, double t);
int			cyl_light_inter(t_cylinder cyl, t_light light, t_vector inter_p);
t_color		diffuse_l(t_vector normal, t_vector lr, t_color color);
t_color		diffuse_l_alt(t_vector normal, t_vector lr, t_color color);
double		dot(t_vector a, t_vector b);
double		double_extract(int fd);
void		draw_cone(t_base base, t_prim *prim, t_mlx mlx, t_i i);
void		draw_cyl(t_base base, t_prim *prim, t_mlx mlx, t_i i);
void		draw_plane(t_base base, t_prim *prim, t_mlx mlx, t_i i);
void		draw_prim(t_prim *prim, t_base base, t_mlx mlx, t_i i);
void		draw_sphere(t_base base, t_prim *prim, t_mlx mlx, t_i i);
t_vector	getnormal_cone(t_vector	inter_p, t_cone cone, t_ray ray, double t);
t_vector	getnm_cyl(t_cylinder cyl, t_vector inter_p, t_ray ray, double t);
t_vector	getnormal_sphere(t_sphere sphere, t_vector inter_p);
void		initialize_ray(t_cam cam, t_base *base);
t_cone		init_cone(t_cone cone);
t_cylinder	init_cylinder(t_cylinder cylinder);
t_plane		init_plane(t_plane plane);
t_sphere	init_sphere(t_sphere sphere);
double		intersect_prim(t_prim *prim, int i, t_base base, double t);
void		fail(int i);
void		find_cam(t_i *i, t_prim *prim);
int			find_light(t_i i, t_prim *prim);
void		free_prim(t_prim ***prim, int len);
void		free_tab(char **tab, int len);
double		get_double(char **split);
int			key(int key, void *param);
int			lexer(char *file, int number, int *cam);
void		light_ch(int fd);
t_color		light_effect(t_color diff, t_color spec, double amb, t_color color);
void		light_fill(int fd, t_prim *prim, int index);
void		main_algo(t_base base, t_prim *prim, t_mlx mlx, t_i i);
t_color		multi_l_s(t_prim *prim, t_base base, t_color color, t_i i);
t_color		multi_l_p(t_prim *prim, t_base base, t_color color, t_i i);
int			name_obj(char *line);
double		norm(t_vector v);
t_vector	normalize(t_vector v);
void		plane_ch(int fd);
void		plane_fill(int fd, t_prim *prim, int index);
int			plane_intersect(t_plane plane, t_ray ray, double t);
int			plane_light_inter(t_plane plane, t_light light);
t_prim		*parser(char *file, int number, t_prim *prim);
void		print_pixel(t_mlx mlx, t_tools tools, t_color color);
double		power(double i, int power_value);
void		put_color(int x, int y, unsigned int *str, double dt);
t_vector	reflect(t_vector n, t_vector i);
t_color		rgb_value(t_color color, double r, double g, double b);
int			shadow(t_prim *prim, t_i i, t_light light, t_vector inter_p);
t_color		specular_l(t_vector normal, t_vector half, t_color color, int sign);
void		sphere_ch(int fd);
void		sphere_fill(int fd, t_prim *prim, int index);
int			sphere_intersect(t_sphere sphere, t_ray ray, double t);
int			sphere_light_int(t_sphere sphere, t_light light, t_vector inter_p);
int			str_isdigit(char *str);
int			str_isdot(char *str);
int			str_isdouble(char *str);
t_vector	upleft_calc(t_base base);
t_vector	vec_add(t_vector a, t_vector b);
t_vector	vec_sub(t_vector a, t_vector b);
t_vector	vec_mult(t_vector a, t_vector b);
t_vector	vec_div(t_vector a, t_vector b);
t_vector	vec_add_double(t_vector a, double b);
t_vector	vec_sub_double(t_vector a, double b);
t_vector	vec_mult_d(t_vector a, double b);
t_vector	vec_div_double(t_vector a, double b);
t_vector	vec3_extract(int fd);
double		vec3_extract_x(char **split, char ***split2);
double		vec3_extract_y(char **split, char ***split2);
double		vec3_extract_z(char **split, char ***split2);
=======
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
>>>>>>> b9daabd7e66dd3a019b7c1bdac02ae51a838f0fb

#endif
