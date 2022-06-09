@echo off

set codePath=C:\Users\meleu\OneDrive\Desktop\robo-spiders-in-space

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set compilerFlags=-EHsc -W4 -wd4100 -Z7
set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL


IF NOT EXIST %codePath%\build mkdir %codePath%\build
pushd %codePath%\build

cl %compilerFlags% %codePath%\code\Winmain.cpp %codePath%\code\Scene.cpp %codePath%\code\FireButton.cpp ^
            %codePath%\code\Animator.cpp %codePath%\code\Explosion.cpp %codePath%\code\Player.cpp ^
            %codePath%\code\Target.cpp %codePath%\code\Projectile.cpp %codePath%\code\Enemy.cpp ^
            %codePath%\code\EnemyManager.cpp %codePath%\code\Menu.cpp ^
    %linkerFlags% user32.lib d2d1.lib Ole32.lib 

popd

call %codePath%\build\Winmain.exe