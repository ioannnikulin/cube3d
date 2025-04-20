/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:31:07 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:22 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_INTERNAL_H
# define LINE_INTERNAL_H
# include "../../cube3d.h"

typedef struct s_line_arg
{
	double		x0;
	double		y0;
	double		z0;
	double		clr0;
	double		x1;
	double		y1;
	double		z1;
	double		clr1;
	double		steep;
	double		dx;
	double		dy;
	double		gradient;
	int			end0x;
	int			end0y;
	int			end1x;
	int			end1y;
	double		intery;
	t_mlx		*mlx;
}	t_line_arg;

t_color	color(double clr, double alpha);
double	flr(double c);
double	fpart(double c);
double	rfpart(double c);
double	rnd(double c);
void	endpoint0(t_line_arg *arg, double x, double y);
void	endpoint1(t_line_arg *arg, double x, double y);

typedef struct s_endpoint_args
{
	double		xend;
	double		yend;
	double		xgap;
	t_color		clr;
}	t_endpoint_args;

#endif