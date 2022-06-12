@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set compilerFlags=-EHsc -W4 -wd4100 -Z7 -std:c++17

set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL

cl %compilerFlags% ..\code\Winmain.cpp ..\code\Scene.cpp ..\code\FireButton.cpp ..\code\Animator.cpp ..\code\Explosion.cpp ..\code\Player.cpp ^
            ..\code\Target.cpp ..\code\Projectile.cpp ..\code\Enemy.cpp ..\code\EnemyManager.cpp ..\code\Score.cpp ..\code\Menu.cpp ../code/PauseButton.cpp ^
            %linkerFlags% user32.lib d2d1.lib Ole32.lib Shlwapi.lib

popd