# Reproduce with NixOS

> **Gentle Reminder:** This project uses `flake`, please enable this feature in your configuration.

1. Clone and enter the repository.

```bash
git clone https://github.com/Fovir-GitHub/smart-sort.git && cd smart-sort
```

2. Enter the dev shell:

```bash
nix develop # Without `direnv`
direnv allow # With `direnv`
```

3. Build the project:

```bash
just build
```

4. Run the program:

```bash
just run
```
