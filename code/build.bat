@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl /Z7 ..\code\winmaintest.cpp ..\code\Scene.cpp ..\code\Player.cpp /link /INCREMENTAL:NO /DEBUG:FULL user32.lib Gdi32.lib d2d1.lib

popd