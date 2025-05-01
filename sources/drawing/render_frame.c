/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:09:48 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/01 19:03:24 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	render_frame(t_mlx *mlx)
{
	if (make_image(mlx))
		return (3);
	draw_map(mlx);
	draw_player(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, *next_img(mlx), 0, 0);
	mlx->frame.next_frame_idx = (mlx->frame.next_frame_idx + 1) % FRAMES_BUFFER;
	return (0);
}
