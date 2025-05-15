/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_endpoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/15 11:31:45 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_internal.h"

static t_endpoint_args	make_ea(double xend, double yend, double xgap,
							t_color *clr)
{
	t_endpoint_args	r;

	r.xend = xend;
	r.yend = yend;
	r.xgap = xgap;
	r.clr = *clr;
	return (r);
}

void	endpoint0(t_line_arg *arg, double x, double y)
{
	t_endpoint_args	ea;

	ea = make_ea(rnd(x), y + arg->gradient * (rnd(x) - x),
			rfpart(x + 0.5), arg->clr);
	arg->end0x = ea.xend;
	arg->end0y = flr(ea.yend);
	if (arg->steep)
	{
		ea.clr = prealpha(&ea.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end0y, arg->end0x, &ea.clr);
		arg->clr0 = ea.clr;
		ea.clr = prealpha(&ea.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end0y + 1, arg->end0x, &ea.clr);
	}
	else
	{
		ea.clr = prealpha(&ea.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end0x, arg->end0y, &ea.clr);
		arg->clr0 = ea.clr;
		ea.clr = prealpha(&ea.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end0x, arg->end0y + 1, &ea.clr);
	}
	arg->intery = ea.yend + arg->gradient;
}

void	endpoint1(t_line_arg *arg, double x, double y)
{
	t_endpoint_args	ea;

	ea = make_ea(rnd(x), y + arg->gradient * (rnd(x) - x),
			fpart(x + 0.5), arg->clr);
	arg->end1x = ea.xend;
	arg->end1y = flr(ea.yend);
	if (arg->steep)
	{
		ea.clr = prealpha(&ea.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end1y, arg->end1x, &ea.clr);
		arg->clr1 = ea.clr;
		ea.clr = prealpha(&ea.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end1y + 1, arg->end1x, &ea.clr);
	}
	else
	{
		ea.clr = prealpha(&ea.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end1x, arg->end1y, &ea.clr);
		arg->clr1 = ea.clr;
		ea.clr = prealpha(&ea.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->mlx, arg->end1x, arg->end1y + 1, &ea.clr);
	}
}
