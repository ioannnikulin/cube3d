/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:54:12 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/11 19:56:33 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	draw_map(t_mlx *mlx)
{
	int		row;
	int		col;
	t_color	clr;

	row = -1;
	while (++ row < mlx->map.map_height)
	{
		col = -1;
		while (++ col < mlx->map.map_width)
		{
			if (mlx->map.map[row][col] == '1')

		}
	}
	return (0);
}