/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 00:00:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:56:30 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

// Fix symbolic link with or without / & -l
static bool fix_args_symbolic()
{
	if (!get_struct_ls()->s_dir)
		return (false);
	for (size_t i = 0; get_struct_ls()->s_dir[i]; i++)
	{
		char *element = get_struct_ls()->s_dir[i];
		struct stat st;
		if ((lstat(element, &st)) == -1)
			return (false);
		if (S_ISLNK(st.st_mode) && element[ft_strlen(element) - 1] != '/' && LS_ARG_containItem(E_LS_ARG_L))
		{
			get_struct_ls()->s_files = append_array(get_struct_ls()->s_files, element);
			get_struct_ls()->s_dir = remove_array_element(get_struct_ls()->s_dir, element);
			if (!get_struct_ls()->s_dir)
				break;
			else
				continue;
		}
	}
	return (true);
}

static bool check_part_is_file(char *str)
{
	if (isFile(str))
	{
		get_struct_ls()->s_files = append_array(get_struct_ls()->s_files, str);
		return (true);
	}
	else
		return (false);
}

static bool check_part_is_dir(char *str)
{
	DIR *dir;

	if (!(dir = opendir(str)))
	{
		closedir(dir);
		return (false);
	}
	else
	{
		closedir(dir);
		get_struct_ls()->s_dir = append_array(get_struct_ls()->s_dir, str);
		return (true);
	}
	return (true);
}
static bool check_part_args_validity(char *str, size_t *invalidIndex)
{
	size_t i = 1;

	if (str[0] != '-')
		return (false);
	if ((str[0] == '-' && ft_strlen(str) <= 1))
		return (false);
	for (; str[i]; i++)
	{
		if (char_contain_one_of((str[i]), LS_ARGS))
		{
			// Add Args
			if (str[i] == 'f')
			{
				if (LS_ARG_containItem(E_LS_ARG_L))
					remove_all_args_in_str(E_LS_ARG_L);
				append_LS_ARG(convert_char_to_ls_args('a'));
			}
			else if (str[i] == 'g')
				append_LS_ARG(convert_char_to_ls_args('l'));
			append_LS_ARG(convert_char_to_ls_args(str[i]));
			continue;
		}
		else
		{
			*invalidIndex = i;
			return (false);
		}
	}
	return (true);
}

static void resetValidParts(bool *isValidArg, bool *isValidDir, bool *isValidFile)
{
	*isValidArg = true;
	*isValidDir = true;
	*isValidFile = true;
}

bool check_args_validity(size_t argc, char **argv)
{
	bool isValidArg = true, isValidDir = true, isValidFile = true;

	for (size_t i = 1; i < (argc); i++)
	{
		size_t invalidIndex = 0;

		if (ft_strlen(argv[i]) > PATH_MAX)
		{
			display_error("ft_ls : nom de fichier trop long");
			return (false);
		}

		// Check Args
		isValidArg = check_part_args_validity(argv[i], &invalidIndex);
		isValidDir = check_part_is_dir(argv[i]);
		isValidFile = check_part_is_file(argv[i]);

		if (isValidArg || (isValidDir || isValidFile))
			continue;

		if (!isValidArg && (argv[i][0] == '-'))
		{
			display_error_to_free(array_to_str((char *[]){
									  "ft_ls : option invalide -- '",
									  (char[2]){argv[i][invalidIndex], 0}, "\'",
									  NULL}),
								  true);
			return (false);
		}
		if ((!isValidDir || !isValidFile))
		{
			display_error_to_free(array_to_str((char *[]){
									  "ft_ls: impossible d'accéder à \'",
									  argv[i],
									  "\': Aucun fichier ou dossier de ce type",
									  NULL}),
								  true);
			return (false);
		}
		resetValidParts(&isValidArg, &isValidDir, &isValidFile);
	}
	return (true);
}
bool parse(int argc, char **argv)
{
	if (!check_args_validity(argc, argv))
		return (false);
	// Symbolic Links
	fix_args_symbolic();

	if (get_struct_ls()->s_files)
	{
		if (!LS_ARG_containItem(E_LS_ARG_F))
		{
			sort_array_alphabeticaly(get_struct_ls()->s_files);
			if (LS_ARG_containItem(E_LS_ARG_T))
				sort_array_by_time(get_struct_ls()->s_files);
			if (LS_ARG_containItem(E_LS_ARG_LR))
				invert_array(get_struct_ls()->s_files);
		}
	}
	if (get_struct_ls()->s_dir)
	{
		if (!LS_ARG_containItem(E_LS_ARG_F))
		{
			sort_array_alphabeticaly(get_struct_ls()->s_dir);
			if (LS_ARG_containItem(E_LS_ARG_T))
				sort_array_by_time(get_struct_ls()->s_dir);
			if (LS_ARG_containItem(E_LS_ARG_LR))
				invert_array(get_struct_ls()->s_dir);
		}
	}
	else if (!get_struct_ls()->s_files)
	{
		get_struct_ls()->s_dir = ft_calloc(sizeof(char *), 2);
		get_struct_ls()->s_dir[0] = ft_strcpy(".");
		get_struct_ls()->s_dir[1] = NULL;
	}
	if (array_len(get_struct_ls()->s_dir) > 1)
		get_struct_ls()->display_file_infos = true;
	else if (get_struct_ls()->s_dir && get_struct_ls()->s_files)
		get_struct_ls()->display_file_infos = true;
	else
	{
		if (get_struct_ls()->args)
		{
			for (size_t i = 0; get_struct_ls()->args[i]; i++)
			{
				if (get_struct_ls()->args[i] == E_LS_ARG_R)
					get_struct_ls()->display_file_infos = true;
			}
		}
	}
	return (true);
}
