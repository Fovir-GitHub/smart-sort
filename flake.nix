{
  description = "DevShell for C/C++";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};

    clangdConfig = pkgs.writeText ".clangd" ''
      CompileFlags:
        Add:
          - -isystem${pkgs.libcxx.dev}/include/c++/v1
          - -std=c++20
    '';
  in {
    devShells.${system}.default = pkgs.mkShell {
      # Add packages here.
      buildInputs = with pkgs; [
        bear
        cgdb
        clang-tools
        cmake
        gdb
        gnumake
        libcxx
      ];

      # Shell hooks.
      shellHook = ''
        echo "Entering the development environment!"
        cp ${clangdConfig} .clangd
      '';
    };
  };
}
