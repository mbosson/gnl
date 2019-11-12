/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbosson <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/12 12:30:14 by mbosson      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 18:15:18 by mbosson     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> // A RETIRER

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

int		is_there_n(char *staticstr)
{
	int			i;

	i = 0;
	while (staticstr[i])
	{
		if (staticstr[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		fill_staticstr(char **staticstr, int start)
{
	char	*buffer;
	int		len;
	int i;

	i = 0;
	len = 0;
	while ((*staticstr)[start + len] != 0)
		len++;
	if ((buffer = malloc(sizeof(char) * (len + 1))) == 0)
		return (-1);
	while ((*staticstr)[start + i] != 0)
	{
		buffer[i] = (*staticstr)[start + i];
		i++;
	}
	buffer[i] = 0;
	*staticstr = buffer;
	return (1);
}

int		fill_line(char **line, char **staticstr)
{
	int			i;
	int			len;
	char		*buffer;

	i = 0;
	len = 0;
	while ((*staticstr)[len] != '\n' && (*staticstr)[len] != 0)
		len++;
	if ((buffer = malloc(sizeof(char) * (len + 1))) == 0)
		return (-1);
	while ((*staticstr)[i] != '\n' && (*staticstr)[len] != 0)
	{
		buffer[i] = (*staticstr)[i];
		i++;
	}
	buffer[i] = 0;
	*line = buffer;
	return (fill_staticstr(staticstr, len));
}

int		get_next_line(int fd, char **line)
{
	char static	*staticstr;

	if (fd < 1 || read(fd, staticstr, 0) == -1 || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	if (staticstr == 0)
	{
		if ((staticstr = malloc(sizeof(char) * BUFFER_SIZE + 1)) == 0)
			return (-1);
		staticstr[BUFFER_SIZE] = 0;
		read(fd, staticstr, BUFFER_SIZE);
		while (is_there_n(staticstr) == 0)
			read(fd, staticstr, BUFFER_SIZE);
	}
	if (fill_line(line, &staticstr) == -1)
		return (-1);
	printf("static : %s\n", staticstr);
	return (1);
}

int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("1ere lecture : %s\n", line);
	get_next_line(fd, &line);
	printf("2ere lecture : %s\n", line);
}
