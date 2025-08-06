/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaehun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:35:23 by schaehun          #+#    #+#             */
/*   Updated: 2022/04/08 20:28:19 by schaehun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_cut(char *s)
{
	int		i;
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[0] == '\n')
		len = 0;
	str = (char *)malloc(len + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	free(s);
	return (str);
}

void	ft_swap(char *tmp, char *buf, char **line)
{
	tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = tmp;
}

char	*get_next_line(int fd)
{
	int			len;
	static char	*line;
	char		*tmp;
	char		*out;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = "";
	while (ft_search(line) == 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		buf[len] = '\0';
		if (len < 1)
			break ;
		if (line == NULL)
			line = ft_strdup(buf);
		else
			ft_swap(tmp, buf, &line);
	}
	out = ft_strdup(line);
	free(line);
	line = ft_strdup(ft_strchr(out, '\n'));
	return (ft_cut(out));
}
