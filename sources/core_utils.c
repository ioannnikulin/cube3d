/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:10:18 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/10 18:25:07 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	**next_img(t_mlx *mlx)
{
	return (&(mlx->frame.imgs[mlx->frame.next_frame_idx]));
}

char	**next_img_data(t_mlx *mlx)
{
	return (&(mlx->frame.imgs_data[mlx->frame.next_frame_idx]));
}
