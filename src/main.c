/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/08 20:35:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTE: (implementation detail) God Save the King
//              z   $b$$F
//             F"  4$$P"
//              r *$$$".c...
//              %-4$$$$$$$$"
//               J$*$$$$$$P
//              ^r4$$$$$$"
//                *f*$$*"
//              ".4 *$$$$$$.
//        4ee%.e.  .$$$$$$$$r DIEU ET MON DROIT
//       4$$$$$$b  P$**)$$$$b REX ANGLIAE DEI GRATIA
//    e..4$$$$$$$"     $$$$$$c.
//    3$$$$$$$$*"   "  ^"$$$$$$c
//   *$$$$$$$$$.        *$$$$$$$.
//    ..$$$$$$$L    c ..J$$$$$$$b
//    d"$$$$$$$F   .@$$$$$$$$$$$P"..
// ..$$$$$$$$$$      d$$$$$$$$$$$$$$$
// =$$$$$$P"" "    .e$$$$$$$$$$$$$$$$
//   *""          $**$$$$$$$$$$$$$$*
//                    "".$$$$$$$$$C .
//                 .z$$$$$$$$$$$$$$""
//                .$$$*"^**"  "
//              =P"  "
//      BORN  TO  ROYAL
//        KINGDOM  IS  A  FUCK
//           EXECUTE  EM  ALL  1660
//              I AM CROWN MAN
//                  410,757,864,530  GOLD  DUCATS
//

static void	dbg_print_lines(char **lines)
{
	int	iter;

	iter = 0;
	while (lines[iter])
	{
		printf("%d: %s\n", iter, lines[iter]);
		iter++;
	}
}

int	prompt(t_ms *ms)
{
	splash();
	ms->line = readline("λ :: > ");
	line_parser(ms);
	dbg_print_lines(ms->lines);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
	{
		//global_sig = 0;
		if (check_fd())
			return (msg_err("fd problem()", FAILURE));
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			return (1);
		if (init_ms_struct(ms))
			return (msg_err("init_ms_struct()", FAILURE));
		if (init_env_struct(ms, envp))
			return (msg_err("init_env_struct()", FAILURE));
		prompt(ms);
		//clean_tokenlist(&ms->tokenlist);
		//clean_env(ms->env);
		//free (ms);
		return (0);
	}
	return (msg_err("Please do not provide any arguments.", 1));
}
