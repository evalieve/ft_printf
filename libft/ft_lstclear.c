/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/05 10:32:39 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:27:44 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*after;

	if (!*lst || !lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		after = temp;
		temp = temp->next;
		ft_lstdelone(after, del);
	}
	*lst = NULL;
}
