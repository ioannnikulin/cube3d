/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:09:48 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/27 20:59:26 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	render_frame(t_mlx *mlx)
{
	if (make_image(mlx))
		return (3);
	cast_rays(mlx);
	if (mlx->map.minimap_show)
	{
		draw_minimap(mlx);
		draw_player(mlx);
	}
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_put_image_to_window(mlx->mlx, mlx->win, *next_img(mlx), 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->assets.wall_west.img, 0, 0);
	mlx->frame.next_frame_idx = (mlx->frame.next_frame_idx + 1) % FRAMES_BUFFER;
	return (0);
}
