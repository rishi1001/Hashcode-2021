#!/bin/bash

g++ -std=c++17 program.cpp -o program

./program < a.txt > a_out.txt
./program < b.txt > b_out.txt
./program < c.txt > c_out.txt
./program < d.txt > d_out.txt
./program < e.txt > e_out.txt
./program < f.txt > f_out.txt