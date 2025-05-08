/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:47:20 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/08 15:32:44 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		is_valid_char(char c, int *player_already_parsed);
int		longest_line(char **map);
int		is_surrounded_by_walls(t_mlx *data);
void	print_map(char **map);
int		count_map_lines(char *map);
int		validate_map(t_mlx *data, char *map);
int		is_map_row_valid(char *row);
void	free_map(char **map);
void	free_exit(t_mlx *data);

#endif
