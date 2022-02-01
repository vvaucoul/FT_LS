/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:39:29 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 13:21:39 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <errno.h>

/*
** COLORS
*/

#define NORMAL "\e[0m"
#define BOLD "\e[1m"

#define BLACK "\e[0;30m"
#define WHITE "\e[0;37m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN "\e[0;36m"

#define BG_YELLOW "\e[43m"
#define BG_RED "\e[41m"
#define BG_CYAN "\e[46m"
#define BG_BLUE "\e[44m"

// Create Boolean Type //
typedef enum
{
	false,
	true
} bool;

// UTILS - VALUES
void *getTMPValue(bool clean, void *ptr);
size_t ft_nbrlen(int n);

// - FREE
void freeProgramm();

// UTILS - DIRECTORY
enum E_FILE_TYPE direntTypeToFileType(unsigned char type);

// UTILS - DISPLAY
void ft_putstr(char *str);
void ft_putendl(char *str);
void ft_putnbr(int n);

void display_error(char *str);
void display_error_to_free(char *str, bool to_free);

// UTILS - STR
bool str_contain_one_of(char *str, char *compare);
bool char_contain_one_of(char c, char *compare);
char *ft_strcpy(char *str);
int ft_strcmp(char *str, char *str2);
int ft_alphabeticalcmp(char *s1, char *s2);
char *ft_strtolower(char *str);
int ft_strlen(char *str);
char *ft_strjoin(char *s1, char *s2, bool to_free);
char *ft_multijoin(char **arr, char *del);
char *remove_doublons(char *str, char c);
char *remove_char_in_str(char *str, char c);
void ft_swap(void **ptr, void **ptr2);
char *ft_itoa(int n);

// UTILS - ARRAY
void free_array(char **arr);
char *array_to_str(char **arr);
void *append_array(char **arr, char *str);
char **copy_array(char **arr);
void sort_array_alphabeticaly(char **arr);
void sort_array_by_time(char **arr);
size_t array_len(char **arr);
size_t array_size(char **arr);
void invert_array(char **arr);
char **remove_array_element(char **arr, char *element);

// UTILS - MEMORY
void *ft_memset(void *b, int c, size_t len);
void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
size_t ft_memlen(void *ptr);
void *ft_memlower(char *str);

// UTILS - ALLOC
void *ft_realloc(void *ptr, size_t newsize);
void *ft_calloc(size_t count, size_t size);

#endif
