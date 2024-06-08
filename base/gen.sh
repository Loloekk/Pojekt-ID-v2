#!/bin/bash
 g++ -O3 -std=c++17 generatorka.cpp -o gen
echo ----------------------tabels > create.sql
 echo >> create.sql
 echo >> create.sql
cat create_only_tabels.sql >> create.sql
 echo >> create.sql
 echo >> create.sql
echo ----------------------data >> create.sql
 echo >> create.sql
 echo >> create.sql
 ./gen >> create.sql
cat usterki.sql >> create.sql
 echo >> create.sql
 echo >> create.sql
echo ----------------------functions >> create.sql
 echo >> create.sql
 echo >> create.sql
./functions/gen_functions.sh >> create.sql
 echo >> create.sql
 echo >> create.sql
echo ----------------------trigers >> create.sql
 echo >> create.sql
 echo >> create.sql
./triggers/gen_triggers.sh >> create.sql
 echo >> create.sql
 echo >> create.sql
echo ----------------------rules >> create.sql
 echo >> create.sql
 echo >> create.sql
./rules/gen_rules.sh >> create.sql
 rm gen
