/* ************************************************************************** */
/*                                                                            */
/*   parser_helper.c                                                          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/argv_env.h"

static t_token	*skip_redir(t_token *token)
{
	token = token->next;
	if (token)
		token = token->next;
	return (token);
}

static t_redir	*new_redir(t_token *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->file = ft_strdup(token->next->value);
	node->next = NULL;
	if (!node->file)
		return (free(node), NULL);
	return (node);
}

int	count_cmd_argc(t_token *token)
{
	int	n;

	n = 0;
	while (token && token->type != PIPE)
	{
		if (is_redir_type(token->type))
			token = skip_redir(token);
		else
		{
			n++;
			token = token->next;
		}
	}
	return (n);
}

int	build_redirs(t_token *token, t_redir **head)
{
	t_redir	*tail;
	t_redir	*new;

	*head = NULL;
	tail = NULL;
	while (token && token->type != PIPE)
	{
		if (is_redir_type(token->type) && token->next)
		{
			new = new_redir(token);
			if (!new)
				return (free_redir(*head), -1);
			if (!*head)
				*head = new;
			else
				tail->next = new;
			tail = new;
			token = token->next->next;
		}
		else
			token = token->next;
	}
	return (0);
}

int	build_argv_arr(t_argv *node, t_token *token)
{
	int	n;

	n = 0;
	node->argv = malloc(sizeof(char *) * (node->argc + 1));
	if (!node->argv)
		return (-1);
	while (token && token->type != PIPE)
	{
		if (is_redir_type(token->type))
			token = skip_redir(token);
		else
		{
			node->argv[n] = ft_strdup(token->value);
			if (!node->argv[n])
				return (-1);
			n++;
			token = token->next;
		}
	}
	node->argv[n] = NULL;
	return (0);
}
