/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:51:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 14:49:30 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/xattr.h>
#include <sys/sysmacros.h>

#include <stdio.h>
#include "utils.h"

#define E_LS_MAX_ARGS 8
#define HASH_MAX_LEN 4096
#define NNULL_PTR ""

#define PATH_MAX 4096
#define LST_NEXT(lst) lst = lst->next

/* STAT | Timespec | Backward compatibility */
#define st_atime st_atim.tv_sec
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec

struct s_file_map;

#define TF struct s_file

enum E_LS_ARGS
{
	E_LS_ARG_NONE,
	E_LS_ARG_L,
	E_LS_ARG_R,
	E_LS_ARG_A,
	E_LS_ARG_LR,
	E_LS_ARG_T,
	E_LS_ARG_F,
	E_LS_ARG_G,
};

enum E_FILE_TYPE
{
	FT_BLK = DT_BLK,
	FT_CHR = DT_CHR,
	FT_DIR = DT_DIR,
	FT_FIFO = DT_FIFO,
	FT_LNK = DT_LNK,
	FT_REG = DT_REG,
	FT_SOCK = DT_SOCK,
	FT_UNKNOWN = DT_UNKNOWN,
};

#define LS_ARGS "lRartfg"

typedef struct s_link
{
	struct stat lst;  // LinkFileStats
	char *lnk_buffer; // ReadDirBufferResult
} t_link;

typedef struct s_file
{
	char *name;			   // fileName
	char *filePath;		   // fullPathToAccessFile
	char *directory;	   // DirectoryOfThisFile
	enum E_FILE_TYPE type; // FileType
	struct stat st;		   // FileStats (with st)
	t_link ln;			   // Struct symbolic link
	struct s_file *next;   // Next ptr
} t_file;

typedef struct s_ls
{
	enum E_LS_ARGS *args;	 // LS Args
	char **s_dir;			 // LS Directories
	char **s_files;			 // LS Files
	bool display_file_infos; // Display file info (with -R & multiple files)
} t_ls;

// CORE
void readdir_rec(char *start_path);
bool diplay_files_selected();
bool display_dir_info(enum E_LS_ARGS arg, char *current_dir);
void display_file_color(struct stat st, enum E_FILE_TYPE eft);
void display_multi_dir_info(char *current_dir);

// LS CASES
void ls_case_none(TF *list, char *current_dir);
void ls_case_l(TF *list, char *current_dir, bool displayTotal);
void ls_case_r(TF *list, char *current_dir);

// FILES UTILS
void *sortFiles(TF **files);
TF *readAllFilesInDir(char *path, bool *error);
bool removeHiddenFiles(TF **list);

int ft_timeCompare(TF *node, TF *node2);

// FILES MANAGEMENT
bool TFaddDirentFile(TF **list, struct dirent *file, char *path);
bool TFaddDirentFiles(TF **list, struct dirent **files, char *path);
bool TFaddFile(TF **list, TF newFile);
bool TFaddFiles(TF **list, TF **arrayfiles);
bool TFaddList(TF **list, TF **add);

void TFeraseElement(TF **list, TF element);
void TFfreeFiles(TF **list);
void TFcleanFiles(TF **list);

TF *TFgetFiles(TF *list);
TF *TFgetElement(TF **list, TF *element);
size_t TFfilesLen(TF *list);
void TFprintList(TF **list);
TF *TFfilesCopy(TF *list, bool freeList);

TF *TFbackLST(TF **lst);
TF *TFinvertList(TF **lst);
void *TFswapElements(TF **list, TF *element, TF *element2);
TF *TFswap(TF *element, TF *element2);

// Parsing //

bool parse(int argc, char **argv);

// 	DISPLAY UTILS
void display_permissions(struct stat st, char *path, bool use_acl);
void displayNBRFromRight(size_t nbr, int maxSize);
void displaySTRFromRight(char *str, int maxSize);
void displaySTRFromLeft(char *str, int maxSize);
void display_time(time_t t);
bool displayLink(TF *element);

// UTILS //

t_ls *get_struct_ls();

void multiFree(void **freePtrs);
bool dirContainDirectory(TF *lst);
char get_file_acl(char *path);

bool isFile(char *file);
bool isDir(char *path);
void freeDirentArray(struct dirent **files);
struct stat getFileStat(char *path);
struct dirent *direntCopy(struct dirent *rp);

bool LS_ARG_containItem(size_t item);
void append_LS_ARG(size_t to_add);
enum E_LS_ARGS *remove_all_args_in_str(enum E_LS_ARGS en);
char convert_ls_args_to_char(enum E_LS_ARGS en);
enum E_LS_ARGS convert_char_to_ls_args(char c);
char *convert_file_type_to_string(enum E_FILE_TYPE eft);

void set_file_type(struct stat st, enum E_FILE_TYPE *type);

#endif
