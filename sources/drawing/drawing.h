/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:20 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/23 22:37:38 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "../cube3d.h"
# include "../includes.h"

typedef struct s_mlx	t_mlx;
typedef struct s_color	t_color;

typedef struct s_triangle_vertices
{
	t_point				*a;
	t_point				*b;
	t_point				*c;
}						t_triangle_vertices;

typedef struct s_quadrangle_vertices
{
	t_point				*a;
	t_point				*b;
	t_point				*c;
	t_point				*d;
}						t_quadrangle_vertices;

typedef struct s_triangle_arg
{
	t_mlx				*mlx;
	t_triangle_vertices	vertices;
	t_triangle_vertices	sorted_vertices;
	t_color				*color;
	bool				fill;
}						t_triangle_arg;

void					line(t_mlx *s, t_point *f, t_point *t);
void					circle(t_mlx *mlx, t_point *center, int radius,
							t_color clr);
void					pixel(t_mlx *mlx, int x, int y, t_color clr);
void					ray(t_mlx *mlx, t_point *from, t_point *to);

void					draw_player(t_mlx *mlx);
// state do_sort true by default; false is for internal usage
t_triangle_vertices		triangle_vertices(t_point *a, t_point *b, t_point *c);
t_triangle_arg			triangle_arg(t_mlx *mlx, t_triangle_vertices vertices,
							t_color *color, int fill);
int						triangle(t_triangle_arg arg);
t_quadrangle_vertices	quadrangle_vertices(t_point *a, t_point *b, t_point *c,
							t_point *d);
void					quadrangle(t_mlx *mlx, t_quadrangle_vertices vertices,
							t_color *clr, bool fill);
t_color					clr_black(void);
t_color					clr_white(void);
#endif