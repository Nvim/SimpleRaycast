{
  description = "Raycasting engine";

  outputs =
    { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };
    in
    {
      # Equivalent to  inputs'.nixpkgs.legacyPackages.hello;
      packages.${system}.default = pkgs.callPackage ./package.nix { };
      devShells.default = self.packages.default;
    };
}
