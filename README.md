### printf implementation for 42 school projects  
Includes support for [cspdiouxXf] conversions and [h/hh/l/ll/L] flags for additional type casting.  
Supports [#0-+ ] flags, field width and precision. Width and precision can be given as an additional argument [\*].  
Additionally supports wide characters (UTF-8) and writing to given file descriptor with ft_fprintf().  
Nul-pointer handling, special floating point values etc. mainly follow the glibc implementation.    
  
![](example.gif)
