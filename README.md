# badapple-os
![Static Badge](https://img.shields.io/badge/Source_Distribution-None-blue)
[![Static Badge](https://img.shields.io/badge/Youtube%20@WompWomp1234--j6c-red)](https://www.youtube.com/@WompWomp1234-j6c)


i686 PC-AT Bad Apple Operating system based off of the OSDev wiki.

## Requirements
---
* a functional CPU from at least 1997 (to play safe, 2000s or 2010s)
* PC-AT BIOS or CSM

## About
---
I made this project for fun, and as a literal joke. Why not, am i right? Perhaps, it's also a bit of a flex :p 
Also do yall like the badges i just found out you can do this!!!


~~### Why isn't there source code.~~

~~Simple. I lost it. Idk where it is. If you want, uhh you can try to recreate it just see the OSDev wiki following sections:~~
* ~~PIT~~
* ~~Bare bones~~
* ~~Cross-compiler~~
* ~~Building GCC for i686~~

(not the exact names I'm not too sure)


**EDIT**: i found the source code, but i tried to act smart so it's broken cry about it (it was meant for personal use so what do you expect):
In general, what i broke:
* the PIT implementation in genc.py and in extension out.h is completely broken. What it should do: busy poll PIT as hlt is broken-ish in CSM.
* do **NOT** use `__attribute__((interrupt))`. It will not compile.
* You can use this as a fun exercise to fix if you're learning how to do x86_32 PIT i guess

## How to use?
---
Just write the ISO to a CD and boot it. Not that deep bro.

## NOTES

`genc.py`
