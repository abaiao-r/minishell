
static void parse_aux(t_arg *arg, char *str, int *i, t_input **head, t_input **tail)
{
    char c;
    int prev_was_pipe;

	prev_was_pipe = 0;
    while (*i < arg->string_len && arg->arg_len < arg->string_len)
    {
        c = str[*i];
        if (handle_quotes(arg, c, i))
        {
            if (arg->in_quotes == 1 && arg->within_quotes == 0)
                arg->within_quotes = 1;
            continue;
        }
        if (!arg->in_quotes && ft_isspace(c))
            break;
		if (!arg->in_quotes && c == '<' && str[*i + 1] == '<')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup("<<");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
			(*i)++;
            prev_was_pipe = 1;
            continue;
        }
		if (!arg->in_quotes && c == '<')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup("<");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
            prev_was_pipe = 1;
            continue;
        }
		if (!arg->in_quotes && c == '>' && str[*i + 1] == '>')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup(">>");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
			(*i)++;
            prev_was_pipe = 1;
            continue;
        }
		if (!arg->in_quotes && c == '>')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup(">");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
            prev_was_pipe = 1;
            continue;
        }
        if (!arg->in_quotes && c == '|' && str[*i + 1] == '|')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup("||");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
			(*i)++;
            prev_was_pipe = 1;
            continue;
        }
        if (!arg->in_quotes && c == '|')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = arg->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                arg->arg_index++;
                arg->arg = malloc(arg->string_len * sizeof(char));
                arg->arg_len = 0;
            }
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup("|");
            new_input->index = arg->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            arg->arg_index++;
            (*i)++;
            prev_was_pipe = 1;
            continue;
        }
        arg->arg[arg->arg_len++] = c;
        (*i)++;
        prev_was_pipe = 0;
    }

    if (arg->arg_len > 0)
    {
        arg->arg[arg->arg_len] = '\0';

        t_input *new_input = malloc(sizeof(t_input));
        new_input->input = arg->arg;
        new_input->index = arg->arg_index;
        new_input->within_quotes = arg->within_quotes;
        new_input->next = NULL;

        if (*head == NULL)
        {
            *head = new_input;
            *tail = new_input;
        }
        else
        {
            (*tail)->next = new_input;
            *tail = new_input;
        }

        arg->arg_index++;
    }
    else if (!prev_was_pipe)
        free(arg->arg);
}