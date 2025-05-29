/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:06:42 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/29 17:43:26 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "drawing/drawing.h"
# include "includes.h"
# include "player_controls/player_controls.h"
# include "resources.h"
# include "world_creation/world_creation.h"
# include "parsing.h"
# include "debug.h"

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define FRAMES_BUFFER 5 // advance buffering not implemented yet,
// just looping through frames on demand for now
# define STEP_LENGTH 5
# define ROT_ANGLE_PI_DIVISOR 36
# define RAYS_COUNT 120
# define MINIMAP_RAYS_COUNT 10
# define MINIMAP_BLOCK_SIZE 64
# define BIGMAP_BLOCK_SIZE 64
# define EPSILON 1e-6
# define DEGREE 0.0174532925199432957692369076848861
# define VIEWFIELD 60
# define MIN_DISTANCE_TO_WALL 5
# define MAX_WALL_HEIGHT 500
# define BIGMAP_COL_WIDTH 8
# define MAP_TEXTURE_HEIGHT 300
# define MAP_TEXTURE_WIDTH 300

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			alpha;
}	t_color;

typedef struct s_palette
{
	t_color	black;
	t_color	white;
	t_color	red;
	t_color	dark_red;
	t_color	green;
	t_color	blue;
	t_color	yellow;
	t_color	cyan;
	t_color	magenta;
}	t_palette;

typedef struct s_img
{
	void			*img;
	int				height;
	int				width;
	char			*path;
}					t_img;

typedef struct s_assets
{
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
	t_palette	palette;
}	t_assets;

typedef struct s_plane
{
	t_color			color;
}					t_plane;

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
	int			minimap_show;
	int			is_enclosed;
}	t_map;

typedef struct s_player
{
	t_vector	coords;
	double		to_wall_ahead;
	double		to_wall_behind;
	t_gamepad	gamepad;
	t_vector	minimap_rays[MINIMAP_RAYS_COUNT];
}	t_player;

/*
 * color offsets - for different endians
 */
typedef struct s_mlx_img
{
	void			**imgs;
	char			**imgs_data;
	int				next_frame_idx;
	int				bpp;
	int				linesz;
	int				endian;
	int				red_offset;
	int				green_offset;
	int				blue_offset;
}					t_mlx_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_mlx_img		frame;
	t_assets		assets;
	t_map			map;
	t_player		player;
	int				errno;
	unsigned int	dbg;
}	t_mlx;

int		finalize(t_mlx *mlx, char *msg, int ret);
int		close_it(void *param);
void	**next_img(t_mlx *mlx);
char	**next_img_data(t_mlx *mlx);
int		world_create(t_mlx *mlx);
int		make_image(t_mlx *mlx);
int		pre(t_mlx *mlx);
void	free_img(t_mlx *mlx, t_img *img);
#endif
