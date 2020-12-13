#!/bin/bash
rm outfile
g++ -o ga *.cpp -I. -lm
./ga
python gagraph.py