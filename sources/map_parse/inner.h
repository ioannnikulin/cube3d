/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:19:21 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/24 15:56:29 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INNER_H
# define INNER_H

# include "../cube3d.h"

int		is_row_valid(char *row);
int		check_extension(char *map);
int		is_map_row_valid(char *row);
int		longest_line(char **map);
int		is_map_valid(int map_width, int valid_elements);
int		is_valid_char(t_mlx *data, char c, int *player_already_parsed);
int		is_surrounded_by_walls(t_mlx *data);
int     set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path);
int		parse_color_line(t_mlx *data, char *line);
int		parse_texture_line(t_mlx *data, char *line);
void	parse_instructions(t_mlx *data, char *file);
void	free_assets(t_mlx *data);
void	init_parse_data(t_mlx *data);
int     is_map_line(char *line);
void	free_instructions(char **instructions, int count);
int     process_line(t_mlx *data, char *line, int *elements_found,
		int *map_start_index, int current_line_idx);



#endif
