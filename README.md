_This project has been created as part of the 42 curriculum by fmesci._

# ft_printf

## Description

`ft_printf` is a re-implementation of the C standard library function `printf()`.
The goal of the project is to learn how **variadic functions** work in C
(`va_list`, `va_start`, `va_arg`, `va_end`) and to write a well-structured,
extensible piece of code that can later be reused in other projects.

The result is a static library, `libftprintf.a`, exposing:

```c
int	ft_printf(char const *format, ...);
```

It returns the number of characters written, like the original `printf()`.
The buffer management of the original `printf()` is **not** implemented:
everything is written directly with `write()`.

### Supported conversions

| Specifier | Output                                       |
| --------- | -------------------------------------------- |
| `%c`      | A single character                           |
| `%s`      | A string (`(null)` if the pointer is `NULL`) |
| `%p`      | A `void *` pointer in hexadecimal (`0x...`)  |
| `%d`      | A signed decimal number (base 10)            |
| `%i`      | A signed integer (base 10)                   |
| `%u`      | An unsigned decimal number (base 10)         |
| `%x`      | An unsigned number in lowercase hexadecimal  |
| `%X`      | An unsigned number in uppercase hexadecimal  |
| `%%`      | A percent sign                               |

### Project structure

| File                  | Content                                                                            |
| --------------------- | ---------------------------------------------------------------------------------- |
| `ft_printf.h`         | Prototypes and includes                                                            |
| `ft_printf.c`         | `ft_printf()` (format parsing) and `check_format()` (dispatcher)                   |
| `ft_printf_utils.c`   | `ft_putchar`, `ft_print_char`, `ft_print_str`, `ft_print_nbr`, `ft_print_unsigned` |
| `ft_printf_utils_2.c` | `ft_print_hex`, `ft_print_ptr`                                                     |
| `Makefile`            | Builds `libftprintf.a`                                                             |

## Instructions

### Compilation

```sh
make        # builds libftprintf.a in the root of the repository
make clean  # removes the object files
make fclean # removes the object files and libftprintf.a
make re     # fclean + all
```

The library is compiled with `cc -Wall -Wextra -Werror` and archived with `ar rcs`.
The Makefile does not relink if nothing has changed.

### Usage

Write a program that includes the header and link it with the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = ft_printf("Hello %s, you are %d years old. Hex: %x\n", "42", 30, 255);
	ft_printf("Characters written: %d\n", n);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

## Algorithm and data structures

**Parsing.** `ft_printf()` walks the format string once with an index.
Every character that is not `%` is written directly with `write()` and counted.
When a `%` is found, the next character is the specifier and it is delegated
to `check_format()`. The `%` and its specifier are consumed together. If the
string ends right after a `%`, nothing more is read, so the function never
goes past the terminating `'\0'`.

**Dispatching.** `check_format()` is a chain of `if / else if` that maps each
specifier to its printing function and returns how many characters it wrote.
`ft_printf()` simply accumulates those values into the final return count.
A chain of `if` was chosen because the `switch` statement is forbidden by the Norm,
and it keeps each function short and readable. It is also easy to extend: adding a new
conversion only needs a new printing function and one new branch.

**Variadic arguments.** The `va_list` is created in `ft_printf()` and passed to
`check_format()` **by pointer** (`va_list *`). This way each `va_arg()` call
advances the same list, instead of working on a copy.

**Number printing (recursion, no buffers).** `ft_print_nbr`, `ft_print_unsigned`
and `ft_print_hex` use recursion: the number is divided by the base until
it fits in one digit, and then the digits are written on the way back, which gives
them in the correct order without allocating memory or reversing a string.

- `ft_print_nbr` stores the value in a `long` so that `INT_MIN` can be negated
  without overflow.
- `ft_print_hex` selects the digit set (`0123456789abcdef` or
  `0123456789ABCDEF`) depending on the specifier.
- `ft_print_ptr` casts the pointer to `unsigned long`, prints `0x` and then the
  address in lowercase hexadecimal.

**Memory.** No dynamic memory is used, so there are no leaks possible.

### Technical decisions

- `%p` with a `NULL` pointer prints `(nil)`, which is the behaviour of glibc
  (Linux). macOS prints `0x0`. The subject does not define this case.
- An incomplete conversion (a `%` at the end of the string) and unknown
  specifiers are undefined behaviour in the original `printf()`. Here, a
  trailing `%` prints nothing and an unknown specifier prints nothing either.

## Resources

- `man 3 printf`, `man 3 stdarg`, `man 2 write`, `man ar`
- [GNU C Library manual: Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)
- [cppreference: `printf` family and format specifiers](https://en.cppreference.com/w/c/io/fprintf)
- The 42 Norm and the `ft_printf` subject (version 12.0)

### Use of AI

AI was used as a tutor and reviewer, **not** to write the
implementation:

- Reviewing the code against the subject and the Norm.
- Running comparison tests against the original `printf()` with
  AddressSanitizer / UBSan.
- Detecting edge cases (a trailing `%`, a possible `NULL` dereference in
  `ft_print_hex`) and guiding the fixes with hints.
- Drafting this README.

The code was written, fixed and understood by the author.
