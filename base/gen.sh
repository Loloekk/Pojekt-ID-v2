#!/bin/bash
g++ -O2 generatorka.cpp -o gen
cat create_only_tabels.sql > create.sql
./gen >> create.sql
cat usterki.sql >> create.sql
rm gen