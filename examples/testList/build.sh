#!/bin/bash
INCLUDE_PATH=/workSpace/myRebuildList/BaseLib/include


#gcc -I $(INCLUDE_PATH) test_list.c -o test_list
gcc -I /workSpace/baseLib/include test_list.c -o test_list
