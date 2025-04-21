/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:14:29 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/20 17:24:21 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	make_image(t_mlx *mlx)
{
	if (*next_img(mlx))
		mlx_destroy_image(mlx->mlx, *next_img(mlx));
	*next_img(mlx) = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!*next_img(mlx))
		return (finalize(mlx, ERR_MLX_IMG, 4));
	*next_img_data(mlx) = mlx_get_data_addr(*next_img(mlx), &(mlx->frame.bpp),
		&(mlx->frame.linesz), &(mlx->frame.endian));
	if (!*next_img_data(mlx))
		return (finalize(mlx, ERR_MLX_GETADDR, 5));
	return (0);
}
