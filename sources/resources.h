/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:27:25 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/23 19:10:59 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCES_H
# define RESOURCES_H

# define USAGE "Usage: cube3D filename.cub\n\tfilename.cub - file containing:\n\
\t- NO ./path_to_the_north_texture\n\
\t- SO ./path_to_the_south_texture\n\
\t- WE ./path_to_the_west_texture\n\
\t- EA ./path_to_the_east_texture\n\
\t(all should be valid paths to xpm files)\n\n\
\t- F 200,100,0\n\
\t- C 225,30,0\n\
\t(color components 0-255 each, F for floor, C for ceiling)\n\
\t(all the parts above can follow in any order, also with empty lines)\n\n\
\t- [A map of 0, 1 (walls, enclosed), one letter of [NSEW] \
depicting player's spawn position and face direction]\n"
# define ERROR "Error\n"
# define ERR_MALLOC "Error\nFailed to allocate memory\n"
# define ERR_MLX_INIT "Error\nFailed to initialize mlx\n"
# define ERR_MLX_IMG "Error\nFailed to create image\n"
# define ERR_MLX_WIN "Error\nFailed to create window\n"
# define ERR_MLX_GETADDR "Error\nFailed to allocate frame memory\n"
# define ERR_MALLOC_MAP "Error\nFailed to allocate map memory\n"
# define MSG_EXIT "Exiting normally\n"
# define ERR_MAP_EXT "Error\nInvalid map extension\n"
# define ERR_MAP_OPEN "Error\nFailed to open map file\n"
# define ERR_NO_PLAYER "Error\nNo player found\n"
# define ERR_MAP_ENCLOSED "Error\nMap is not enclosed by walls\n"
# define ERR_MAP_EMPTY_ROW "Error\nEmpty row in a map\n"
# define ERR_PLAYERS_NUMBER "Error\nInvalid number of players\n"
# define ERR_INVALID_CHAR "Error\nInvalid character in map\n"
# define WINDOW_TITLE "Cube3D"

#endif
