/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:30:33 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/29 19:27:18 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# define DBG_PLAYER_MOVE 1
# define DBG_FULL 1
# define DBG_NOEXIT 2
/* used to disable exit() in finalize, 
* to allow direct function calls in unit-tests
*/
# define DBG_TEXTURE_PATH 4

#endif