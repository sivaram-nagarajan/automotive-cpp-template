# Changelog

All notable changes are documented here. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and the project uses
[Semantic Versioning](https://semver.org/).

## [Unreleased]

## [0.1.0] - 2026-11-10
### Added
- CMake build for C11 and C++17 with a strict warning set.
- CRC-8 SAE J1850 module with an AUTOSAR-compatible interface.
- `StaticRingBuffer`, a heap-free FIFO for embedded C++.
- GoogleTest unit tests, MISRA C:2012 checks (cppcheck), clang-tidy, coverage.
- Requirement-to-test traceability check (`tools/trace.py`).
