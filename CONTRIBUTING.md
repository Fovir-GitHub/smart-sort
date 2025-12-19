# Contributing

## Shell (For Windows Developers)

**Do not** use `cmd` or `powershell`, use `Git Bash` instead.

## Repository Setup

0. Clone this repository:

```bash
git clone git@github.com:Fovir-GitHub/smart-sort.git
```

1. Enter the Repository

```bash
cd smart-sort
```

2. Install `pre-commit`

Install [`pre-commit`](https://pre-commit.com/), and run the following command in your shell.

```bash
pre-commit install
```

3. Switch to the `develop` branch.

```bash
git switch develop
```

4. Create a feature branch named `feature/${your-feature}` to add new functions. For example,

```bash
git fetch develop # Ensure the develop branch is updated.
git switch --create feature/sort-algorithm develop
```

5. Implement your feature.

6. Push your branch.

```bash
git push -u origin ${your-branch-name}
```

7. (Optional) Create a fix branch named `fix/${scope}` to fix a function that has been merged into `develop` or `main` branch.

## Commit

Please follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/), and separate your commits properly.

All words in the first line should be lower-case except some variable names.

## Before Push

If there are too many duplicated or unused commits, please **squash** them into one commit.

## After Push

Check the status of `CI`. If it is failed, please fix the problem in your local repository, and **squash** your commits since they have not being merged into `develop` or `main` branch yet.

## Code Format

All `C/C++` code format should follow [`.clang-format`](https://github.com/Fovir-GitHub/smart-sort/blob/main/.clang-format), which is based on `LLVM` style.

It can be easily achieved by using `clang-format`.

- Use `VSCode`: Install the extension [`xaver.clang-format`](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) after installing `clang-format` on the computer.
- Use `just`: Run `just format` to format all `.cpp` and `.h` files.

## Code Style

The code style should follow [`.clang-tidy`](https://github.com/Fovir-GitHub/smart-sort/blob/main/.clang-tidy).

`pre-commit` will add a hook before you committing changes, which will take a short time to check your code style.

If there are any problems with the code style, the commit will be terminated, then you should correct your code style according to the output.
