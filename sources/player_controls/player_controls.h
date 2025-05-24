/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:37:26 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/11 14:35:55 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CONTROLS_H
# define PLAYER_CONTROLS_H
# include "../cube3d.h"

typedef struct s_gamepad
{
	int	fwd_pressed;
	int	back_pressed;
	int	turn_ccw_pressed;
	int	turn_cw_pressed;
}	t_gamepad;

int		key_pressed(int keycode, void *param);
int		key_released(int keycode, void *param);
double	rot_angle(void);
#endif