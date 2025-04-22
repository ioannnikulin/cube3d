/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:47:20 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/23 00:56:42 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		is_valid_char(char c, int *player_already_parsed);
void	find_player_pos(t_mlx *game, int i, int *col, int *row);
void	floodfill(t_mlx *game, int row, int col, int **passed);
int		is_surrounded_by_walls(t_mlx *data);
void	print_map(char **map);
int		count_map_lines(char *map);
int		validate_map(t_mlx *data, char *map);

#endif