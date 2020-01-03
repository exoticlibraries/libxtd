@echo off
if not exist "./build/" ( mkdir .\build\)
make all EXT=.exe