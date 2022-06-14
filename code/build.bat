@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set compilerFlags=-EHsc -W4 -wd4100 -Z7 -std:c++17 /Fe"Winmain.exe"

set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL

cl %compilerFlags% ..\code\*.cpp ..\code\input\*.cpp %linkerFlags% user32.lib d2d1.lib Ole32.lib Shlwapi.lib Dwrite.lib

popd

@REM below are the files to be compiled
@REM ..\code\Winmain.cpp ..\code\Scene.cpp ..\code\input\FireButton.cpp ..\code\Animator.cpp ..\code\Explosion.cpp ..\code\Player.cpp ^
@REM ..\code\Target.cpp ..\code\Projectile.cpp ..\code\Enemy.cpp ..\code\EnemyManager.cpp ..\code\Score.cpp ..\code\Menu.cpp ..\code\input\PauseButton.cpp ^
@REM ..\code\input\StartButton.cpp ^