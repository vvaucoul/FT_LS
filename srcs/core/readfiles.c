/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 00:26:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 17:12:32 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void set_file_type(struct stat st, enum E_FILE_TYPE *type)
{
	if (S_ISDIR(st.st_mode))
		*type = FT_DIR;
	else if (S_ISREG(st.st_mode))
		*type = FT_REG;
	else if (S_ISCHR(st.st_mode))
		*type = FT_CHR;
	else if (S_ISBLK(st.st_mode))
		*type = FT_BLK;
	else if (S_ISFIFO(st.st_mode))
		*type = FT_FIFO;
	else if (S_ISLNK(st.st_mode))
		*type = FT_LNK;
	else if (S_ISSOCK(st.st_mode))
		*type = FT_SOCK;
	else
		*type = FT_UNKNOWN;
}

static bool add_files_selected(TF **list)
{
	TF newFile;
	char **files = get_struct_ls()->s_files;
	struct stat st;
	struct stat lst;

	if (!files)
		return (true);
	for (size_t i = 0; files[i]; i++)
	{
		newFile.name = files[i];
		newFile.filePath = files[i];
		newFile.directory = files[i];

		if ((stat(newFile.name, &st)) == -1)
			return (false);
		newFile.st = st;
		if ((lstat(newFile.name, &lst)) != -1)
		{
			bool isLink = S_ISLNK(lst.st_mode);

			if (isLink)
			{
				newFile.type = FT_LNK;
				newFile.ln.lst = lst;
				newFile.st = lst;

				// Read LNK Buffer
				{
					size_t buffSize = newFile.ln.lst.st_size == 0 ? PATH_MAX : newFile.ln.lst.st_size + 1;
					int nBytes = 0;
					if (!(newFile.ln.lnk_buffer = ft_calloc(sizeof(char), buffSize)))
					{
						perror("malloc");
						return (false);
					}
					if ((nBytes = readlink(newFile.name, newFile.ln.lnk_buffer, buffSize)) == -1)
						return (false);
					if (nBytes == (int)buffSize)
					{
						display_error("Returned buffer may have been truncated");
						return (false);
					}
				}
			}
			else
			{
				newFile.ln = (t_link){};
				set_file_type(newFile.st, &newFile.type);
			}
		}
		else
		{
			newFile.ln = (t_link){};
			set_file_type(newFile.st, &newFile.type);
		}
		newFile.next = NULL;
		TFaddFile(list, newFile);
	}
	return (true);
}

bool diplay_files_selected()
{
	TF *list = NULL;

	if (!get_struct_ls()->s_files)
		return (true);
	if (!(add_files_selected(&list)))
		return (false);

	if (LS_ARG_containItem(E_LS_ARG_L))
		ls_case_l(list, NULL, false);
	else
		ls_case_none(list, NULL);
	if (get_struct_ls()->s_dir)
		ft_putstr("\n");
	return (true);
}
