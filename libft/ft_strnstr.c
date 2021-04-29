/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 15:30:38 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:42:48 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_compare(const char *haystack, const char *needle, size_t len,
						int j)
{
	size_t	i;
	int		m;
	int		k;

	i = 0;
	k = 0;
	m = j;
	while (i < len && haystack[i])
	{
		while (haystack[i + k] == needle[k] && (i + k) < len)
		{
			m--;
			if (m == 0)
				return ((char *)haystack + i);
			k++;
		}
		m = j;
		k = 0;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	char	*result;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	i = ft_strlen(needle);
	result = ft_compare(haystack, needle, len, i);
	return (result);
}
