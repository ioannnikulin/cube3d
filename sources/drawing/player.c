/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:27:24 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/15 11:25:05 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_player(t_mlx *mlx)
{
	int		i;
	t_color	clr;

	clr = mlx->assets.palette.yellow;
	clr.alpha = 0.5;
	circle(mlx, &mlx->player.coords.from, 3, &clr);
	i = -1;
	while (++i < MINIMAP_RAYS_COUNT)
		line(mlx, &mlx->player.minimap_rays[i].from,
			&mlx->player.minimap_rays[i].to, &clr);
}
