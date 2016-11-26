# LLN_calculator_guisan

## Introduction
A simple calculator with guisan and LL grammar.

## Runtime requirements
* SDL 2.0+
* SDL2_image
* SDL2_ttf
* SDL2_mixer
* Guisan(built-in)

## LL Grammar

Raw Grammar:

	E-->E+T|E-T|void
	T-->N*T|N/T|void
	N-->M^N|M
	M-->(E)
	   |sin(E)
	   |cos(E)
	   |ln(E)
	   |lg(E)
	   |sqrt(E)
	   |tan(E)
	   |number

Eliminate the left recursion:

	E-->Te
	e-->+Te|-Te|void
	T-->Nt
	t-->*Nt|/Nt|void
	N-->Mn
	n-->^N|void
	M-->(E)
	   |sin(E)
	   |cos(E)
	   |ln(E)
	   |lg(E)
	   |sqrt(E)
	   |tan(E)
	   |number


