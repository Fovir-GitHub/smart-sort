> ~Life is short, stay away from Windows.~

# Reproduce on Windows

## Requirements

1. Install [`CMake`](https://cmake.org/) and add it to `$PATH`.
2. Install [`MSVC`](https://visualstudio.microsoft.com/downloads/) to compile the project.
3. Install [`Python 3.12`](https://www.python.org/downloads/windows/).
4. Install [`Git`](https://git-scm.com/).

Ensure these tools can be reached by your `PowerShell`. Once this step is done, launch your `PowerShell` and continue with this guide.

## Set up the Repository

1. Clone and enter the repository.

```ps1
git clone https://github.com/Fovir-GitHub/smart-sort.git
cd smart-sort
```

2. Create `Python` virtual environment and activate it.

```ps1
python -m venv .venv
```

Before activating the virtual environment, the `PowerShell` should be enabled to run scripts by running the following command, and enter `Y` after executing the command.

```ps1
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
```

Then, activate the virtual environment with this command:

```ps1
.\.venv\Scripts\Activate.ps1
```

As the command line shows following content, this step is done successfully.

```ps1
(.venv) PS C:\Users\path\to\project>
```

3. Download Python dependencies.

This project uses `poetry` to manage Python dependencies to ensure the reproducibility. So you need to install it at first.

```ps1
pip install poetry
```

Then, run the following commands to install dependencies.

```ps1
cd .\MLmodel\
poetry install --no-root
```

Once dependencies are installed, step back to the root directory of the project with

```ps1
cd ..
```

To verify all dependencies are installed properly, run this command:

```ps1
python .\MLmodel\predict_api.py "[1,2,3]" 1
```

The expected output is an integer without errors or warnings.

4. Build the main program.

This project uses `CMake` as the build tool. So we need to generate `CMake` configuration before compiling the project.

```ps1
cmake -S . -B build `
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake `
  -DVCPKG_TARGET_TRIPLET=x64-windows `
  -Dgtest_disable_pthreads=ON `
  -Dgtest_force_shared_crt=ON `
  -DCMAKE_CXX_FLAGS="/EHsc /DGTEST_HAS_PTHREAD=0 /DGTEST_OS_WINDOWS=1"
```

Then, compile the project.

```ps1
cmake --build build --config Release
```

5. Execute the main program.

```ps1
.\build\src\Release\smart-sort.exe
```
