@echo off

if exist "%1.obj" del "%1.obj"
if exist "%1.exe" del "%1.exe"

\masm32\bin\ml /c /coff /Fl%1.lst "%1.asm" /Zi
if errorlevel 1 goto errasm

\masm32\bin\Link /SUBSYSTEM:WINDOWS /ALIGN:4 /OPT:NOWIN98 "%1.obj" /MERGE:.rdata=.text /STUB:newstub.txt /DEBUG 
if errorlevel 1 goto errlink
dir "%1.*"
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
