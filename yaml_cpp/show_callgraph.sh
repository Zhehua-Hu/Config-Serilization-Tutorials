#!/usr/bin/env bash

rm callgrind.out.*
valgrind --tool=callgrind ./bin/main

# Use gprof2dot
gprof2dot.py -f callgrind callgrind.out.* -n5 -e0 -s -w | xdot

# kcachegrind
#kcachegrind callgrind.out.*

echo "________________________"
echo "Done!"

