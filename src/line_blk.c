#include "../includes/minishell.h"
#include "../includes/structs.h"
#include "../includes/prototypes.h"

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
//              BORN  TO  ROYAL
//                KINGDOM  IS  A  FUCK
//                   EXECUTE  EM  ALL  1660
//                      I AM CROWN MAN
//                          410,757,864,530  GOLD  DUCATS

// NOTE: IMPORTANT
// This function is terribly temporary. Currently interprets
// bloody everything as either a command or a pipe_blk.
t_line_blk *line_blk_array_generator(char **lines, int n_blocks)
{
	t_line_blk	*line_blk;

	line_blk = malloc(sizeof(t_line_blk) * n_blocks);
	if (!line_blk)
	{
		msg_err("line_blk_array_generator()", FAILURE);
		return (NULL);
	}
	if (n_blocks == 2)
	{
		line_blk[0].type = tkn_pipe;
		line_blk[0].val[0] = lines[0];
		line_blk[0].val[1] = lines[1];
	}
	else
	{
		line_blk[0].type = tkn_cmd;
		line_blk[0].val[0] = lines[0];
		line_blk[0].val[1] = NULL;
	}
	return (line_blk);
}
