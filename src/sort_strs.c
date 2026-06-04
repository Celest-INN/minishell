/* ************************************************************************** */
/*                                                                            */
/*   sort_strs.c                                                              */
/*   改动: 去掉 wildcard 用的 entry_strcmp, sort_entry, mutistrdup            */
/*   只保留 ft_memcpy 和 ft_strjoin (expander 用)                             */
/*                                                                            */
/* ************************************************************************** */

#include "argv_env.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	if (dest == NULL && src == NULL)
		return (NULL);
	tmp_d = (unsigned char *)dest;
	tmp_s = (unsigned char *)src;
	while (n > 0)
	{
		*tmp_d = *tmp_s;
		tmp_d++;
		tmp_s++;
		n--;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == 0)
		return (NULL);
	ft_memcpy(join, s1, ft_strlen(s1));
	ft_memcpy(&join[ft_strlen(s1)], s2, ft_strlen(s2));
	join[ft_strlen(s1) + ft_strlen(s2)] = 0;
	return (join);
}
