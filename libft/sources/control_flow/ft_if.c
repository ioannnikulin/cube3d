/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:29 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/20 17:46:20 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_if_i(int choice, int a, int b)
{
	if (choice)
		return (a);
	return (b);
}

double	ft_if_d(int choice, double a, double b)
{
	if (choice)
		return (a);
	return (b);
}

char	ft_if_c(int choice, char a, char b)
{
	if (choice)
		return (a);
	return (b);
}

char	*ft_if_s(int choice, char *a, char *b)
{
	if (choice)
		return (a);
	return (b);
}
