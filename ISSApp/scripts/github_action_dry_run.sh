#!/usr/bin/env bash
#
# Dry-run helper for the GitHub Actions iOS release workflow using `act`.
# This does NOT build real IPAs; it just exercises the workflow logic locally.
#
# Usage:
#   ./ISSApp/scripts/github_action_dry_run.sh
#

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$PROJECT_ROOT"

echo "Running GitHub Actions dry run with act (simulated macos-26)..."
echo "Project root: $PROJECT_ROOT"

act release \
  -W .github/workflows/ios-release-ipas.yml \
  -P macos-26=ghcr.io/catthehacker/ubuntu:act-latest \
  --container-architecture linux/amd64 \
  --env ACT=true \
  --job build

echo "Done. Check act output above to verify the workflow steps."

