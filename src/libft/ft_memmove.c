/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:18:53 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/15 22:58:03 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*s1;
	const char	*s2;

	if (!dest || !src)
		return (NULL);
	if (n == 0)
		return (dest);
	s1 = (char *)dest;
	s2 = (const char *)src;
	if (s1 < s2)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			s1[n] = s2[n];
	}
	return (dest);
}
