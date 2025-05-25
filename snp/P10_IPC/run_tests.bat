@echo off
echo Running tests in WSL...
wsl bash /mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/P10_IPC/run_tests.sh
if %ERRORLEVEL% neq 0 (
    echo Test execution failed with code %ERRORLEVEL%
) else (
    echo Tests completed successfully
)
pause
