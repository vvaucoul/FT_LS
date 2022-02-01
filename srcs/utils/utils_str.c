/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:27:34 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 13:22:37 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//****************************************************************************//
//							  	  STR - TESTS			     				  //
//****************************************************************************//

bool char_contain_one_of(char c, char *compare)
{
	for (size_t i = 0; compare[i]; i++)
	{
		if (c == compare[i])
			return (true);
	}
	return (false);
}

bool str_contain_one_of(char *str, char *compare)
{
	for (size_t i = 0; str[i]; i++)
	{
		for (size_t j = 0; compare[j]; j++)
		{
			if (str[i] == compare[j])
				return (true);
		}
	}
	return (false);
}

int ft_strcmp(char *str, char *str2)
{
	unsigned int i;

	i = 0;
	while (str[i] && str[i] == str2[i])
		++i;
	return ((unsigned char)str[i] - (unsigned char)str2[i]);
}

//****************************************************************************//
//							  	  STR - ALLOC			     				  //
//****************************************************************************//

char *ft_strcpy(char *str)
{
	char *nstr = NULL;

	if (!str)
		return (NULL);
	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (NULL);
	int i = 0;
	for (; str[i]; i++)
	{
		nstr[i] = str[i];
	}
	nstr[i] = 0;
	return (nstr);
}

char *ft_remove_char_in_str(char *str, char c)
{
	if (!str)
		return (NULL);

	char *nstr = NULL;
	size_t j = 0;

	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(str))))
		return (NULL);
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] != c)
		{
			nstr[j] = str[i];
			nstr[j + 1] = 0;
			++j;
		}
	}
	nstr[j] = 0;
	if (j == 0)
	{
		free(nstr);
		return (NULL);
	}
	return (nstr);
}

char *ft_remove_string_in_str(char *str, char *cmp)
{
	if (!str)
		return (NULL);
	if (!cmp)
		return (ft_strcpy(str));

	char *nstr = NULL;
	size_t j = 0;
	bool contain = false;

	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (NULL);
	for (size_t i = 0; str[i]; i++)
	{
		for (size_t k = 0; cmp[k]; k++)
		{
			if (str[i] == cmp[k])
			{
				contain = true;
				break;
			}
		}
		if (!contain)
		{
			nstr[j] = str[i];
			nstr[j + 1] = 0;
			++j;
		}
		else
			contain = false;
	}
	nstr[j] = 0;
	if (j == 0)
	{
		free(nstr);
		return (NULL);
	}
	return (nstr);
}

char *ft_memstrremove(char str[PATH_MAX], char *cmp)
{
	if (!str || !cmp)
		return (NULL);

	char nstr[PATH_MAX];

	ft_memset(nstr, 0, PATH_MAX);
	size_t j = 0;
	for (size_t i = 0; str[i]; i++)
	{
		if (char_contain_one_of(str[i], cmp) == true)
			continue;
		else
		{
			nstr[j] = str[i];
			++j;
		}
	}
	ft_memcpy(str, nstr, ft_strlen(str));
	return (str);
}

int ft_alphabeticalcmp(char *s1, char *s2)
{
	char ns1[PATH_MAX] = {0};
	char ns2[PATH_MAX] = {0};

	if (!s1 || !s2)
		return (0);

	if (!ft_strcmp(s1, "."))
		return (-1);
	else if (!ft_strcmp(s2, "."))
		return (1);
	else if (!ft_strcmp(s1, ".."))
		return (-1);
	else if (!ft_strcmp(s2, ".."))
		return (1);

	ft_memcpy(ns1, s1, ft_strlen(s1));
	ft_memcpy(ns2, s2, ft_strlen(s2));

	unsigned int i;

	i = 0;
	while (ns1[i])
	{
		if (ns1[i] == '.' || ns1[i] == '_')
			ns1[i] = ns1[i + 1];
		if (ns2[i] == '.' || ns2[i] == '_')
			ns2[i] = ns2[i + 1];
		if (ns1[i] >= 'A' && ns1[i] <= 'Z')
			ns1[i] += 32;
		if (ns2[i] >= 'A' && ns2[i] <= 'Z')
			ns2[i] += 32;
		if (ns1[i] != ns2[i]) {
			break;
		}
		++i;
	}
	return ((unsigned char)ns1[i] - (unsigned char)ns2[i]);
}

char *ft_strtolower(char *str)
{
	char *nstr = NULL;

	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (NULL);
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			nstr[i] = str[i] + 32;
		else
			nstr[i] = str[i];
	}
	return (nstr);
}

char *ft_strjoin(char *s1, char *s2, bool to_free)
{
	char *nstr = NULL;

	if (!s1 || !s2)
		return (NULL);
	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);

	size_t j = 0;
	for (size_t i = 0; s1[i]; i++)
	{
		nstr[j] = s1[i];
		++j;
	}
	for (size_t i = 0; s2[i]; i++)
	{
		nstr[j] = s2[i];
		++j;
	}
	nstr[j] = 0;
	if (to_free)
		free(s1);
	return (nstr);
}

char *ft_multijoin(char **arr, char *del)
{
	char *str = NULL;

	if (!arr)
		return (NULL);
	if (!del)
		del = "";
	if (!(str = ft_calloc(sizeof(char), array_size(arr) + ft_strlen(del) + 1)))
		return (NULL);
	for (size_t i = 0; arr[i]; i++)
	{
		str = ft_strjoin(str, arr[i], true);
		if (arr[i + 1])
			str = ft_strjoin(str, del, true);
	}
	return (str);
}

char *remove_doublons(char *str, char c)
{
	char *nstr = NULL;

	if (!(nstr = ft_calloc(sizeof(char), (ft_strlen(str) + 1))))
		return (NULL);
	size_t j = 0;
	for (size_t i = 0; str[i]; i++)
	{
		if (i + 1 < (size_t)ft_strlen(str))
		{
			if (str[i] != c || str[i + 1] != c)
			{
				nstr[j] = str[i];
				++j;
			}
		}
		else
		{
			nstr[j] = str[i];
			++j;
		}
	}
	nstr[j] = 0;
	free(str);
	return (nstr);
}

char *remove_char_in_str(char *str, char c)
{
	char *nstr = NULL;

	if (!(nstr = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (NULL);
	size_t j = 0;
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] != c)
			nstr[j++] = str[i];
	}
	nstr[j] = 0;
	free(str);
	return (nstr);
}

char *ft_strdup(char *s1)
{
	char *ptr;
	size_t i;

	if ((ptr = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < (size_t)ft_strlen(s1))
	{
		ptr[i] = s1[i];
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int n_lenght(int n)
{
	int nsize;

	nsize = 0;
	if (n > -2147483648 && n < 0)
	{
		++nsize;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		++nsize;
	}
	return (nsize);
}

static int is_min_int(int n, char **str)
{
	if (n != -2147483648)
		return (0);
	*str = ft_strdup("-2147483648");
	return (1);
}

char *ft_itoa(int n)
{
	int i;
	int size;
	char *str;
	int isneg;

	size = n_lenght(n);
	if ((str = malloc(sizeof(char) * (n_lenght(n) + 1))) == NULL)
		return (NULL);
	if (is_min_int(n, &str) == 1)
		return (str);
	if ((isneg = ((n >= -2147483647 && n < 0) ? 1 : 0)) == 1)
		n *= -1;
	i = (isneg ? 1 : 1);
	while (size - i >= 0)
	{
		str[size - i] = n % 10 + 48;
		n /= 10;
		++i;
	}
	if (isneg)
		str[0] = '-';
	str[size] = '\0';
	return (str);
}
