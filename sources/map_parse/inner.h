/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:19:21 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/25 17:29:32 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INNER_H
# define INNER_H

# include "../cube3d.h"

int		is_row_valid(char *row);
int		is_map_row_valid(char *row);
int		longest_line(char **map);
int		is_map_valid(int map_width, int valid_elements);
int		is_valid_char(t_mlx *data, char c, int *player_already_parsed);
int		is_surrounded_by_walls(t_mlx *data);
int     set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path);
int		parse_color_line(t_mlx *data, char *line);
int		parse_texture_line(t_mlx *data, char *line);
void	parse_instructions(t_mlx *data, char *file);
void	init_parse_data(t_mlx *data);
int     is_map_line(char *line);
int     process_line(t_mlx *data, char *line, int *elements_found,
		int *map_start_index, int current_line_idx);
void	set_direction(t_mlx *game, int to_x, int to_y);
int		is_number(char *str);
int		set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path);
void	handle_configure_error(char **parts, char *trimmed_line, \
									const char *error_message);
void	initialize_texture_asset(t_img *asset, char *path_str, \
									void ***img_ptr_target);
// free functions
void	free_passed_array(int **passed, int height);
void	free_color_parts(char **parts);
void	free_instructions(char **instructions, int count);
void	free_assets(t_mlx *data);
void	free_map_exit(t_mlx **data, char *msg);
void	free_texture_parts(char **parts);
void	find_elements_and_map_start(t_mlx *data, char **instructions,
		int *elements_found_out, int *map_start_idx_out);
void	copy_map_data(t_mlx *data, char **instructions, int map_start_index,
		int map_height);



#endif
