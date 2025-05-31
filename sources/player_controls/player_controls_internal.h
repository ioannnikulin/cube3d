/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:37:26 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 15:35:55 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CONTROLS_INTERNAL_H
# define PLAYER_CONTROLS_INTERNAL_H

# include "../cube3d.h"

typedef enum e_action
{
	NO,
	EXIT,
	FWD,
	BACK,
	TURN_CCW,
	TURN_CW,
	STEP_RIGHT,
	STEP_LEFT,
	MINIMAP
}	t_action;

void	side_step(t_mlx *mlx);
double	f_b_step(t_mlx *mlx, double suggest);
#endif