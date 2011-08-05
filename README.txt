This contains the template for the project.

You may add any files you would like.  However,
you should only change the files:

                * * *
{A,B}.{hpp,cpp} are example files.  They can be compiled
with modulegen into .so files.

                * * *

Emitter is a convenience class to help print out the generated
code.  The main things it does is help maintain the indent level,
perform automatic variable substition, and allow use of formats.

The indent level can be incremented by using the increment or
decrement methods directly, or by putting an integer as the first
parameter.  This integer will be added to the current indent
level, causing it to increase or decrease.

Any $$ in the output string will be replaced with the replacement
string supplied in the constructor of the Emitter, or set
with the setReplacement() method.

An emit method ending in F will allow the use of formats.

    int i = 1234;
    emitter.emitLineF("A formatted line: %d.", i);

This would print the line:

    A formatted line: 1234
