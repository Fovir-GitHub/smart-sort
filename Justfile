build-dir := "build"

suffix := if os() == "windows" {".exe"} else {""}

fb:
  # Fast build if Makefile exists.
  cmake --build {{build-dir}}

build:
  # Generate Makefile and build.
  cmake -S . -B {{build-dir}}
  just fb

run:
  # Run the program.
  {{"./build/src/smart-sort" + suffix}}

test:
  # Run tests.
  {{"./build/tests/tests" + suffix}}

gc:
  # Prune build caches.
  rm -rf {{build-dir}} .cache/ Testing/

format:
  # Format code.
  find src tests -type f \( -name "*.cpp" -o -name "*.h" \) -print0 | xargs -0 clang-format -i

tidy:
  # Run clang-tidy
  ./scripts/run-tidy.sh
