#include "../includes/prototypes.h"
#include "../includes/minishell.h"
#include "../includes/structs.h"

t_token_element	*new_token_element(void)
{
	t_token_element	*new;

	new = malloc(sizeof(t_token_element));
	if (!new)
	{
		msg_err("new_token_element()", FAILURE);
		return (NULL);
	}
	new->type = -1;
	new->next = NULL;
	new->value = NULL;
	return (new);
}

t_token_element *assign_token_element(t_token_element *element, int type)
{
	element->type = type;
	if (type == tkn_cmd)
	{

	}
}

t_token_element	*token_list_generator(int *token_list)
{
	t_token_element	*head;
	t_token_element	*curr_element;
	int				iter;

	iter = 0;
	head = new_token_element();
	if (!head)
	{
		msg_err("token_list_generator()", FAILURE);
		return (NULL);
	}
	while (token_list[iter] != -1)
	{

	}
	return (head);
}
