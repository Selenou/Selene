@echo off
pushd %~dp0\..\
call vendor\bin\premake\premake5.exe clean
popd
::PAUSE