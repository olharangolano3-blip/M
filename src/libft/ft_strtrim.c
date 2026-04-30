/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:58:55 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/25 08:07:36 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	str = NULL;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && start < end && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && end > start && ft_strchr(set, s1[end - 1]))
			end--;
		str = (char *)malloc(sizeof(char) * (end - start + 1));
		if (str)
			ft_strlcpy(str, s1 + start, end - start + 1);
	}
	return (str);
}
