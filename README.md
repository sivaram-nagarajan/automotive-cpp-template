# automotive-cpp-template

[![CI](https://github.com/sivaram-nagarajan/automotive-cpp-template/actions/workflows/ci.yml/badge.svg)](https://github.com/sivaram-nagarajan/automotive-cpp-template/actions/workflows/ci.yml)

A starting point for automotive-style C and C++ projects. It has the
engineering setup that safety-critical ECU software expects, ready from the
first commit:

| Area | What is set up |
|------|----------------|
| Build | CMake, C11 and C++17, strict warnings treated as errors, GCC and Clang |
| Unit tests | GoogleTest, discovered by CTest, JUnit results in CI |
| Coding rules | MISRA C:2012 checks with the cppcheck addon, clang-tidy (CERT, C++ Core Guidelines) |
| Coverage | gcovr, line coverage gate at 90 %, HTML report as a CI artifact |
| Traceability | Requirements in `docs/requirements.md`, tests tagged `@verifies REQ-…`, matrix generated in CI, and the build fails on gaps |
| Change control | Issue templates for requirements and defects, PR checklist, CHANGELOG, semantic versioning |

Two small example modules show the conventions:

- `Crc_CalculateCRC8`, CRC-8 SAE J1850 with the AUTOSAR CRC library interface, checked against the AUTOSAR reference vectors.
- `autolib::StaticRingBuffer<T, N>`, a fixed-capacity FIFO with no dynamic memory.

## Quick start

```bash
sudo apt-get install -y cmake g++ libgtest-dev cppcheck clang-tidy gcovr
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure

tools/static_analysis.sh build     # MISRA C + clang-tidy
python3 tools/trace.py             # writes build/traceability.md
```

Coverage:

```bash
cmake -S . -B build-cov -DAUTOLIB_COVERAGE=ON && cmake --build build-cov
ctest --test-dir build-cov && gcovr -r . --filter src/ --filter include/
```

## Layout

```
include/autolib/    public headers
src/                implementation (C)
test/               GoogleTest unit tests, tagged with @verifies
docs/               requirements
tools/              static analysis and traceability scripts
.github/            CI workflow, issue and PR templates
```

## Development workflow

1. Add or change a requirement in `docs/requirements.md`, through a *Requirement* issue.
2. Implement it, and tag the tests that verify it: `// @verifies REQ-XXX-001`.
3. Open a PR. CI builds with GCC and Clang, runs the tests, MISRA and clang-tidy, the coverage gate and the traceability check.
4. Update `CHANGELOG.md` and tag a release.

## MISRA note

The MISRA rule texts are copyrighted and not included. cppcheck still reports
each violation by rule number. If you have a licensed copy, put the rule texts in
`tools/misra_rules.txt` to get full descriptions.

## License

MIT
