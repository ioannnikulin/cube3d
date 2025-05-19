/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:01:39 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/19 06:22:37 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		return (finalize(NULL, USAGE, 1));
	if (!validate_map(&mlx, argv[1]))
		return (1);
	if (pre(&mlx))
		return (2);
	world_create(&mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win, 2, 1, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 2, key_released, &mlx);
	mlx_hook(mlx.win, 17, 0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
