/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp_segfault_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:56:03 by inikulin          #+#    #+#             */
/*   Updated: 2023/11/17 14:18:13 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	char *s = 0;
	char *d = calloc(10, 1);
	if (!d)
		return (bad_alloc(1));
	ft_memcmp(d, s, 1);
	return (segfault_expected(1));
}
