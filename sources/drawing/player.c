/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:27:24 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/01 19:16:21 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_player(t_mlx *mlx)
{
	circle(mlx, &mlx->player.coords.from, 3, mlx->assets.palette.yellow);
	cast_rays(mlx);
}
