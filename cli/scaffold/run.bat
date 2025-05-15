@echo off
@REM for /f "tokens=2 delims==." %%a in ('wmic cpu get NumberOfLogicalProcessors /value ^| find "="') do set cores=%%a
@REM set /a half_cores=(cores + 1) / 2
call cmake --build build -- -j 6
call .\build\framework-demo.exe