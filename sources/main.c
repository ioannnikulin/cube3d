/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:01:39 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/29 16:07:09 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifdef FT_CALLOC_IF_TRAPPED
/*
* fail mallocs one by one
* to check that the program exits correctly without leaks every time
*/

void	trap(void)
{
	int		fd;
	char	*line;

	fd = open("trap.tgt", O_RDONLY);
	if (fd < 0)
	{
		ft_calloc_if_trap_setup(0);
		return ;
	}
	line = get_next_line(fd);
	if (!line)
		finalize(NULL, ERR_TRAP_MALLOC, 1);
	ft_calloc_if_trap_setup(ft_atoi(line));
	free(line);
	close(fd);
}

void	untrap(void)
{
	ft_calloc_if_trap_count();
}

#else

void	trap(void)
{
}

void	untrap(void)
{
}

#endif

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	trap();
	if (argc != 2)
		return (finalize(NULL, USAGE, 1));
	if (pre(&mlx))
		return (2);
	if (!validate_map(&mlx, argv[1]))
		return (1);
	world_create(&mlx);
	render_frame(&mlx);
	mlx_hook(mlx.win, 2, 1, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 2, key_released, &mlx);
	mlx_hook(mlx.win, 17, 0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	untrap();
	return (0);
}
