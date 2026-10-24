#!/usr/bin/env bash
# Runs every built solution against its inputs.
#
#   bin/run.sh [year [problem]]
#
# For build/<year>/<p>_<k>:
#   <year>/<p>.input  -> build/<year>/<p>_<k>.out
#   <year>/i<p>_<n>.txt -> build/<year>/<p>_<k>.i<n>.out   (example inputs)

set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${BUILD_DIR:-$ROOT/build}"
YEAR_FILTER="${1:-}"
PROBLEM_FILTER="${2:-}"

if [[ ! -d "$BUILD" ]]; then
  echo "no build directory at $BUILD; run 'make' first" >&2
  exit 1
fi

failed=0

run_one() {
  local exe="$1" input="$2" out="$3" label="$4"
  if "$exe" < "$input" > "$out"; then
    printf '%-24s %s\n' "$label" "$(tr '\n' ' ' < "$out")"
  else
    printf '%-24s FAILED (exit %d)\n' "$label" "$?"
    failed=1
  fi
}

for year_dir in "$BUILD"/[0-9][0-9][0-9][0-9]; do
  [[ -d "$year_dir" ]] || continue
  year="$(basename "$year_dir")"
  [[ -z "$YEAR_FILTER" || "$year" == "$YEAR_FILTER" ]] || continue

  # Sort numerically by problem then part so 10_1 comes after 9_2.
  while IFS= read -r exe; do
    name="$(basename "$exe")"
    problem="${name%_*}"
    [[ -z "$PROBLEM_FILTER" || "$problem" == "$PROBLEM_FILTER" ]] || continue
    src_dir="$ROOT/$year"

    for example in "$src_dir"/i"${problem}"_*.txt; do
      [[ -f "$example" ]] || continue
      n="$(basename "$example" .txt)"
      n="${n#i"${problem}"_}"
      run_one "$exe" "$example" "$year_dir/$name.i$n.out" "$year/$name (example $n)"
    done

    input="$src_dir/$problem.input"
    if [[ -f "$input" ]]; then
      run_one "$exe" "$input" "$year_dir/$name.out" "$year/$name"
    else
      printf '%-24s missing %s\n' "$year/$name" "${input#"$ROOT"/}"
    fi
  done < <(find "$year_dir" -maxdepth 1 -type f -perm -u+x  \
             -regex '.*/[0-9]*_[0-9]*' | sort -V)
done

exit "$failed"
