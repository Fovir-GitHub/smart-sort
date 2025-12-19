# Smart Sort

This repository stores the source code of **SmartSort**, including
the core implementation with C++ and a machine-learning–based sorting model.

## Pre-requirement

### System Toolchain (for native build)

| Tool       | Version  |
| ---------- | -------- |
| `CMake`    | `4.1.2`  |
| `GNU Make` | `4.4.1`  |
| `g++`      | `14.3.0` |

### Python Environment (for ML model)

The machine learning components are implemented in Python.
For **reproducibility**, we use **Conda + Poetry** to manage dependencies.

#### Required

- **OS**: Windows / Linux / macOS  
- **Python**: `3.12` (other versions are not guaranteed to work)
- **Conda** (recommended)
- **Poetry**

---

## Setup Instructions

### 1. Clone the repository

```bash
git clone https://github.com/yourname/SmartSort.git
cd SmartSort
```

### 2. Create and activate Conda environment

```bash
conda create -n SmartSort python=3.12 -y
conda activate SmartSort
```

### 3. Install Poetry

If Poetry is not installed:
```bash
pip install poetry
```

Verify:
```bash
poetry --version
```

### 4. Install Python dependencies (reproducible)
```bash
poetry install
```

This installs exact dependency versions defined in poetry.lock.

### 5. Verify installation (optional)
```bash
python -c "import import numpy; import sklearn; import xgboost; print("numpy:", numpy.__version__); print("sklearn:", sklearn.__version__); print("xgboost:", xgboost.__version__)"
```

Expected output:
```text
numpy: 2.3.5
sklearn: 1.7.1
xgboost: 3.1.2
```

## Usage
Run ML prediction example
```bash
python ./MLmodel/predict_api.py "[1,2,3]" 1
```

## Notes on Reproducibility

pyproject.toml and poetry.lock are the source of truth for Python dependencies.
requirements.txt (if present) is provided for reference only.
Please install dependencies using poetry install to avoid version mismatches.
**Mandatory**:

| Tool                                             | Version  |
| ------------------------------------------------ | -------- |
| [`CMake`](https://cmake.org/)                    | `4.1.2`  |
| [`GNU Make`](https://www.gnu.org/software/make/) | `4.4.1`  |
| [`clang-format`](https://llvm.org/builds/)       | `21.1.2` |
| [`clang-tidy`](https://llvm.org/builds/)         | `21.1.2` |
| [`g++`](https://gcc.gnu.org/)                    | `14.3.0` |
| [`git`](https://git-scm.com/)                    | `2.51.2` |
| [`pre-commit`](https://pre-commit.com/)          | `4.3.0`  |

_Optional_ but **recommend**:

- [`just`](https://just.systems/): Providing a handy way to save and run project-specific commands.
- [`gdb`](https://sourceware.org/gdb/) or [`cgdb`](https://cgdb.github.io/): Debugger.

## Development

Install all required tools above.

Then follow the [CONTRIBUTING.md](https://github.com/Fovir-GitHub/smart-sort?tab=contributing-ov-file).
