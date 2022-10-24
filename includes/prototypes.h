#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structs.h"

/* SHELL */
int		prompt(t_ms *ms);

/* ENVIRONMENT */
char	**env_to_arrays(t_env **env);

/* ERROR MESSAGES */
int		msg_err(char *s, int ret);
void	*null_msg_err(char *s);

/* TOKENISATION */
t_exec_element	*tokenizer(t_ms *shell);

/* EXECUTION */
int		execute_command(t_cmd *cmd);
int		executor(t_exec_element *head);
void	dealloc_exec_list(t_exec_element *head);

/* EXEC LIST */
t_exec_element	*exec_list_generator(t_exec_element *head, t_env **env);
t_exec_element	*new_exec_element(void);
void			free_exec_list(t_exec_element *head);

/* LINE PARSER */
char	**parse_line(t_ms *lambda);

/* CMD STRUCT */
t_cmd		*cmd_constructor(char *prog_n, t_env **env);
void		cmd_deallocator(t_cmd *cmd);

/* PATH */
char	*get_path(char *prog_n, t_env **env);
int		free_ptr_array(char *ptr[]);

/* DEBUG */
void	dbg_print_exec_list(t_exec_element *head);
void	dbg_print_lines(char **lines);

#endif
