# eval
Arithmetic Expression Evaluator -- Alan Zhong

This C++ program parses an input string and evaluates the arithmetic expression that it contains according to the order
of operations; this is similar to an eval() function in other programming languages. However, this program only accepts
integer inputs and doesn't support division or exponentiation. 

It works by descending down the order of operations––it finds all parentheses from the innermost to the outermost and then finds
all the products in the parentheses, evaluates them, and then find the addition and subtraction, and evaluates them. This will
ensure that all parentheses are calculated before products, which are calculated before addition and subtraction. 

Syntax:
'+' for addition  
'-' for subtraction  
'*' for multiplication  
'()' for parentheses  
