# Project Test Suite: Arithmetic Expression Evaluator

## Valid Expression Tests
These cases verify correct calculation based on PEMDAS and operator associativity rules.

| ID | Description | Input | Expected Output | Rule Verified |
|:---|:---|:---|:---|:---|
| TC-VAL-01 | Basic Addition | `3 + 4` | `7` |Addition|
| TC-VAL-02 | Subtraction Precedence | `8 - (5 - 2)` | `5` |Parentheses|
| TC-VAL-03 | L-to-R Associativity | `10 * 2 / 5` | `4` |`*` and `/`|
| TC-VAL-04 | Exponentiation | `2 ** 3` | `8` |`**` operator|
| TC-VAL-05 | Mixed Operators | `4 * (3 + 2) % 7 - 1` | `5` |Full PEMDAS|
| TC-VAL-08 | Nested Exponents | `(((2**(1+1))+((3-1)**2))/((4/2)%3))` | `4` |Complex nesting|
| TC-VAL-11 | Unary & Arithmetic | `+(-2) * (-3) - ((-4) / (+5))` | `6.8` |Unary +/-|
| TC-VAL-14 | Unary Exponentiation | `+2 ** (-3)` | `0.125` |Right-to-Left `**`|

## Invalid Expression Tests
These cases ensure the program provides robust error handling for mathematically undefined or poorly formatted input.

| ID | Description | Input | Expected Error Message |
|:---|:---|:---|:---|
| TC-INV-01 | Unmatched Parentheses | `2 * (4 + 3 - 1` |`Error: Missing closing parenthesis`|
| TC-INV-02 | Missing Operands | `* 5 + 2` |`Error: Invalid expression`|
| TC-INV-03 | Division by Zero | `4 / 0` |`Error: Division by zero`|
| TC-INV-04 | Missing Operator | `5 (2 + 3)` |`Error: Invalid expression`|
| TC-INV-05 | Invalid Characters | `7 & 3` |`Error: Unexpected characters`|
| TC-INV-10 | Unsupported Symbols | `((7 * 3) ^ 2)` |`Error: Missing closing parenthesis` (due to `^`)|