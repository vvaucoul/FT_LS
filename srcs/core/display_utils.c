/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:54:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/25 22:35:50 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

char get_file_acl(char *path) {
	ssize_t buflen = 0;

	buflen = listxattr(path, NULL, 0);
	if (buflen == -1) {
		return (' ');
	} else if (!buflen) {
		return (' ');
	} else
		return ('+');
}

void display_permissions(struct stat st, char *path, bool use_acl) {
	char perm[11];

	ft_memset(&perm, 0, 11);
	perm[0] = (( S_ISDIR(st.st_mode)) ? 'd' :
		S_ISFIFO(st.st_mode) ? 'p' :
		S_ISSOCK(st.st_mode) ? 's' :
		S_ISCHR(st.st_mode) ? 'c' :
		S_ISBLK(st.st_mode) ? 'b' :
		S_ISLNK(st.st_mode) ? 'l' : '-');
    perm[1] = ((st.st_mode & S_IRUSR) ? 'r' : '-');
    perm[2] = ((st.st_mode & S_IWUSR) ? 'w' : '-');
    perm[3] = ((st.st_mode & S_IXUSR) ? 'x' : '-');
    perm[4] = ((st.st_mode & S_IRGRP) ? 'r' : '-');
    perm[5] = ((st.st_mode & S_IWGRP) ? 'w' : '-');
    perm[6] = ((st.st_mode & S_IXGRP) ? 'x' : '-');
    perm[7] = ((st.st_mode & S_IROTH) ? 'r' : '-');
    perm[8] = ((st.st_mode & S_IWOTH) ? 'w' : '-');
    perm[9] = ((st.st_mode & S_IXOTH) ? 'x' : '-');
	perm[10] = use_acl ? get_file_acl(path) : 0;

	if (st.st_mode & S_ISUID) {
		perm[3] = (perm[3] == '-' ? 'S' : 's');
	} else if (st.st_mode & S_ISGID) {
		perm[6] = (perm[6] == '-' ? 'S' : 's');
	} else if (st.st_mode & S_ISVTX) {
		perm[9] = (perm[9] == '-' ? 'T' : 't');
	}

	ft_putstr(perm);
}

void display_time(time_t t) {
	char *stTime = ft_memlower(ctime(&t));
	char current[6];

	ft_memset(current, 0, 6);
	ft_memcpy(current, stTime + 4, 3);
	ft_putstr(current);
	ft_putstr(". ");

	ft_memset(current, 0, 6);
	ft_memcpy(current, stTime + 8, 2);
	ft_putstr(current);
	ft_putstr(" ");

	ft_memset(current, 0, 6);
	ft_memcpy(current, stTime + 11, 5);
	ft_putstr(current);
	ft_putstr(" ");
}

void displaySTRFromLeft(char *str, int maxSize) {
	int lenSize = ft_strlen(str);

	ft_putstr(str);
	if (lenSize == 0)
		lenSize = 1;
	while ((maxSize - lenSize) > 0) {
		write(1, " ", 1);
		++lenSize;
	}
}

void displaySTRFromRight(char *str, int maxSize) {
	int lenSize = ft_strlen(str);

	if (lenSize == 0)
		lenSize = 1;
	while ((maxSize - lenSize) > 0) {
		write(1, " ", 1);
		++lenSize;
	}
	ft_putstr(str);
}

void displayNBRFromRight(size_t nbr, int maxSize) {
	int lenSize = ft_nbrlen(nbr);

	if (lenSize == 0)
		lenSize = 1;
	while ((maxSize - lenSize) > 0) {
		write(1, " ", 1);
		++lenSize;
	}
	ft_putnbr(nbr);
}

bool displayLink(TF *element) {
	if (element->type == FT_LNK) {
		ft_putstr(" -> ");
		struct stat nst;
		enum E_FILE_TYPE nft;

		char *fp = ft_multijoin((char *[]){element->filePath, element->name, NULL}, "/");

		if ((stat(fp, &nst)) != -1) {
			set_file_type(nst, &nft);
			display_file_color(nst, nft);
		}
		ft_putstr(element->ln.lnk_buffer);
		free(fp);
	}
	return (true);
}
