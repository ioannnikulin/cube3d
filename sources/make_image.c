/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:14:29 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 15:40:34 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	make_image(t_mlx *mlx)
{
	char	**nimg_data;
	void	**nimg;

	if (*next_img(mlx))
		mlx_destroy_image(mlx->mlx, *next_img(mlx));
	nimg = next_img(mlx);
	*nimg = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!*next_img(mlx))
		return (finalize(mlx, ERR_MLX_IMG, 4));
	nimg_data = next_img_data(mlx);
	*nimg_data = mlx_get_data_addr(*next_img(mlx), &(mlx->frame.bpp),
			&(mlx->frame.linesz), &(mlx->frame.endian));
	if (!*next_img_data(mlx))
		return (finalize(mlx, ERR_MLX_GETADDR, 5));
	return (0);
}
