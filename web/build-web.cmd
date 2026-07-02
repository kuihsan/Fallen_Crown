@echo off
setlocal
call D:\Fallen_Crown\emsdk\emsdk_env.bat >nul 2>&1
if not defined SFML_EMSCRIPTEN (
  echo Set SFML_EMSCRIPTEN to the folder containing your Emscripten-built SFML install.
  exit /b 1
)

if not exist "%SFML_EMSCRIPTEN%\include\SFML" (
  echo SFML include directory not found at %SFML_EMSCRIPTEN%\include.
  exit /b 1
)

if not exist "%SFML_EMSCRIPTEN%\lib" (
  echo SFML lib directory not found at %SFML_EMSCRIPTEN%\lib.
  exit /b 1
)

if not exist web\assets mkdir web\assets
xcopy /E /I /Y D:\Fallen_Crown\Image web\assets\Image >nul
xcopy /E /I /Y D:\Fallen_Crown\fonts web\assets\fonts >nul
xcopy /E /I /Y D:\Fallen_Crown\sound web\assets\sound >nul

e++ -O2 D:\Fallen_Crown\coding\*.cpp -I D:\Fallen_Crown\src\include -I "%SFML_EMSCRIPTEN%\include" -L "%SFML_EMSCRIPTEN%\lib" -s USE_SDL=2 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 --preload-file D:\Fallen_Crown\web\assets@/assets -o D:\Fallen_Crown\web\main.js
if errorlevel 1 exit /b %errorlevel%

echo Build complete. Open D:\Fallen_Crown\web\index.html in a browser or run serve.cmd.
