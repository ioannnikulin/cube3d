/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:44:16 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/01 14:35:47 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"
#include "../drawing.h"

void	ray(t_mlx *mlx, t_point *from, t_point *to, t_color *clr)
{
	double	x;
	double	y;
	double	t;
	t_point	end;

	x = to->x - from->x;
	y = to->y - from->y;
	t = sqrt(x * x + y * y);
	x /= t;
	y /= t;
	if (x != 0)
		t = ft_if_d(x > 0, (WINDOW_WIDTH - from->x) / x, -from->x / x);
	else
		t = ft_if_d(y > 0, (WINDOW_HEIGHT - from->y) / y, -from->y / y);
	end.x = from->x + x * t;
	end.y = from->y + y * t;
	line(mlx, from, &end, clr);
}
