{
  lib,
  stdenv,
  SDL2,
}:

stdenv.mkDerivation {
  name = "please-work";
  src = lib.sourceByRegex ./. [
    "^src.*"
    "^include.*"
    "Makefile"
  ];
  nativeBuildInputs = [
    SDL2
    SDL2.dev
  ];

  buildInputs = [
    SDL2
    SDL2.dev
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp ./bin/debug/game $out/bin/
  '';

  doCheck = false;
}
