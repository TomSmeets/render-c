{ stdenv, SDL2 }: 
stdenv.mkDerivation {
  name = "render-c";
  src = ./.;
  buildInputs = [ SDL2 ];
}
