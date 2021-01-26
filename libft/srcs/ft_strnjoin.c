#include <stdlib.h>
#include "../include/libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int len)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
		+ len) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strncat(str, s2, len);
	return (str);
}
