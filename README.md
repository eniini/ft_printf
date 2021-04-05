### ANSI-compliant printf implementation for 42 school projects
Features [cspdiouxXf] conversions and [h/hh/l/ll/L] flags for additional type casting.
Supports [#0-+ ] flags, field width and precision. Width and precision can be given as an additional argument (\*).
Additionally supports wide characters (UTF-8) and writing to given file descriptor via ft_fprintf(2).
Nul-pointer handling, special floating point values etc. mainly follow glibc implementation.

![](example.gif)
