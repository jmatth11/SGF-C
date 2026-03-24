#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

find "${PROJECT_DIR}/core/src" -iname '*.h' -o -iname '*.c' | xargs clang-format -i
