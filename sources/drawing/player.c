/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:27:24 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:42 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_player(t_mlx *mlx)
{
	t_color	clr;

	clr.r = 255;
	clr.g = 255;
	clr.b = 0;
	clr.alpha = 1;
	circle(mlx, &mlx->player.coords.from, 3, clr);
	line(mlx, &mlx->player.coords.from, &mlx->player.coords.to);
}