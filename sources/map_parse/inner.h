/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:19:21 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/29 15:43:37 by inikulin         ###   ########.fr       */
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
int		set_texture_target(t_mlx *data, char *id,
			void	***target_path_ptr, char *path);
int		parse_color_line(t_mlx *data, char *line, char **instructions);
int		parse_texture_line(t_mlx *data, char *line, char **instructions);
void	parse_instructions(t_mlx *data, char *file);
void	init_parse_data(t_mlx *data);
int		is_map_line(t_mlx *data, char *line);
void	set_direction(t_mlx *game, int to_x, int to_y);
int		is_number(char *str);
int		set_texture_target(t_mlx *data, char *id,
			void ***target_path_ptr, char *path);
void	handle_configure_error(t_mlx *data, char **parts, char *trimmed_line,
			char *error_message);
void	initialize_texture_asset(t_mlx *data, t_img *asset, char *path_str,
			void ***img_ptr_target);
int		validate_map_input(t_mlx *mlx, char **map);
int		validate_row_properties(t_mlx *mlx, char *row);
int		check_elements(t_mlx *mlx, char **map);
int		open_map_file_and_get_fd(t_mlx *data, char *file, int *total_lines_out);
char	**allocate_instructions_array(t_mlx *data, int total_lines);
void	convert_texture_to_image(t_mlx *mlx);

// free functions
void	free_passed_array(int **passed, int height);
void	free_assets(t_mlx *data);
void	find_elements_and_map_start(t_mlx *data, char **instructions,
			int *elements_found_out, int *map_start_idx_out);
void	copy_map_data(t_mlx *data, char **instructions, int map_start_index,
			int map_height);
void	free_2d_array(char **array);

#endif
