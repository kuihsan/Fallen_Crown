Desktop build:
mingw32-make -f MakeFile
copy & paste to terminal to compile exe

Windows web setup:
1. Open PowerShell in the project root.
2. Clone the Emscripten SDK if you do not already have it:
   git clone https://github.com/emscripten-core/emsdk.git
3. Install and activate the toolchain:
   cd .\emsdk
   .\emsdk.bat install latest
   .\emsdk.bat activate latest
4. Build or install an SFML version for Emscripten and point the build script at it:
   $env:SFML_EMSCRIPTEN = "C:\path\to\emscripten-sfml"
5. Build the web version:
   .\web\build-web.cmd
6. Serve the generated files locally:
   .\web\serve.cmd

What changed for the web build:
- The game now uses asset-path resolution that can work from a packaged web bundle.
- Highscores are stored in browser localStorage when built for Emscripten.
- A basic browser shell is available in web/index.html.
- The build script expects an Emscripten-enabled SFML installation and produces a browser build in web/.
