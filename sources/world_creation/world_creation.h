/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_creation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:33:16 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/23 23:29:28 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_CREATION_H
# define WORLD_CREATION_H
# include "../cube3d.h"

typedef struct s_mlx	t_mlx;

int						world_create(t_mlx *mlx);
int						draw_map(t_mlx *mlx);
#endif