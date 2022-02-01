/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_dir_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:53:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:44:41 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool display_dir_info(enum E_LS_ARGS arg, char *current_dir)
{
	TF *currentList = NULL;
	bool error = false;
	TF *element = readAllFilesInDir(current_dir, &error);

	// Check List element
	if (!element)
	{
		if (!error)
		{
			// Last directory without file
			if (LS_ARG_containItem(E_LS_ARG_L))
				ls_case_l(NULL, current_dir, true);
			else
			{
				ls_case_none(NULL, current_dir);
			}
		}
		return (false);
	}
	else
	{
		currentList = element;
	}
	if (!current_dir || !currentList)
		return (false);

	// Switch Args
	switch (arg)
	{
	case E_LS_ARG_NONE:
	{
		ls_case_none(currentList, current_dir);
		break;
	}
	case E_LS_ARG_L:
	{
		ls_case_l(currentList, current_dir, true);
		break;
	}
	case E_LS_ARG_R:
	{
		ls_case_r(currentList, current_dir);
		break;
	}
	case E_LS_ARG_A:
	{
		display_dir_info(E_LS_ARG_NONE, current_dir);
		break;
	}
	case E_LS_ARG_LR:
	{
		// Not Used
		break;
	}
	case E_LS_ARG_T:
	{
		// Not Used
		break;
	}
	case E_LS_ARG_F:
	{
		// Not Used
		break;
	}
	case E_LS_ARG_G:
	{
		ls_case_l(currentList, current_dir, true);
		break;
	}
	}
	return (true);
}
