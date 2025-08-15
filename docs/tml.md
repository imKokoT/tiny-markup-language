# TML standard v1.0

- [Base Syntax](#base-syntax)
    - [Comments](#comments)
    - [Variable definition](#variable-definition)
    - [Indentation](#indentation)
    - [Semi](#semi)
- [Data types](#data-types)
    - [String](#string)
    - [Object](#object)
    - [List](#list)

## Base Syntax

The syntax mostly inspired by [YAML](https://yaml.org) and [JSON](https://www.json.org/json-en.html), but the main point is to make it more easier to understand, use a stricter format. Other important point is serialized data length: as shorter as possible, while maintaining human-readability.

The **root object** from variant of [data types](#data-types) detects by entry syntax. Entry syntax for [*Object*](#object) simplified:
```tml
a = 123
b = the fast brown fox jumps over the lazy dog.

# same as
# {
#   a = 123
#   b = the fast brown fox jumps over the lazy dog.
# } 
```

### Comments

Comments starts from '#' symbol. If '#' found, all next symbols will be ignored.
Example:
```tml
var = 'abc' # the comment
```

### Variable definition

Variable can be defined at [*Object*](#object) with next syntax: `[name]=[value]`

Example:
```tml
a = 123
```

Variable name can contain ASCII English symbols (`a-z` and `A-Z`), numbers (`0-9`) and `-`, `_`, `.` symbols. Variable starts only from alphabet symbols. Variable names case-sensitive, so variable with name `a` and `A`, are different variables.

Example:
```tml
# 'a' and 'A' are different
a = 123 
A = 321

_test = 0    # parse error
0zero = 0    # parse error
-zero = 0    # parse error
ñ = 0        # parse error
```

> [!NOTE]
> Repeating variables is allowed and its value will set by last one

### Indentation

To separate variables between, use newline symbol `\n`. Important to use same indentation for all levels using same symbol of space ` ` or tab `\t`.

### Semi

Variables are separated with newline symbol `\n`, but you can separate with `;`

Example:
```tml
a = 123; b = 321
```


## Data types
- Bool -> boolean type
- Numeric -> numeric type
- Float -> float point type
- String -> string type
- List -> dynamic list
- Object -> object of variables
- Null -> special type; no value  

Example:
```tml
boolean = true       # `false` or `T` or `F`
numeric = 12345.6789 # also possible -.123, 123e10 etc
string = 'string'    # see more in doc about formatting
list = [1,2,3,4,5]
object = {x=0;y=0}
null_type = null     # or nothing
```

### String

String starts and ends from `'` or `"`.
Also TML supports strings without quotes. 

Example:
```tml
a = 'a'
b = "b"
c = "c"
d = d
```

> [!IMPORTANT]
> Strings without quotes will be detected only if it:
> - NOT a reserved word (like `null`, `true` etc)
> - NOT any other type (for example `a = 12345a6` will be a *String* but `a = 12345e6` will be a *Numeric*)
> - NOT break syntax (for example `[abc,def]` *List* will have 2 *Strings*)

TML allows next escape codes:
- `\\` -> `\`
- `\n` -> new line
- `\t` -> tab
- `\"` -> `"`
- `\'` -> `'`
- `\b` -> backspace
- `\v` -> vertical tab
- `\f` -> formfeed
- `\a` -> play sound
- `\r` -> return carry
- `\xff` -> 1 byte char
- `\xffff` -> 2 byte char
- `\e` -> escape code char
- `\,` -> `,`

TML supports multiline *String* syntax but with limitations.

### Object

Object contains variables with values and it dictionary-like. Object has two main formats: **in braces** and **by indentation**.

Example:
```tml
# in braces
vector = {x=0; y=0} # inline
person = {          # multiline, lines separate by newline
    name = Bob
    age = 21
    zip = 43123
}

# by indentation
profile:
    author = John Due
    about = the fast brown fox jumps over the lazy dog.
    timestamp = 1755188070
    mail = example@mail.com
```

> [!IMPORTANT]
> In Object defined by indents, can be defined other inner Objects in `{}` or by indents. But inner Objects defined at root Object by `{}` can be defined only by `{}`

### List

List contains any objects and separate by `,` symbol.

Example:
```tml
list = [
    true, false, T, F, 
    null,, # two commas also null
    123,
    3.14,
    text,
    [1,2,3]
    {x=0,y=0} # only Objects by braces allowed
]
```
