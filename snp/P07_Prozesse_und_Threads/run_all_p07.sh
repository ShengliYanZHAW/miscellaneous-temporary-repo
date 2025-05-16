#!/usr/bin/env bash
set -e
# Navigate to project root
topdir=$(cd "$(dirname "$0")" && pwd)
echo "Running all P07 exercises in $topdir"

# Task 1
cd "$topdir/work/Prozesse_und_Threads/Aufgabe01"
make
./ProcA1.e > output01.txt

echo "Task 1 output written to Aufgabe01/output01.txt"

# Task 2
cd "$topdir/work/Prozesse_und_Threads/Aufgabe02"
make
# normal run
./ProcA2.e > output02.txt
# rename child executable and capture error
mv ChildProcA2.e ChildProcA2.f || true
./ProcA2.e > output02_renamed.txt 2>&1 || true
mv ChildProcA2.f ChildProcA2.e
# remove execute permission and capture chmod error
chmod -x ChildProcA2.e
./ProcA2.e > output02_noexec.txt 2>&1 || true
chmod +x ChildProcA2.e

echo "Task 2 outputs in Aufgabe02/"

# Task 3
cd "$topdir/work/Prozesse_und_Threads/Aufgabe03"
make
# run and capture hierarchy
./ProcA3.e & child_pid=$!
sleep 1
echo "Shell PID: $$" > tree03.txt
pstree -n -p $$ >> tree03.txt
echo "Task 3 pstree captured in Aufgabe03/tree03.txt"
kill $child_pid || true

# Task 4
cd "$topdir/work/Prozesse_und_Threads/Aufgabe04"
make
./ProcA4.e > output04_run1.txt
./ProcA4.e > output04_run2.txt

echo "Task 4 outputs in Aufgabe04/"

# Task 5
cd "$topdir/work/Prozesse_und_Threads/Aufgabe05"
make
./ProcA5.e & orphan_pid=$!
sleep 1
top -b -n1 | head -n20 > top05.txt
echo "Task 5 top snapshot in Aufgabe05/top05.txt"
kill $orphan_pid || true

# Task 6
cd "$topdir/work/Prozesse_und_Threads/Aufgabe06"
make
echo "Starting aaaa.e for Task6"
./aaaa.e & zombie_pid=$!
# run mtop once (if available)
if command -v mtop >/dev/null 2>&1; then
  mtop aaaa.e --once > mtop06.txt
else
  echo "mtop not found" > mtop06.txt
fi
kill $zombie_pid || true
echo "Task 6 mtop output in Aufgabe06/mtop06.txt"

# Task 7
cd "$topdir/work/Prozesse_und_Threads/Aufgabe07"
make
./ProcA7.e > output07.txt
ulimit -c unlimited
./ProcA7.e 1 > output07_seg.txt 2>&1 || true
echo "Task 7 outputs in Aufgabe07/"

echo "All P07 exercises completed."

# Verification of outputs
echo "\nVerifying all outputs..."
for dir in Aufgabe01 Aufgabe02 Aufgabe03 Aufgabe04 Aufgabe05 Aufgabe06 Aufgabe07; do
  echo "Checking $dir:"
  outdir="$topdir/work/Prozesse_und_Threads/$dir"
  found=false
  for f in "$outdir"/*.txt; do
    if [ -e "$f" ]; then
      found=true
      if [ -s "$f" ]; then
        echo "  ✓ $(basename "$f") is non-empty"
      else
        echo "  ✗ $(basename "$f") is empty"
      fi
    fi
  done
  $found || echo "  ✗ No .txt outputs in $dir"
done
