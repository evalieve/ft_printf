/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 09:35:22 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:40:22 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

static int	ft_start(char const *s, char c, int words)
{
	int	start;

	start = 0;
	if (s[start] != c && words == 1)
		return (start);
	start++;
	while (s[start] && words > 0)
	{
		if (s[start] != c && words == 1)
		{
			words--;
			start--;
		}
		if (s[start] == c && s[start - 1] != c)
			words--;
		start++;
	}
	return (start);
}

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	free_rest(char **str, int index)
{
	while (!str[index])
	{
		free(str[index]);
		index++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;
	int		len;
	int		start;

	if (!s)
		return (0);
	words = ft_words(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (0);
	str[words] = 0;
	while (words > 0)
	{
		start = ft_start(s, c, words);
		len = ft_wordlen(s, c, start);
		str[words - 1] = ft_substr(s, start, len);
		if (!str[words - 1])
		{
			free_rest(str, words);
			return (0);
		}
		words--;
	}
	return (str);
}
