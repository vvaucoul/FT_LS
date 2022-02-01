/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:50:47 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 16:23:49 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	if (!(parse(argc, argv)))
	{
		freeProgramm();
		return (1);
	}
	if (get_struct_ls()->s_files)
		diplay_files_selected();
	if (get_struct_ls()->s_dir)
	{
		char **initDir = copy_array(get_struct_ls()->s_dir);
		for (size_t i = 0; initDir[i]; i++)
		{
			char *current_dir = initDir[i];
			readdir_rec(current_dir);
		}
		free_array(initDir);
	}
	freeProgramm();
	return (0);
}