/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:06:42 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/10 17:41:07 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "includes.h"
# include "resources.h"
# include "drawing/drawing.h"
# include "player_controls/player_controls.h"

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

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

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
	double	alpha;
	double	clr;
}	t_color;

typedef struct s_plane
{
	t_color		color;
}	t_plane;

/*
 * zmin and zmax are leftovers from fdf, don't know if we still need them
 * keeping as a stub
 */
typedef struct s_map
{
	int			map_height;
	int			map_width;
	char		**map;
	t_plane		floor;
	t_plane		ceiling;
	double		zmin;
	double		zmax;
}	t_map;

typedef struct s_player
{
	t_vector	coords;
}	t_player;

# define FRAMES_BUFFER 5

/*
 * color offsets - for different endians
 */
typedef struct s_mlx_img
{
	void	**imgs;
	char	**imgs_data;
	int		next_frame_idx;
	int		bpp;
	int		linesz;
	int		endian;
	int		red_offset;
	int		green_offset;
	int		blue_offset;
}	t_mlx_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_mlx_img	frame;
	t_assets	assets;
	t_map		map;
	t_player	player;
	int			errno;
}	t_mlx;

int		finalize(t_mlx *mlx, char *msg, int ret);
void	**next_img(t_mlx *mlx);
char	**next_img_data(t_mlx *mlx);
#endif