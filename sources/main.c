/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:01:39 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/24 16:53:16 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	usage(void)
{
	printf("Error\n");
	printf("Usage: cube3D filename.cub\n\tfilename.cub - file containing:\n");
	printf("\t- NO ./path_to_the_north_texture\n");
	printf("\t- SO ./path_to_the_south_texture\n");
	printf("\t- WE ./path_to_the_west_texture\n");
	printf("\t- EA ./path_to_the_east_texture\n");
	printf("\t(all should be valid paths to xpm files)\n");
	printf("\t- F 200,100,0\n");
	printf("\t- C 225,30,0\n");
	printf("\t(color components 0-255 each, F for floor, C for ceiling)\n");
	printf("\t(all the parts above can follow in any order, \
also with empty lines)\n");
	printf("\t- [A map of 0, 1 (walls, enclosed), one letter of [NSEW] \
depicting player's spawn position and face direction]\n");
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (usage());
	return (0);
}