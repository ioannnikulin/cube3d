/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:27:52 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/26 12:23:28 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <math.h>
# include <stdbool.h>

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}	t_point;

typedef struct s_vector
{
	t_point	from;
	t_point	to;
}	t_vector;

t_vector	*ft_vector_dup(t_vector src);
void		ft_vector_cp(t_vector from, t_vector *to);
t_vector	ft_vector_make(t_point from, t_point to);
/*t_vector	ft_vector_add(t_vector *a, t_vector *b);
t_vector	ft_vector_sub(t_vector *a, t_vector *b);
t_vector	ft_vector_mult(t_vector *a, t_vector *b);*/
bool		ft_vector_eq(t_vector *a, t_vector *b, double epsilon);
t_vector	ft_vector_move(t_vector *a, double b);
t_vector	ft_vector_rot(t_vector *a, double b);
t_vector	ft_vector_rot_z(t_vector *a, double b);
void		ft_vector_move_here(t_vector *a, double b);
void		ft_vector_rot_here(t_vector *a, double b);
void		ft_vector_rot_z_here(t_vector *a, double b);
double		ft_vector_len(t_vector *a);
double		ft_vector_x(t_vector *a);
double		ft_vector_y(t_vector *a);
double		ft_vector_z(t_vector *a);

t_point		*ft_point_dup(t_point src);
t_point		ft_point_make(double x, double y);
void		ft_point_cp(t_point from, t_point *to);
bool		ft_point_eq(t_point *a, t_point *b, double epsilon);
void		ft_swap_pts(t_point **a, t_point **b);
t_point		ft_point_add(t_point *a, t_point *b);
t_point		ft_point_sub(t_point *a, t_point *b);
t_point		ft_point_scale(t_point *a, double b);
t_point		ft_point_norm(t_point *a);
t_point		ft_point_rot_x(t_point *a, double angle);
t_point		ft_point_rot_y(t_point *a, double angle);
t_point		ft_point_rot_z(t_point *a, double angle);
t_point		ft_point_rot(t_point *a, double angle);
void		ft_point_add_here(t_point *a, t_point *b);
void		ft_point_sub_here(t_point *a, t_point *b);
void		ft_point_scale_here(t_point *a, double b);
void		ft_point_norm_here(t_point *a);
void		ft_point_rot_x_here(t_point *a, double angle);
void		ft_point_rot_y_here(t_point *a, double angle);
void		ft_point_rot_z_here(t_point *a, double angle);
void		ft_point_rot_here(t_point *a, double angle);

#endif