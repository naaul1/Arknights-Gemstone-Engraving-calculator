# Arknights-Gemstone-Engraving-calculator
A calculator tool made for the minigame of Arknights' Pepe event. Codes are packed into one file for easier online compiling.

## How to run
#### If you have a C++ compiler:
- You know how.
#### If not:
- Go to [onlinegdb.com](onlinegdb.com)
- Choose "C++" as your language.
- Enter the content of "main.cpp" into the editor.
- Profit.

## How to use
- Cards (or techniques) of each color are notated as "\<color\>\<tier\>", where color is in {Red, Teal, Purple, Gold}, and tier is the tier of the product.<br>
E.g., 'RED' card that produces 'Tier1' red gem is notated as "r1".
- Upon a new round, you should initialize your materials with "newround", set your cards with "setred"/"setteal"/"setpurple"/"setgold" or with "setmin"/"setmax".<br>
You can then test your card combination using "try", and add the result to the cumulative score with "submit".
- You could also "setscore" (if you lost track of it), or "setbenches" (if you're going to use r4).
