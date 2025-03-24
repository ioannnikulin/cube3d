/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:16:17 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/24 16:30:31 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# define LLTOA_BASE_MAX_LEN 65
# include "sources/symbols/symbols.h"
# include "sources/numbers/numbers.h"
# include "sources/strings/strings.h"
# include "sources/memory/memory.h"
# include "sources/lists/list.h"
# include "sources/dlists/dlist.h"
# include "sources/map/mapss/mapss.h"
# include "sources/tree/tree.h"
# include "sources/control_flow/control_flow.h"
# include "sources/printf/print.h"
# include "sources/graphics/graphics.h"

char	*get_next_line(int fd);
#endif
