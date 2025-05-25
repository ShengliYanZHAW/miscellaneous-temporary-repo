@echo off
REM Batch script to compile and run Collatz calculations

REM Navigate to the script's directory (and where the Java files are)
cd /D "%~dp0"

echo Compiling Java files...
javac CollatzUnoptimized.java
javac CollatzOptimized.java

echo.
echo =====================================================
echo == Running Unoptimized Collatz Calculations ==
echo =====================================================

set inputs_unoptimized=1000 10000 100000 1000000 5000000 10000000

for %%x in (%inputs_unoptimized%) do (
    echo.
    echo --- Unoptimized for x = %%x ---
    java CollatzUnoptimized %%x
)

echo.
echo ===================================================
echo == Running Optimized Collatz Calculations ==
echo ===================================================

set inputs_optimized=1000 10000 100000 1000000 5000000 10000000 90000000

for %%x in (%inputs_optimized%) do (
    echo.
    echo --- Optimized for x = %%x ---
    if "%%x"=="90000000" (
        echo Running with increased heap size (-Xmx4g) for x = 90000000
        java -Xmx4g CollatzOptimized %%x
    ) else (
        java CollatzOptimized %%x
    )
)

echo.
echo All calculations complete.

pause
