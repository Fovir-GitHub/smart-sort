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
          - -isystem${pkgs.glibc.dev}/include
          - -isystem${pkgs.gtest.dev}/include
          - -std=c++20
    '';
  in {
    devShells.${system}.default = pkgs.mkShell {
      # Add packages here.
      buildInputs = with pkgs; [
        cgdb
        clang-tools
        cmake
        gcc
        gdb
        gnumake
        gtest
        just
      ];

      # Shell hooks.
      shellHook = ''
        echo "Entering the development environment!"
        ln -sf ${clangdConfig} .clangd
      '';
    };
  };
}
