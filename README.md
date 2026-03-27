# ctype

`ctype` is a wrapper around POSIX C's `ctype.h`.
It can print the types or determine whether a char belongs to a type.

The current locale is respected.

`ctype.pl` is an equivalent Perl implementation.
It has the protability upside of not requiring a compile,
but comes with the downside of depending on `FFI::Platypus`
and the off-chance of exploding under esoteric clib versions.
Choose your poison.
