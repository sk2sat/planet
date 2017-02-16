#!/bin/sh
rm out/out00000.*
#make run
./render.py out%05d.pov 0 1 1
