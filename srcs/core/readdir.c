/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:55:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:52:04 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

TF *readAllFilesInDir(char *path, bool *error)
{
	TF *list = NULL;
	DIR *dir = NULL;
	char *ptr = NULL;
	struct dirent *rp;

	if (!(dir = opendir(path)))
	{
		ptr = ft_multijoin((char *[]){
							   "ls: impossible d'ouvrir le répertoire '",
							   path,
							   "': ",
							   strerror(errno),
							   NULL},
						   "");
		display_error_to_free(ptr, true);
		*error = true;
		return (NULL);
	}
	while ((rp = readdir(dir)))
	{
		if (rp->d_name[0] == '.' && !LS_ARG_containItem(E_LS_ARG_A))
			continue;
		TFaddDirentFile(&list, rp, path);
	}
	if (dir)
		closedir(dir);
	if (!(sortFiles(&list)))
		return (NULL);
	return (list);
}

void readdir_rec(char *path)
{
	if (LS_ARG_containItem(E_LS_ARG_R))
		display_dir_info(E_LS_ARG_R, path);
	else if (LS_ARG_containItem(E_LS_ARG_L))
		display_dir_info(E_LS_ARG_L, path);
	else
		display_dir_info(E_LS_ARG_NONE, path);
}
