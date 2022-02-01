/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 00:34:25 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 17:26:09 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//****************************************************************************//
//							  READ CASES - UTILS							  //
//****************************************************************************//

void display_file_color(struct stat st, enum E_FILE_TYPE eft)
{
	if (LS_ARG_containItem(E_LS_ARG_F))
		return;
	ft_putstr(st.st_mode & S_IXUSR ? GREEN BOLD : "");
	ft_putstr(eft == FT_DIR ? BLUE BOLD : eft == FT_LNK				   ? CYAN BOLD
									  : eft == FT_FIFO				   ? YELLOW
									  : eft == FT_CHR || eft == FT_BLK ? YELLOW BOLD
									  : eft == FT_SOCK				   ? MAGENTA BOLD
																	   : "");
	if (st.st_mode & S_ISUID)
	{
		ft_putstr(NORMAL);
		ft_putstr(WHITE);
		ft_putstr(BG_RED);
	}
	else if (st.st_mode & S_ISGID)
	{
		ft_putstr(NORMAL);
		ft_putstr(BLACK);
		ft_putstr(BG_YELLOW);
	}
	else if (st.st_mode & S_ISVTX)
	{
		ft_putstr(NORMAL);
		ft_putstr(WHITE);
		ft_putstr(BG_BLUE);
	}
}

void display_multi_dir_info(char *current_dir)
{
	static size_t pass = 0;
	//	printf("\t- currentdir valid: %d\n", current_dir ? 1 : 0);
	if (current_dir && get_struct_ls()->display_file_infos)
	{
		if (pass)
			ft_putstr("\n");
		else
			++pass;
		ft_putstr(current_dir);
		ft_putendl(":");
	}
}

//****************************************************************************//
//							  READ CASE - NONE 					 			  //
//****************************************************************************//

void ls_case_none(TF *list, char *current_dir)
{
	display_multi_dir_info(current_dir);
	if (list)
	{
		for (TF *tmp = list; tmp; LST_NEXT(tmp))
		{
			if (tmp->name[0] == '.' && S_ISDIR(tmp->st.st_mode) && !LS_ARG_containItem(E_LS_ARG_A))
				continue;
			display_file_color(tmp->st, tmp->type);
			ft_putstr(tmp->name);
			ft_putstr(NORMAL);
			ft_putstr(tmp->next ? "  " : "");
		}
		ft_putstr("\n");
	}
	TFfreeFiles(&list);
}

//****************************************************************************//
//							     READ CASE - L 								  //
//****************************************************************************//

