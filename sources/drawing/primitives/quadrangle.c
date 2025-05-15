/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:12:04 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/15 10:27:05 by inikulin         ###   ########.fr       */
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
		int mode)
{
	if (mode & MODE_FILL)
	{
		triangle(triangle_arg(mlx, triangle_vertices(vertices.a, vertices.b,
					vertices.c), clr, mode & MODE_FILL));
		triangle(triangle_arg(mlx, triangle_vertices(vertices.a, vertices.c,
					vertices.d), clr, mode & MODE_FILL));
	}
	if (mode & MODE_SIDES)
	{
		line(mlx, vertices.a, vertices.b, clr);
		line(mlx, vertices.b, vertices.c, clr);
		line(mlx, vertices.c, vertices.d, clr);
		line(mlx, vertices.d, vertices.a, clr);
	}
}
