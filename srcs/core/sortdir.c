/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:03:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:14:34 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//****************************************************************************//
//								REVERSE LINKED LIST							  //
//****************************************************************************//

static TF *reverse_linked_list(TF **lst)
{
	if (!lst)
		return (NULL);

	TF *prev = NULL;
	TF *current = *lst;
	TF *next = NULL;

	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*lst = prev;
	return (*lst);
}

//****************************************************************************//
//								SORT ALPHABETICALY							  //
//****************************************************************************//

static TF *sortInsertAlphabeticaly(TF *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_alphabeticalcmp(lst->name, lst->next->name) > 0)
		lst = TFswap(lst, lst->next);
	lst->next = sortInsertAlphabeticaly(lst->next);
	if (lst->next && ft_alphabeticalcmp(lst->name, lst->next->name) > 0)
	{
		lst = TFswap(lst, lst->next);
		lst->next = sortInsertAlphabeticaly(lst->next);
	}
	return (lst);
}

//****************************************************************************//
//						      SORT BY MODIFICATION TIME				 		  //
//****************************************************************************//

static TF *sortFileByModificationTime(TF *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->st.st_mtim.tv_sec < lst->next->st.st_mtim.tv_sec))
		lst = TFswap(lst, lst->next);
	else if (lst->next && lst->st.st_mtim.tv_sec == lst->next->st.st_mtim.tv_sec)
		if (lst->next && (lst->st.st_mtim.tv_nsec < lst->next->st.st_mtim.tv_nsec))
			lst = TFswap(lst, lst->next);
	lst->next = sortFileByModificationTime(lst->next);
	if (lst->next && (lst->st.st_mtim.tv_sec < lst->next->st.st_mtim.tv_sec))
	{
		lst = TFswap(lst, lst->next);
		lst->next = sortFileByModificationTime(lst->next);
	}
	else if (lst->next && lst->st.st_mtim.tv_sec == lst->next->st.st_mtim.tv_sec)
	{
		if (lst->next && (lst->st.st_mtim.tv_nsec < lst->next->st.st_mtim.tv_nsec))
		{
			lst = TFswap(lst, lst->next);
			lst->next = sortFileByModificationTime(lst->next);
		}
	}
	return (lst);
}

//****************************************************************************//
//								MAIN SORT FUNCTIONS							  //
//****************************************************************************//

void *sortFiles(TF **files)
{
	// Case to do not sort
	if (LS_ARG_containItem(E_LS_ARG_F))
		return (NNULL_PTR);
	if (!(*files = sortInsertAlphabeticaly(*files)))
		return (NULL);
	if (LS_ARG_containItem(E_LS_ARG_T))
	{
		if (!(*files = sortFileByModificationTime(*files)))
			return (NULL);
	}
	if (LS_ARG_containItem(E_LS_ARG_LR))
	{
		if (!(*files = reverse_linked_list(files)))
			return (NULL);
	}
	return (NNULL_PTR);
}
