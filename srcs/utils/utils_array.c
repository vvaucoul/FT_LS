/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:21:24 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:48:12 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//****************************************************************************//
//								   ARRAY - UTILS							  //
//****************************************************************************//

// Array Size (Max X * Y)
size_t array_size(char **arr)
{
	size_t max_x = 0;
	size_t y = 0;

	if (!arr)
		return (0);
	for (; arr[y]; y++)
	{
		for (size_t x = 0; arr[y][x]; x++)
		{
			if (x > max_x)
				max_x = x;
		}
	}
	return ((y + 1) * (max_x + 1));
}

// Array Length
size_t array_len(char **arr)
{
	if (!arr)
		return (0);
	size_t i = 0;
	for (; arr[i]; i++)
		;
	return (i);
}

char *array_to_str(char **arr)
{
	char *str = NULL;

	if (!arr)
		return (NULL);

	size_t x = 0;
	size_t y = 0;
	size_t size[2] = {0, 0};

	for (y = 0; arr[y]; y++)
	{
		for (x = 0; arr[y][x]; x++)
			;
		if (x > size[1])
			size[1] = x;
		size[0] = y;
	}
	if (!(str = malloc(sizeof(char) * ((size[0] + 1) * size[1]) + 1)))
		return (NULL);
	else
	{
		size_t i = 0;

		for (y = 0; arr[y]; y++)
		{
			for (x = 0; arr[y][x]; x++)
			{
				str[i] = arr[y][x];
				++i;
			}
			str[i] = 0;
		}
		return (str);
	}
	return (NULL);
}

//****************************************************************************//
//							    ARRAY - MODIFICATORS						  //
//****************************************************************************//

void *append_array(char **arr, char *str)
{
	char **narray = NULL;
	size_t y = 0;

	if (!arr)
	{
		if (!(narray = ft_calloc(sizeof(char *), (2 * ft_strlen(str)))))
			return (NULL);
		narray[0] = ft_strcpy(str);
		narray[1] = NULL;
	}
	else
	{
		if (!(narray = ft_calloc(sizeof(char *), (array_size(arr) + ft_strlen(str) + 1))))
			return (NULL);
		for (; arr[y]; y++)
		{
			narray[y] = ft_strcpy(arr[y]);
		}
		narray[y] = ft_strcpy(str);
		narray[y + 1] = NULL;
	}
	free_array(arr);
	return (narray);
}

char **copy_array(char **arr)
{
	char **narray = NULL;

	if (!arr)
		return (NULL);
	size_t a_size = array_size(arr);
	if (!a_size)
	{
		if (!(narray = malloc(sizeof(char *))))
			return (NULL);
	}
	else
	{
		if (!(narray = malloc(sizeof(char *) * (a_size))))
			return (NULL);
	}
	size_t y = 0;
	for (; arr[y]; y++)
		narray[y] = ft_strcpy(arr[y]);
	narray[y] = NULL;
	return (narray);
}

void invert_array(char **arr)
{
	size_t j = 0;

	for (size_t i = array_len(arr) - 1; i > 0; i--)
	{
		char *tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		++j;
	}
	arr[j + 1] = NULL;
}

//****************************************************************************//
//							   	   ARRAY - SORT								  //
//****************************************************************************//

void sort_array_alphabeticaly(char **arr)
{
	if (!arr)
		return;
	for (size_t i = 0; arr[i + 1]; i++)
	{
		if (ft_alphabeticalcmp(arr[i], arr[i + 1]) > 0)
		{
			ft_swap((void **)&arr[i], (void **)&arr[i + 1]);
		}
	}
}

void sort_array_by_time(char **arr)
{
	struct stat st, st_next;

	if (!arr)
		return;
	for (size_t i = 0; arr[i + 1]; i++)
	{
		if ((lstat(arr[i], &st)) == -1)
			continue;
		if ((lstat(arr[i + 1], &st_next)) == -1)
			continue;
		if (st.st_mtim.tv_sec < st_next.st_mtim.tv_sec)
			ft_swap((void **)&arr[i], (void **)&arr[i + 1]);
		else if (st.st_mtim.tv_sec == st_next.st_mtim.tv_sec)
		{
			if (st.st_mtim.tv_nsec < st_next.st_mtim.tv_nsec)
				ft_swap((void **)&arr[i], (void **)&arr[i + 1]);
		}
	}
}

//****************************************************************************//
//							    ARRAY - FREE / REMOVE						  //
//****************************************************************************//

void free_array(char **arr)
{
	if (arr)
	{
		for (size_t i = 0; arr[i]; i++)
		{
			free(arr[i]);
		}
		free(arr);
	}
	arr = NULL;
}

char **remove_array_element(char **arr, char *element)
{
	if (!arr)
		return (NULL);
	if (!element)
		return (arr);

	char **narr = NULL;
	size_t j = 0;

	if (!(narr = ft_calloc(sizeof(char *), (array_size(arr) + 1 + ft_strlen(element)))))
		return (NULL);
	for (size_t i = 0; arr[i]; i++)
	{
		if (arr[i] != element)
		{
			narr[j] = ft_strcpy(element);
			narr[j + 1] = NULL;
		}
	}
	if (!j)
	{
		free(narr);
		narr = NULL;
	}
	free_array(arr);
	return (narr);
}