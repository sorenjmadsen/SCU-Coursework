/*
 * File:	machine.h
 *
 * Description:	This file contains the values of various parameters for the
 *		target machine architecture.
 */

# define SIZEOF_CHAR 1
# define SIZEOF_INT 4
# define SIZEOF_PTR 4
# define SIZEOF_REG 4
# define SIZEOF_ARG 4

# if defined (__linux__) && (defined(__i386__) || defined(__x86_64__))

# define STACK_ALIGNMENT 4
# define global_prefix ""
# define label_prefix ".L"

# elif defined (__APPLE__) && (defined(__i386__) || defined(__x86_64__))

# define STACK_ALIGNMENT 16
# define global_prefix "_"
# define label_prefix "L"

# else

# error Unsupport architecture
# endif
