#include "minishell.h"

void    display_prompt(int num)
{
    num++;
    write(1, "\n", 1);
//    rl_replace_line("", 0);
    rl_on_new_line();
}
    
void    define_input_signals(void)
{
    signal(SIGINT, display_prompt);//CTRL+C
    signal(SIGQUIT, SIG_IGN);//CTRL+"\"
}