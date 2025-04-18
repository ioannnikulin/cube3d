/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:31:12 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/19 00:09:33 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	map_stub(t_mlx *mlx)
{
	int	i;

	ft_assign_i(&mlx->map.map_height, 8, ft_assign_i(&mlx->map.map_width, 8,
			ft_assign_i(&i, -1, 0)));
	mlx->map.map = ft_calloc_if(sizeof(char *) * mlx->map.map_height, 1);
	if (!mlx->map.map)
		return (finalize(mlx, ERR_MALLOC, 1));
	while (++ i < mlx->map.map_height)
	{
		mlx->map.map[i] = ft_calloc_if(sizeof(char) * mlx->map.map_width, 1);
		if (!mlx->map.map[i])
			return (finalize(mlx, ERR_MALLOC, 2));
		ft_memset(mlx->map.map[i], '0', mlx->map.map_width);
		mlx->map.map[i][0] = '1';
		mlx->map.map[i][mlx->map.map_width - 1] = '1';
		if (i == 0 || i == mlx->map.map_height - 1)
			ft_memset(mlx->map.map[i] + 1, '1', mlx->map.map_width - 2);
	}
	mlx->map.map[1][2] = '1';
	mlx->map.map[2][2] = '1';
	mlx->map.map[3][2] = '1';
	mlx->map.map[5][5] = '1';
	return (0);
}

static int	draw_block(t_mlx *mlx, int x, int y, t_color *clr)
{
	t_point	a;
	t_point	b;
	t_point	c;
	t_point	d;

	a = ft_point_make(x + 1, y + 1);
	b = ft_point_make(x + 1, y + mlx->map.block_size - 1);
	c = ft_point_make(x + mlx->map.block_size - 1, y + mlx->map.block_size - 1);
	d = ft_point_make(x + mlx->map.block_size - 1, y + 1);
	quadrangle(mlx, quadrangle_vertices(&a, &b, &c, &d), clr, true);
	return (0);
}

int	draw_map(t_mlx *mlx)
{
	int		r;
	int		c;
	double	cx;
	double	cy;
	t_color	clr;

	r = -1;
	while (++r < mlx->map.map_height)
	{
		ft_assign_i(&c, -1, ft_assign_d(&cy, r * mlx->map.block_size, 0));
		while (++c < mlx->map.map_width)
		{
			cx = c * mlx->map.block_size;
			clr = clr_black();
			if (mlx->map.map[r][c] == '1')
				clr = clr_white();
			draw_block(mlx, cx, cy, &clr);
		}
	}
	return (0);
}

int	world_create(t_mlx *mlx)
{
	map_stub(mlx);
	draw_map(mlx);
	mlx->player.coords.from = ft_point_make(100, 100);
	mlx->player.coords.to = ft_point_make(100, 120);
	draw_player(mlx);
	return (0);
}
