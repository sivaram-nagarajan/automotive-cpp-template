#!/usr/bin/env bash
# Runs cppcheck (with the MISRA C:2012 addon on C sources) and clang-tidy.
# Usage: tools/static_analysis.sh [build-dir]
set -euo pipefail
BUILD_DIR="${1:-build}"
cd "$(dirname "$0")/.."

echo "== cppcheck (MISRA C:2012 addon) =="
MISRA_ADDON="misra"
# Rule texts are copyrighted by MISRA and not shipped; add tools/misra_rules.txt
# locally (from your licensed copy) to get rule descriptions in the output.
if [[ -f tools/misra_rules.txt ]]; then MISRA_ADDON="tools/misra.json"; fi
cppcheck --std=c11 --enable=warning,style,performance,portability \
  --addon="${MISRA_ADDON}" --inline-suppr --error-exitcode=1 \
  --suppress=missingIncludeSystem --suppress=checkersReport \
  -I include src

echo "== cppcheck (C++) =="
cppcheck --std=c++17 --language=c++ --enable=warning,style,performance,portability \
  --inline-suppr --error-exitcode=1 --suppress=missingIncludeSystem \
  --suppress=checkersReport --suppress=unusedFunction \
  -I include include/autolib/*.hpp

echo "== clang-tidy =="
clang-tidy -p "${BUILD_DIR}" --quiet src/*.c test/*.cpp
