{ stdenv, SDL2, libGL }:
stdenv.mkDerivation {
  name = "render-c";
  src = ./.;
  buildInputs = [ SDL2 libGL ];
}
