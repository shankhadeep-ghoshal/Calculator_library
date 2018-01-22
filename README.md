# Infix to Postfix Conversion & Postfix Evaluation



## Intro

C++ program that parses **Infix Notation** (usual mathematical expressions) to **Reverse Polish Notation** (Postfix notation) and then evaluates it.

### Examples of Infix Conversion to Postfix  

- **Infix** : 2+3*6  **|**  **Postfix** : 2 3 6 * +  
- **Infix** : (2+3)*6  **|** **Postfix** : 2 3 + 6 *  
- **Infix** : (-2-3)6  **|** **Sanitized Infix** : (0 -2 - 3) * 6  



## Supported mathematical operations 

- _Addition_ 
- _Subtraction_ 
- _Multiplication_
- _Division_
- _Absolute Value (denoted by the symbol **m**)_
- _Square Root (denoted by the symbol **t**)_ 
- _Sin, Cos, Tan (denoted by symbols **s**,  **c** and **t** respectively)_
- _Power (denoted by the symbol  **^**)_
- _Modulus_   


## Usage

- Create an instance of `InfixCalculator` which takes in the Infix string as a parameter 
- Call method `evalPostfix()` which return evaluated Postfix as  `string` 



## Possible Improvements 

- Postfix value can be stored as a `List<String>` (depiction and not actual syntax) instead of a `string` 



## Bugs 

- Trigonometric values of negative numbers are not properly evaluated (that's what I think).  

## Additional Note
The code doesn't cover all the edge cases and it for the one using this library to find out what edge cases are missing.  



## Acknowledgements  
- Sergei Lebedev (Data Structures and Algorithms lab in-charge)
- [Introduction to Alorithms, CLRS , MIT Press](https://mitpress.mit.edu/books/introduction-algorithms)
- Heineken Lager Beer


