/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:22:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/11 19:47:12 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	circle(t_mlx *mlx, t_point *center, int radius, t_color clr)
{
	int		x0;
	int		y0;
	int		d;

	x0 = -1;
	y0 = radius;
	d = 3 - 2 * radius;
	while (++ x0 <= y0)
	{
		pixel(mlx, center->x + x0, center->y + y0, clr);
		pixel(mlx, center->x - x0, center->y + y0, clr);
		pixel(mlx, center->x + x0, center->y - y0, clr);
		pixel(mlx, center->x - x0, center->y - y0, clr);
		pixel(mlx, center->x + y0, center->y + x0, clr);
		pixel(mlx, center->x - y0, center->y + x0, clr);
		pixel(mlx, center->x + y0, center->y - x0, clr);
		pixel(mlx, center->x - y0, center->y - x0, clr);
		if (d < 0)
			d += 4 * x0 + 6;
		else
		{
			d += 4 * (x0 - y0) + 10;
			y0 --;
		}
	}
}