# LLN_calculator_guisan

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/316218e3af4d4329b03fcc1e4ec98171)](https://www.codacy.com/app/mythsman/LLN_calculator_guisan?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mythsman/LLN_calculator_guisan&amp;utm_campaign=Badge_Grade)
[![GitHub license](https://img.shields.io/github/license/mythsman/LLN_calculator_guisan.svg)](https://github.com/mythsman/LLN_calculator_guisan/blob/master/LICENSE)

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

	E-->E+T|E-T|T
	T-->N*T|N/T|N
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


