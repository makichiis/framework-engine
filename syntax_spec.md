# Framework Engine Syntax Specification (WIP)
This document outlines the general syntactical and semantic structure of the Framework Engine. This is here to keep development streamlined with minimal tech debt.

## Naming
The names of symbols should always be intuitive and make the intention/structure of a symbol clear. Additionally, name of a variable should not concern itself with code/functionality with which such  variable will be used by (e.g., `add(x, y)` suffices and naming `x` as  `left_hand_side_operand_of_an_add_call` is not necessary).

Variable and parameter names may contain abbreviations that would be intuitive or straightforward for a typical programmer. Some examples include:
- `obj` - short for "Object" (not to confuse with `.obj` model files).
- `i/j/k` - a common series of unary symbols which denote levels of nested iteration/looping.
- `ctor` - an abbreviation of "constructor".
- `tmp` - an abbreviation of "temporary", often used to store temporary states or memory buffers.
- `buf` - similar to `tmp`, but is short for "buffer".
- `sz` - abbrevation of "size".

Avoid using abbreviations that would __only__ be intuitive to an esoteric demographic, particularly ones that only make sense to developers which already actively contribute to Framework (e.g., "`rms`" for the Resource Management System. You know who you are.).

> Note: Avoid usage of [Hungarian notation](https://en.wikipedia.org/wiki/Hungarian_notation) 

### Namespaces
Namespaces are written as mnemonics in lowercase (e.g. `std` = `standard library`). The top-level Framework Engine namespace is specified as `fe`.

###  Classes and Class Members

- Class names - Class names follow `PascalCase` naming syntax. The base Framework object is defined at `fe::Object`.
- Public class functions - Class functions accessed by the end user follow `PascalCase` naming  syntax. This is intentional to make syntax more intuitive to beginner-level developers. 
- Public class attributes - Class attributes which are intended to be interfaced follow `snake_case` naming syntax.
- Private class members - Class members (attributes and functions) which are  internal should follow `snake_case_underscore_postfix_` naming. E.g., the allocator within `fe::ResourceManager` is `fe::ResourceManager::alloc_`.

### Global Functions
Functions which are global should follow `snake_case` syntax to distinguish them from class functions.

```cpp
void SomeBadlyNamedFunction() {...}
void some_goodly_named_function() {...}

class SomeObject : public fe::Object {
public:
    using Object::Object;

    void OnEvent(fe::Event& event) {
        SomeBadlyNamedFunction(); // whether this is a class function or a global one isnt clear.
        some_goodly_named_function(); // very good.
    }
} 
```

### Variables
Similarly to class attributes, variables -- both const and non-const --  should follow `snake_case` naming syntax. 

### Compile-Time Constants and Macros
Compile-time constants (`constexpr`) and C macros defined in the Framework Engine core should follow `SNAKE_UPPER_CASE` naming syntax. 

### Metaprogramming Symbols
#### Template Parameters
Template parameters that belong to generic containers may follow unary-letter syntax (e.g. `std::vector<T>`). Templates which have a specific purpose may express their intention/functionality using a name with `PascalCase` syntax (e.g. `fe::ResourceManager<Allocator>`).

#### Static assertions 
Static assertions prevent generation of templates containing invalid  type parameters. Static assertions should be made using the `requires` keyword following the signature of a method. 

Types with restrictive type parameters may use `concept`s to define static-time assertions. Because `concept`s are treatedly similarly (semantically) to types, they should also follow class naming syntax.

Examples:
```cpp
class Object {
public:
    template <class T, class... Args>
    T* AddChild(Args&&... ctor_args) requires (std::is_base_of_v<Object, T>) {
        return resource_manager->CreateObject<T>(
            std::forward<Args>(ctor_args)...);
    }
};
```

```cpp
template <class T>
concept ObjectType = std::is_base_of_v<Object, T>;

template <ObjectType T>
class ObjectList {
    T* elems; 
    // ...
};
```

## Code Formatting 

### Indentation Style 

In C++ and other C-derived languages, curly braces denote the beginning and end of a nested block of code. The leading curly brace of a block code should be on the same line as the last character of the function signature/ condition clause which precedes it. Conditional statements and loops with only one statement do not require curly braces. Conditional statements and loops which do not exceeds 80 characters may be entirely one-line. This is a modification of *K&R indentation*.

```cpp
#include <iostream>

int main() {
    int input;
    std::cout << "Enter a number: ";
    std::cin >> input;
    
    while (input > 10) {
        std::cout << "Pick a number below 10: ";
        std::cin >> input;
    }

    if (input < 0)
        std::cout << "A negative number was a statistically likely result...";
    else std::cout << "A positive number. Huh.";

    std::endl(std::cout);
}
```

#### Spacing
In general, every line of code must be indented with whitespace in multiples of  four. Most editors apply this via `TAB` (or allow you to make it do as such).



> Exceptions may apply when the readability of a line of code benefits from
line breakage and mid-line alignments (particularly with builder patterns), e.g.:
> ```cpp
> std::cout << "Size of object:     " << sizeof *obj << '\n'
>           << "Size of object.foo: " << sizeof obj->foo << '\n';
> ```

All operands and operators should be separated by exactly one whitespace. Comma-delimited lists may be right-padded and surrounded by a single whitespace on each end.

Examples:
```cpp
int x = 5; // Note variable decl spacing, also.
int y = 2;
int z = x + y;
int nums[3] = { x, y, z };
```
