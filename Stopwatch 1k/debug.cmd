@echo off

if exist "stopwatch.obj" del "stopwatch.obj"
if exist "stopwatch.exe" del "stopwatch.exe"

\masm32\bin\ml /c /coff /Flstopwatch.lst "stopwatch.asm" /Zi
if errorlevel 1 goto errasm

\masm32\bin\Link /SUBSYSTEM:WINDOWS "stopwatch.obj" /DEBUG 
if errorlevel 1 goto errlink
dir "stopwatch.*"
goto TheEnd

:errlink
echo _
echo Link error
goto TheEnd

:errasm
echo _
echo Assembly Error
goto TheEnd

:TheEnd

pause
