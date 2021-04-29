/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 10:04:16 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:41:06 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (0);
	ft_memcpy(s3, s1, ft_strlen(s1));
	ft_strlcpy(&s3[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (s3);
}
