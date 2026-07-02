param(
  [string]$SfmlRoot = $env:SFML_EMSCRIPTEN
)

if (-not (Get-Command em++ -ErrorAction SilentlyContinue)) {
  Write-Error "em++ was not found. Install Emscripten first.";
  exit 1
}

if (-not $SfmlRoot) {
  Write-Error "Set SFML_EMSCRIPTEN to the root of your Emscripten-built SFML installation.";
  exit 1
}

$projectRoot = Resolve-Path ".."
$webRoot = Resolve-Path "."

New-Item -ItemType Directory -Force -Path "$webRoot/assets" | Out-Null
Copy-Item "$projectRoot/Image" -Destination "$webRoot/assets" -Recurse -Force
Copy-Item "$projectRoot/fonts" -Destination "$webRoot/assets" -Recurse -Force
Copy-Item "$projectRoot/sound" -Destination "$webRoot/assets" -Recurse -Force

em++ `
  "$projectRoot/coding"/*.cpp `
  -I "$projectRoot/src/include" `
  -I "$SfmlRoot/include" `
  -L "$SfmlRoot/lib" `
  -s USE_SDL=2 `
  -s FULL_ES3=1 `
  -s ALLOW_MEMORY_GROWTH=1 `
  -s FORCE_FILESYSTEM=1 `
  --preload-file "$webRoot/assets@/assets" `
  -o "$webRoot/main.js"
