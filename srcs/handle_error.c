#include "../include/minishell.h"

void 	handle_error(t_data *data)
{
	printf("error %d\n", data->error->errno);
	if (data->error->errno == QUOTE)
	{
		free(data->command);
		free(data->new_command);
	}
	if (data->error->value)
		printf("%s\n", data->error->value);
	free(data->error->value);
	data->error->errno = NOERROR;
}
