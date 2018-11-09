This is a simple project written in C to explore the behavior of elementary cellular automata.
It includes a Makefile and some useful Bash scripts. These all require gcc and the Bash shell to be installed. 

Running make will result in the creation of an executable called 'auto'. This can be called with 0 to 2 arguments.
The executable reads an inital state from a file called 'cells'. If this file does not exist, it creates a default 
initial condition with a single black cell in the middle of a row of white cells. The width of the field to evolve is
defined by a preprocessor variable called 'MAX'. The value is currently set at 100. Adjusting this value will change how many
cells are tracked in each step.

If 'auto' is called with no arguments, a rule is randomly selected from a class of 'interesting' rules to evolve to the next stage
at every step. A single argument is treated as rule number to be evolved. The evolution is carried on for 20 steps. So, using 
		
		./auto 30
		
will result in evolving according to rule 30 for 20 steps. If two arguments are used, the first is treated as the rule number to 
use for evolution and the second is treated as the number of steps to perform. So calling

		./auto 30 100
	
will result in evolving according to rule 30 for 100 steps.
