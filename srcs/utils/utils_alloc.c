/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:52:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 13:19:56 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//****************************************************************************//
//							  	 	 MEMORY				     				  //
//****************************************************************************//

void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t i;
	unsigned char *t_dst;
	const unsigned char *t_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	t_dst = dst;
	t_src = src;
	while (i < n)
	{
		*t_dst = *t_src;
		++t_dst;
		++t_src;
		++i;
	}
	return (dst);
}

void *ft_memset(void *b, int c, size_t len)
{
	unsigned char *t;

	t = (unsigned char *)b;
	while (len--)
		*(t++) = (unsigned char)c;
	return (b);
}

size_t ft_memlen(void *ptr)
{
	size_t i = 0;
	unsigned char *t = (unsigned char *)ptr;

	while (*t)
	{
		++t;
		i++;
	}
	return (i);
}

void *ft_memlower(char *str)
{

	size_t i = 0;
	while (str[i])
	{
		if (str[i] > 'A' && str[i] < 'Z')
			str[i] += 32;
		++i;
	}
	return (str);
}

//****************************************************************************//
//							  	 	 ALLOC				     				  //
//****************************************************************************//

void *ft_realloc(void *ptr, size_t newsize)
{
	char *newptr;
	size_t cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	if ((ptr = malloc(count * size)) == NULL)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
