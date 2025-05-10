/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:47:20 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/10 20:01:13 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	print_map(char **map);
int		count_map_lines(char *map);
int		validate_map(t_mlx *data, char *map);
void	free_map(char **map);
void	free_map_exit(t_mlx **data, char *msg);
void	exit_error(char *message);

#endif
