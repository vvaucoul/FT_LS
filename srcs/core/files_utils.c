/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:31:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 17:12:22 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//****************************************************************************//
//								FILES MANAGEMENT							  //
//****************************************************************************//

// STATICS
static void *TFaddElement(TF **list, TF element)
{
	TF *newFile = NULL;

	// Init Element values
	{
		if (!(newFile = ft_calloc(sizeof(TF), 1)))
			return (NULL);
		newFile->name = ft_strcpy(element.name);
		newFile->filePath = element.filePath;
		newFile->directory = element.directory;
		newFile->type = element.type;
		newFile->st = element.st;
		newFile->ln = element.ln;
		newFile->next = NULL;
	}
	if (!(*list))
	{
		*list = newFile;
		return (NNULL_PTR);
	}
	else
	{
		TF *tmp = *list;

		while (tmp->next)
			LST_NEXT(tmp);
		tmp->next = newFile;
	}
	return (NNULL_PTR);
}
static bool TFisEqual(TF element, TF compare)
{
	if (!ft_strcmp(element.name, compare.name) &&
		!ft_strcmp(element.filePath, compare.filePath) &&
		!ft_strcmp(element.directory, compare.directory) &&
		element.type == compare.type)
		return (true);
	return (false);
}

// FREE / CLEAN
void TFeraseElement(TF **list, TF element)
{
	TF *current = *list;
	TF *toDelete = NULL;

	if (!*list)
		return;

	// Find Element to delete
	while (current)
	{
		if (TFisEqual(element, *current))
		{
			toDelete = current;
			break;
		}
		else
			LST_NEXT(current);
	}

	if (*list == toDelete)
		*list = toDelete->next;
	if (*list == NULL || toDelete == NULL)
		return;
	if (*list == toDelete)
		*list = toDelete->next;
	if (toDelete->type == FT_LNK)
		free(toDelete->ln.lnk_buffer);
	free(toDelete->name);
	free(toDelete);
	return;
}
void TFfreeFiles(TF **list)
{
	TF *toDelete = NULL;
	TF *tmp = *list;

	while (tmp)
	{
		toDelete = tmp;
		tmp = tmp->next;
		if (toDelete->type == FT_LNK)
			free(toDelete->ln.lnk_buffer);
		free(toDelete->name);
		free(toDelete);
	}
	tmp = NULL;
}
void TFcleanFiles(TF **list)
{
	TFfreeFiles(list);
	*list = NULL;
}

// ADD ELEMENTS
bool TFaddFile(TF **list, TF newFile)
{
	if (!list)
		return (false);
	if (!(TFaddElement(list, newFile)))
		return (false);
	return (true);
}
bool TFaddFiles(TF **list, TF **arrayfiles)
{
	if (!arrayfiles)
		return (false);
	for (size_t i = 0; arrayfiles[i]; i++)
	{
		if (!(TFaddElement(list, *(arrayfiles)[i])))
			return (false);
	}
	return (true);
}
bool TFaddList(TF **list, TF **add)
{
	if (!(list) || !add)
	{
		return (false);
	}
	else
	{
		TF *tmp = *list;
		TF *tmpAdd = *add;

		size_t index = 1;
		while (tmp->next)
		{
			++index;
			LST_NEXT(tmp);
		}
		while (tmpAdd->next)
		{
			tmp->next = tmpAdd;
			LST_NEXT(tmpAdd);
			LST_NEXT(tmp);
		}
	}
	return (true);
}
bool TFaddDirentFile(TF **list, struct dirent *file, char *path)
{
	TF element;

	if (!(file))
		return (false);
	element.name = file->d_name;
	element.filePath = path;
	element.directory = path;
	element.type = direntTypeToFileType(file->d_type);

	char *tmp = ft_multijoin((char *[]){
								 path, file->d_name, NULL},
							 "/");
	if ((stat(tmp, &element.st)) == -1)
		return (false);
	if (element.type == FT_LNK)
	{
		if ((lstat(tmp, &element.ln.lst)) == -1)
			return (false);
		element.st = element.ln.lst;
		size_t buffSize = element.ln.lst.st_size == 0 ? PATH_MAX : element.ln.lst.st_size + 1;
		if (!(element.ln.lnk_buffer = ft_calloc(sizeof(char), buffSize)))
		{
			perror("malloc");
			return (false);
		}
		int nBytes = 0;
		if ((nBytes = readlink(tmp, element.ln.lnk_buffer, buffSize)) == -1)
			return (false);
		if (nBytes == (int)buffSize)
		{
			display_error("Returned buffer may have been truncated");
			return (false);
		}
	}
	else
	{
		element.ln = (t_link){0};
	}
	free(tmp);
	element.next = NULL;
	TFaddFile(list, element);
	return (true);
}
bool TFaddDirentFiles(TF **list, struct dirent **files, char *path)
{
	TF **arrayFiles = NULL;

	if (!files)
		return (false);
	size_t i = 0;
	for (; files[i]; i++)
		;
	if (!(arrayFiles = ft_calloc(sizeof(TF), i + 1)))
		return (false);
	for (size_t i = 0; files[i]; i++)
	{
		TFaddDirentFile(list, files[i], path);
	}
	free(arrayFiles);
	return (true);
}

// GET
TF *TFgetFiles(TF *list)
{
	return (list);
}
TF *TFgetElement(TF **list, TF *element)
{
	TF *tmp = *list;

	size_t i = 0;
	while (tmp)
	{
		if (TFisEqual(*tmp, *element))
		{
			return (tmp);
		}
		LST_NEXT((tmp));
		++i;
	}
	return (NULL);
}

// UTILS
TF *TFswap(TF *element, TF *element2)
{
	element->next = element2->next;
	element2->next = element;
	return (element2);
}
void *TFswapElements(TF **list, TF *element, TF *element2)
{
	if (!*list || !element || !element2)
		return (NULL);
	if (element == element2)
		return (NULL);

	TF *prevX = NULL, *currX = *list;
	while (currX && !TFisEqual(*currX, *element))
	{
		prevX = currX;
		currX = currX->next;
	}

	TF *prevY = NULL, *currY = *list;
	while (currY && !TFisEqual(*currY, *element2))
	{
		prevY = currY;
		currY = currY->next;
	}

	if (currX == NULL || currY == NULL)
		return (NULL);

	if (prevX != NULL)
	{
		prevX->next = currY;
	}
	else
		*list = currY;
	if (prevY != NULL)
	{
		prevY->next = currX;
	}
	else
	{
		*list = currX;
	}

	// Swap next pointers
	TF *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;

	return (NNULL_PTR);
}
size_t TFfilesLen(TF *list)
{
	size_t len = 0;
	TF *tmp = list;

	if (!list)
	{
		return (0);
	}
	else
	{
		while (tmp)
		{
			++len;
			tmp = tmp->next;
		}
	}
	return (len);
}
TF *TFfilesCopy(TF *list, bool freeList)
{
	TF *newList = NULL;

	if (!(list))
		return (NULL);
	else
	{
		TF *tmp = list;

		while (tmp)
		{
			TFaddElement(&newList, *tmp);
			LST_NEXT(tmp);
		}
		if (freeList)
			TFfreeFiles(&list);
	}
	return (newList);
}

// DISPLAY
void TFprintList(TF **list)
{
	if (!list)
	{
		ft_putendl(YELLOW "WARNING: list is empty !" NORMAL);
	}
	TF *tmp = *list;

	size_t element = 0;
	while (tmp)
	{
		printf("Element: [%ld] | Name: [%s]\n", element, tmp->name);
		tmp = tmp->next;
		++element;
	}
}
