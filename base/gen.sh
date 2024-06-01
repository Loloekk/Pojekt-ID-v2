#!/bin/bash
g++ -O3 -std=c++17 generatorka.cpp -o gen
cat create_only_tabels.sql > create.sql
./gen >> create.sql
cat usterki.sql >> create.sql
rm gen
