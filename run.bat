@echo off
color 07

:main
cls
if exist json.exe del json.exe
g++ -Wwrite-strings -Wconversion-null json.cpp -o json.exe
if exist json.exe json.exe
pause
goto:main