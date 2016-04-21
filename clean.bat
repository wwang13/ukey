@echo off
setlocal
call "%VS120COMNTOOLS%vsvars32.bat
MSBUILD UKEY.sln /t:Clean /p:Configuration=Debug
MSBUILD UKEY.sln /t:Clean /p:Configuration=Release

RD /S /Q  Generater\Debug
RD /S /Q  Generater\Release
    
RD /S /Q  PrivateKey\Debug
RD /S /Q  PrivateKey\Release

RD /S /Q  PublicKey\Debug
RD /S /Q  PublicKey\Release

exit /b %ERRORLEVEL%
endlocal
pause