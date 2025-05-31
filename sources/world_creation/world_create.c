/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:31:12 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 19:36:30 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	draw_block(t_mlx *mlx, int x, int y, t_color *clr)
{
	t_point	a;
	t_point	b;
	t_point	c;
	t_point	d;

	a = ft_point_make(x + 1, y + 1);
	b = ft_point_make(x + 1, y + MINIMAP_BLOCK_SIZE - 1);
	c = ft_point_make(x + MINIMAP_BLOCK_SIZE - 1, y + MINIMAP_BLOCK_SIZE - 1);
	d = ft_point_make(x + MINIMAP_BLOCK_SIZE - 1, y + 1);
	quadrangle(mlx, quadrangle_vertices(&a, &b, &c, &d), clr, MODE_FILL);
	return (0);
}

int	draw_minimap(t_mlx *mlx)
{
	int		r;
	int		c;
	double	cx;
	double	cy;
	t_color	clr;

	r = -1;
	clr = mlx->assets.palette.white;
	clr.alpha = 0.5;
	while (++r < mlx->map.map_height)
	{
		ft_assign_i(&c, -1, ft_assign_d(&cy, r * MINIMAP_BLOCK_SIZE, 0));
		while (++c < mlx->map.map_width)
		{
			cx = c * MINIMAP_BLOCK_SIZE;
			if (mlx->map.map[r][c] == '1')
				draw_block(mlx, cx, cy, &clr);
		}
	}
	return (0);
}

static void	fill_textures(t_mlx *mlx)
{
	mlx->assets.wall_north.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_north.path, &mlx->assets.wall_north.width,
			&mlx->assets.wall_north.height);
	mlx->assets.wall_south.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_south.path, &mlx->assets.wall_south.width,
			&mlx->assets.wall_south.height);
	mlx->assets.wall_west.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_west.path, &mlx->assets.wall_west.width,
			&mlx->assets.wall_west.height);
	mlx->assets.wall_east.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_east.path, &mlx->assets.wall_east.width,
			&mlx->assets.wall_east.height);
}

int	world_create(t_mlx *mlx)
{
	fill_textures(mlx);
	return (0);
}
