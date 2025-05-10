/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:19:21 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/10 18:26:01 by iverniho         ###   ########.fr       */
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
int		is_valid_char(char c, int *player_already_parsed);
int		is_surrounded_by_walls(t_mlx *data);

#endif
