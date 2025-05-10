/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:01:21 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/02 12:53:29 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle_internal.h"

static void	hor(t_mlx *mlx, t_vector segment, t_color *color)
{
	int	x;

	if (segment.from.x > segment.to.x)
		ft_swap_d(&(segment.from.x), &(segment.to.x));
	x = segment.from.x - 1;
	while (++x <= segment.to.x)
		pixel(mlx, x, segment.from.y, *color);
}

/*
 * ab is flat top
 */
static void	flat_top(t_triangle_arg *arg)
{
	double	inv_slope_1;
	double	inv_slope_2;
	double	cx1;
	double	cx2;
	int		y;

	inv_slope_1 = (double)(arg->sorted_vertices.c->x
			- arg->sorted_vertices.a->x) / (arg->sorted_vertices.c->y
			- arg->sorted_vertices.a->y);
	inv_slope_2 = (double)(arg->sorted_vertices.c->x
			- arg->sorted_vertices.b->x) / (arg->sorted_vertices.c->y
			- arg->sorted_vertices.b->y);
	cx1 = arg->sorted_vertices.c->x;
	cx2 = cx1;
	y = arg->sorted_vertices.c->y;
	while (y >= arg->sorted_vertices.a->y)
	{
		hor(arg->mlx, ft_vector_make(ft_point_make(cx1, y), ft_point_make(cx2,
					y)), arg->color);
		cx1 -= inv_slope_1;
		cx2 -= inv_slope_2;
		y--;
	}
}

/*
 * bc is flat bottom
 */
static void	flat_bottom(t_triangle_arg *arg)
{
	double	inv_slope_1;
	double	inv_slope_2;
	double	cx1;
	double	cx2;
	int		y;

	inv_slope_1 = (double)(arg->sorted_vertices.b->x
			- arg->sorted_vertices.a->x) / (arg->sorted_vertices.b->y
			- arg->sorted_vertices.a->y);
	inv_slope_2 = (double)(arg->sorted_vertices.c->x
			- arg->sorted_vertices.a->x) / (arg->sorted_vertices.c->y
			- arg->sorted_vertices.a->y);
	cx1 = arg->sorted_vertices.a->x;
	cx2 = cx1;
	y = arg->sorted_vertices.a->y;
	while (y <= arg->sorted_vertices.b->y)
	{
		hor(arg->mlx, ft_vector_make(ft_point_make(cx1, y), ft_point_make(cx2,
					y)), arg->color);
		cx1 += inv_slope_1;
		cx2 += inv_slope_2;
		y++;
	}
}

static void	find_mid_hor(t_triangle_arg *arg, t_point *tgt)
{
	*tgt = ft_point_make(arg->sorted_vertices.a->x
			+ (double)(arg->sorted_vertices.b->y - arg->sorted_vertices.a->y)
			* (arg->sorted_vertices.c->x - arg->sorted_vertices.a->x)
			/ (arg->sorted_vertices.c->y - arg->sorted_vertices.a->y),
			arg->sorted_vertices.b->y);
}

/*
 * a triangle can have a flat top or a flat bottom.
 * if none, then we find the vertically middle point (find_mid_hor)
 * find its horizontal counterpart,
 * and split the triangle into a flattop and flatbottom
 * having these middle and counterpart points as a horizontal separation line
 *
 * possible problems: tmp init and find_mid_hor spoiling a point
 */
/*
 * line(arg.mlx, arg.sorted_vertices.a, arg.sorted_vertices.b);
 * line(arg.mlx, arg.sorted_vertices.b, arg.sorted_vertices.c);
 * line(arg.mlx, arg.sorted_vertices.a, arg.sorted_vertices.c);
 */
int	triangle(t_triangle_arg arg)
{
	t_triangle_arg	tmp;

	if (arg.fill)
	{
		if (arg.sorted_vertices.b->y == arg.sorted_vertices.c->y)
			flat_bottom(&arg);
		else if (arg.sorted_vertices.a->y == arg.sorted_vertices.b->y)
			flat_top(&arg);
		else
		{
			tmp = triangle_arg(arg.mlx, arg.sorted_vertices, arg.color,
					arg.fill);
			find_mid_hor(&arg, tmp.sorted_vertices.c);
			flat_bottom(&tmp);
			ft_swap_pts(&(tmp.sorted_vertices.a), &(tmp.sorted_vertices.b));
			ft_swap_pts(&(tmp.sorted_vertices.b), &(tmp.sorted_vertices.c));
			tmp.sorted_vertices.c = arg.sorted_vertices.c;
			flat_top(&tmp);
		}
	}
	return (0);
}
