/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:22:48 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/20 16:21:57 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	if (!*little)
		return ((char *)big);
	if (len == 0 || !little || !big)
		return (NULL);
	i = 0;
	len_little = ft_strlen(little);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while ((j < len_little) && (i + j < len)
				&& (big[i + j] == little[j]))
				j++;
			if (j == len_little)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