void ls_case_l(TF *list, char *current_dir, bool displayTotal)
{

	display_multi_dir_info(current_dir);
	if (list)
	{
		size_t totalBlocks = 0, maxSizeSTSize = 0, maxSizeNBLinks = 0,
			   maxSizePWUID = 0, maxSizeGRGID = 0;
		bool oneFileHasACL = false;

		// Divide / 2 -> EXT4 FileSystem
		for (TF *tmp = list; tmp; LST_NEXT(tmp))
		{
			totalBlocks += ((tmp->type == FT_LNK ? tmp->ln.lst.st_blocks : tmp->st.st_blocks) / 2);
			size_t nbrTmp = 0;
			if (S_ISCHR(tmp->st.st_mode) || S_ISBLK(tmp->st.st_mode))
			{
				if ((nbrTmp = ft_nbrlen(major(tmp->st.st_rdev)) +
							  ft_nbrlen(minor(tmp->st.st_rdev)) +
							  2) > maxSizeSTSize)
					maxSizeSTSize = nbrTmp;
			}
			else
			{
				if ((nbrTmp = ft_nbrlen(tmp->st.st_size)) > maxSizeSTSize)
					maxSizeSTSize = nbrTmp;
			}
			if ((nbrTmp = ft_nbrlen(tmp->st.st_nlink)) > maxSizeNBLinks)
				maxSizeNBLinks = nbrTmp;
			if ((nbrTmp = ft_strlen(getpwuid(tmp->st.st_uid)->pw_name)) > maxSizePWUID)
				maxSizePWUID = nbrTmp;
			if ((nbrTmp = ft_strlen(getgrgid(tmp->st.st_gid)->gr_name)) > maxSizeGRGID)
				maxSizeGRGID = nbrTmp;

			// Check ACL
			char *file_path = ft_multijoin((char *[]){current_dir, tmp->name, NULL}, "/");
			if (get_file_acl(file_path) == '+')
				oneFileHasACL = true;
			free(file_path);
		}

		if (displayTotal)
		{
			ft_putstr("total ");
			ft_putnbr(totalBlocks);
			ft_putstr("\n");
		}

		for (TF *tmp = list; tmp; LST_NEXT(tmp))
		{
			char *file_path = ft_multijoin((char *[]){current_dir, tmp->name, NULL}, "/");
			display_permissions(tmp->st, file_path, oneFileHasACL);
			free(file_path);
			ft_putstr(" ");
			displayNBRFromRight(tmp->st.st_nlink, maxSizeNBLinks);
			ft_putstr(" ");
			displaySTRFromLeft(getpwuid(tmp->st.st_uid)->pw_name, maxSizePWUID);
			ft_putstr(" ");
			if (!LS_ARG_containItem(E_LS_ARG_G))
			{
				displaySTRFromLeft(getgrgid(tmp->st.st_gid)->gr_name, maxSizeGRGID);
				ft_putstr(" ");
			}

			// Display Device (Major / Minor)
			if (S_ISCHR(tmp->st.st_mode) || S_ISBLK(tmp->st.st_mode))
			{
				ft_putnbr(major(tmp->st.st_rdev));
				ft_putstr(", ");
				for (size_t i = ft_nbrlen(minor(tmp->st.st_rdev)); i < ((maxSizeSTSize)-ft_nbrlen(major(tmp->st.st_rdev)) - 2); i++)
				{
					write(1, " ", 1);
				}
				ft_putnbr(minor(tmp->st.st_rdev));
			}

			// Display File / Directory... Size
			else
			{
				displayNBRFromRight(tmp->st.st_size, maxSizeSTSize);
			}
			ft_putstr(" ");
			display_time(tmp->st.st_mtime);
			display_file_color(tmp->st, tmp->type);
			ft_putstr(tmp->name);
			ft_putstr(NORMAL);
			displayLink(tmp);
			ft_putstr(NORMAL);
			ft_putstr("\n");
		}
	}
	else
	{
		ft_putstr("total ");
		ft_putnbr(0);
		ft_putstr("\n");
	}
	TFfreeFiles(&list);
}

//****************************************************************************//
//							     READ CASE - R 								  //
//****************************************************************************//

void ls_case_r(TF *list, char *current_dir)
{
	char *dir = ft_strcpy(current_dir);
	TF *files = list;
	size_t filesLength = TFfilesLen(files);

	// First pass Arg R
	{
		display_dir_info(LS_ARG_containItem(E_LS_ARG_L) ? E_LS_ARG_L : E_LS_ARG_NONE, dir);
	}

	// For all Directories
	if (files && filesLength > 0)
	{
		for (TF *tmp = files; tmp; LST_NEXT(tmp))
		{
			if (tmp->type == FT_DIR)
			{
				if (tmp->name[0] == '.' && !LS_ARG_containItem(E_LS_ARG_A))
					continue;
				if (!ft_strcmp(tmp->name, "..") || !ft_strcmp(tmp->name, "."))
					continue;
				char *new_dir = ft_multijoin(
					(char *[]){
						dir, tmp->name, NULL},
					"/");
				new_dir = remove_doublons(new_dir, '/');
				display_dir_info(E_LS_ARG_R, new_dir);
				free(new_dir);
			}
		}
		TFfreeFiles(&files);
	}
	free(dir);
}
