/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:37:26 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/11 15:45:47 by inikulin         ###   ########.fr       */
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
	MINIMAP
}	t_action;

#endif