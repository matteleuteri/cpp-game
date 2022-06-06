@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set compilerFlags=-EHsc -W4 -wd4100 -Z7

set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL

cl %compilerFlags% ..\code\Winmain.cpp ..\code\Scene.cpp ..\code\Animator.cpp ..\code\Player.cpp ..\code\Target.cpp ..\code\Projectile.cpp ..\code\Enemy.cpp ..\code\EnemyManager.cpp ..\code\Menu.cpp %linkerFlags% user32.lib d2d1.lib Ole32.lib

popd