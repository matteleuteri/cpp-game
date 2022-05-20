@echo off


IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl ..\code\winmaintest.cpp ..\code\Scene.cpp user32.lib Gdi32.lib

popd

..\build\winmaintest.exe