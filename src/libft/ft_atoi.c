/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:48:24 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/21 16:14:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	handle_overflow(long n, int sign)
{
	if (sign > 0 && n > INT_MAX)
		return (-1);
	if (sign < 0 && n > (long)INT_MAX + 1)
		return (0);
	return ((int)(n * sign));
}

int	ft_atoi(const char *nptr)
{
	long	n;
	int		sign;
	size_t	i;

	if (!nptr)
		return (0);
	n = 0;
	sign = 1;
	i = 0;
	while (nptr[i] && is_space(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i++] - '0');
		if (n > INT_MAX)
			return (handle_overflow(n, sign));
	}
	return ((int)(n * sign));
}
