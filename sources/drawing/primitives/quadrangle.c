/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:12:04 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/19 00:09:52 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../drawing.h"

t_quadrangle_vertices	quadrangle_vertices(t_point *a, t_point *b, t_point *c,
	t_point *d)
{
	t_quadrangle_vertices	vertices;

	vertices.a = a;
	vertices.b = b;
	vertices.c = c;
	vertices.d = d;
	return (vertices);
}


void	quadrangle(t_mlx *mlx, t_quadrangle_vertices vertices, t_color *clr,
		bool fill)
{
	triangle(triangle_arg(mlx, triangle_vertices(vertices.a, vertices.b,
				vertices.c), clr, fill));
	triangle(triangle_arg(mlx, triangle_vertices(vertices.a, vertices.c,
				vertices.d), clr, fill));
}