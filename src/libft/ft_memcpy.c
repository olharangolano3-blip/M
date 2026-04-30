/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:24:35 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/15 22:56:04 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*s1;
	const char	*s2;

	if ((dest == NULL || src == NULL) || n == 0)
		return (dest);
	if (dest == src)
		return (dest);
	s1 = (char *)dest;
	s2 = (const char *)src;
	while (n--)
		*s1++ = *s2++;
	return (dest);
}
