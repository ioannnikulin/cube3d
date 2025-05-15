/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_factories.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:22:00 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/15 09:49:11 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../drawing.h"

t_triangle_vertices	triangle_vertices(t_point *a, t_point *b, t_point *c)
{
	t_triangle_vertices	vertices;

	vertices.a = a;
	vertices.b = b;
	vertices.c = c;
	return (vertices);
}

static void	sort_vertices_y(t_triangle_vertices *vertices)
{
	if (vertices->a->y > vertices->b->y)
		ft_swap_pts(&(vertices->a), &(vertices->b));
	if (vertices->a->y > vertices->c->y)
		ft_swap_pts(&(vertices->a), &(vertices->c));
	if (vertices->b->y > vertices->c->y)
		ft_swap_pts(&(vertices->b), &(vertices->c));
}

// sorted_vertices = vertices can cause problems
t_triangle_arg	triangle_arg(t_mlx *mlx, t_triangle_vertices vertices,
						t_color *color, int mode)
{
	t_triangle_arg	arg;

	arg.mlx = mlx;
	arg.vertices = vertices;
	arg.sorted_vertices = vertices;
	sort_vertices_y(&arg.sorted_vertices);
	arg.color = color;
	arg.mode = mode;
	return (arg);
}
