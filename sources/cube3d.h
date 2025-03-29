/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:06:42 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/29 22:43:32 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "includes.h"

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

int parse_map(char *map);

#endif