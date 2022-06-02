@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set compilerFlags = /Z7 /EHsc

set linkerFlags = /link /INCREMENTAL:NO /DEBUG:FULL

cl %compilerFlags% ..\code\winmaintest.cpp ..\code\Scene.cpp ..\code\Player.cpp ..\code\Projectile.cpp %linkerFlags% user32.lib d2d1.lib Ole32.lib

popd