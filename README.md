# Projecty

A small C++23 project built with Xmake and Docker.

## Requirements

- Git
- Docker Desktop on Windows/macOS, or Docker Engine on Linux

No local C++ compiler or Xmake installation is required.

## Getting started

Clone the repository:

```bash
git clone https://github.com/almeidaorville7-lang/projecty.git
cd projecty
```

Build the project:

```bash
docker build -t projecty .
```

Run the project:

```bash
docker run --rm projecty
```

Rebuild the Docker image after modifying the source code.

## Local development

For contributors who already have Xmake and a compatible C++23 compiler:

```bash
xmake
xmake run projecty
```

## Contributing

1. Create a feature branch.
2. Make your changes.
3. Verify the Docker build succeeds.
4. Open a pull request against `main`.

Do not commit generated build files or compiled executables.