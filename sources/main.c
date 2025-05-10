/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:01:39 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 14:13:30 by iverniho         ###   ########.fr       */
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
	mlx_key_hook(mlx.win, handle_keyboard, &mlx);
	mlx_hook(mlx.win, 17, 0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
