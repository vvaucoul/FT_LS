/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 00:00:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:44:54 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ft_ls.h"

//****************************************************************************//
//									LS UTILS								  //
//****************************************************************************//

t_ls *get_struct_ls()
{
	static t_ls *ls = NULL;

	if (!ls)
	{
		if (!(ls = malloc(sizeof(t_ls))))
			return (NULL);
		ls->args = NULL;
		ls->s_dir = NULL;
		ls->s_files = NULL;
		ls->display_file_infos = false;
	}
	return (ls);
}

bool removeHiddenFiles(TF **list)
{
	TF *current = *list;
	TF *tmp = NULL;

	while (current)
	{
		if (current->name[0] == '.')
			tmp = current;
		current = current->next;
		if (tmp)
		{
			TFeraseElement(list, *tmp);
			tmp = NULL;
		}
	}
	return (true);
}

bool isDir(char *path)
{
	DIR *dir = NULL;
	if ((dir = opendir(path)))
	{
		closedir(dir);
		return (true);
	}
	else
		return (false);
}
bool isFile(char *file)
{
	struct stat st;
	if ((stat(file, &st)) == -1)
		return (false);
	return (!S_ISDIR(st.st_mode));
}
bool dirContainDirectory(TF *lst)
{
	if (!lst)
		return (false);
	for (TF *tmp = lst; tmp; LST_NEXT(tmp))
	{
		if (tmp->type == FT_DIR &&
			(tmp->name[0] != '.' && !LS_ARG_containItem(E_LS_ARG_A)))
			return (true);
	}
	return (false);
}

enum E_LS_ARGS convert_char_to_ls_args(char c)
{
	if (c == 0)
		return (E_LS_ARG_NONE);
	else if (c == 'l')
		return (E_LS_ARG_L);
	else if (c == 'R')
		return (E_LS_ARG_R);
	else if (c == 'a')
		return (E_LS_ARG_A);
	else if (c == 'r')
		return (E_LS_ARG_LR);
	else if (c == 't')
		return (E_LS_ARG_T);
	else if (c == 'f')
		return (E_LS_ARG_F);
	else if (c == 'g')
		return (E_LS_ARG_G);
	return ('0');
}
char convert_ls_args_to_char(enum E_LS_ARGS en)
{
	if (en == 0)
		return ('0');
	else if (en == E_LS_ARG_L)
		return ('l');
	else if (en == E_LS_ARG_R)
		return ('R');
	else if (en == E_LS_ARG_A)
		return ('a');
	else if (en == E_LS_ARG_LR)
		return ('r');
	else if (en == E_LS_ARG_T)
		return ('t');
	else if (en == E_LS_ARG_F)
		return ('f');
	else if (en == E_LS_ARG_G)
		return ('g');
	return ('0');
}
enum E_LS_ARGS *remove_all_args_in_str(enum E_LS_ARGS en)
{
	enum E_LS_ARGS *nt = NULL;

	if (!(nt = ft_calloc(sizeof(enum E_LS_ARGS), E_LS_MAX_ARGS + 1)))
		return (NULL);
	if (get_struct_ls()->args)
	{
		size_t j = 0;
		for (size_t i = 0; get_struct_ls()->args[i]; i++)
		{
			if (get_struct_ls()->args[i] != en)
			{
				nt[j] = get_struct_ls()->args[i];
				++j;
			}
		}
		nt[j] = E_LS_MAX_ARGS;
		free(get_struct_ls()->args);
		get_struct_ls()->args = nt;
	}
	return (nt);
}

char *convert_file_type_to_string(enum E_FILE_TYPE eft)
{
	switch ((int)eft)
	{
	case FT_BLK:
		return ("FT_BLK");
	case FT_CHR:
		return ("FT_CHR");
	case FT_DIR:
		return ("FT_DIR");
	case FT_FIFO:
		return ("FT_FIFO");
	case FT_LNK:
		return ("FT_LNK");
	case FT_REG:
		return ("FT_REG");
	case FT_SOCK:
		return ("FT_SOCK");
	case FT_UNKNOWN:
		return ("FT_UNKNOWN");
	}
	return ("0");
}

bool LS_ARG_containItem(size_t item)
{
	if (get_struct_ls()->args)
	{
		for (size_t i = 0; get_struct_ls()->args[i]; i++)
		{
			if (get_struct_ls()->args[i] == item)
				return (true);
		}
	}
	return (false);
}
void append_LS_ARG(size_t to_add)
{
	enum E_LS_ARGS *narr = NULL;

	if (!get_struct_ls()->args)
	{
		narr = ft_calloc(sizeof(enum E_LS_ARGS), E_LS_MAX_ARGS + 1);
		narr[0] = to_add;
		narr[1] = E_LS_MAX_ARGS;
		get_struct_ls()->args = narr;
	}
	else
	{
		narr = ft_calloc(sizeof(enum E_LS_ARGS), E_LS_MAX_ARGS + 1);
		size_t i = 0;
		for (; get_struct_ls()->args[i] != E_LS_MAX_ARGS; i++)
		{
			narr[i] = get_struct_ls()->args[i];
		}
		if (!LS_ARG_containItem(to_add))
		{
			narr[i] = to_add;
			narr[i + 1] = E_LS_MAX_ARGS;
		}
		else
			narr[i] = E_LS_MAX_ARGS;
		free(get_struct_ls()->args);
		get_struct_ls()->args = narr;
	}
}

int ft_timeCompare(TF *node, TF *node2)
{
	if (node->st.st_mtime == node2->st.st_mtime)
		return (ft_alphabeticalcmp(node->name, node2->name));
	else
		return (node->st.st_mtime > node2->st.st_mtime);
}

enum E_FILE_TYPE direntTypeToFileType(unsigned char type)
{
	switch (type)
	{
	case DT_BLK:
		return (FT_BLK);
	case DT_CHR:
		return (FT_CHR);
	case DT_DIR:
		return (FT_DIR);
	case DT_FIFO:
		return (FT_FIFO);
	case DT_LNK:
		return (FT_LNK);
	case DT_REG:
		return (FT_REG);
	case DT_SOCK:
		return (FT_SOCK);
	case DT_UNKNOWN:
		return (FT_UNKNOWN);
	default:
		return (FT_UNKNOWN);
	}
	return (FT_UNKNOWN);
}

//****************************************************************************//
//								   LIB UTILS								  //
//****************************************************************************//

int ft_strlen(char *str)
{
	size_t i = 0;

	if (!str)
		return (0);
	for (; str[i]; i++)
		;
	return (i);
}
void ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putnbr(-214748364);
		write(1, "8", 1);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(n *= -1);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n == 0)
		write(1, "0", 1);
	else
		write(1, &(char){n + 48}, 1);
}
size_t ft_nbrlen(int n)
{
	size_t i = 0;

	if (n == 0)
		return (1);
	for (; n > 0; i++)
	{
		n /= 10;
	}
	return (i);
}
void ft_swap(void **ptr, void **ptr2)
{
	void *tmp = *ptr;

	*ptr = *ptr2;
	*ptr2 = tmp;
}

//****************************************************************************//
//								   	  FREE									  //
//****************************************************************************//

void multiFree(void **freePtrs)
{
	if (!freePtrs)
	{
		return;
	}
	for (size_t i = 0; freePtrs[i]; i++)
	{
		free(freePtrs[i]);
	}
}
void freeProgramm()
{
	free_array(get_struct_ls()->s_dir);
	free_array(get_struct_ls()->s_files);
	free(get_struct_ls()->args);
	free(get_struct_ls());
}
