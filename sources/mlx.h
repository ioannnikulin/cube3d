/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:06:42 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/24 16:32:15 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H
# include "libft.h"

typedef struct s_img
{
	void	*img;
	int		height;
	int		width;
}	t_img;

typedef struct s_assets
{
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
}	t_assets;

typedef struct s_plane
{
	t_color		color;
}	t_plane;

typedef struct s_map
{
	int			map_height;
	int			map_width;
	char		**map;
	t_plane		*floor;
	t_plane		*ceiling;
}	t_map;

typedef struct s_player
{
	t_vector	*coords;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_assets	*assets;
	t_map		*map;
	t_player	*player;
}	t_mlx;

#endif