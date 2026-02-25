#!/usr/bin/env bash
#
# Build an unsigned DEVICE IPA (iphoneos) without local signing credentials.
# This output is intended for downstream re-signing by a deployment team.
#
# Usage: ./scripts/build_ipa_without_apple_account.sh [APP_TARGET] [CONFIGURATION]
# Default target: ISSApp
# Default configuration: Release-Production
# Output: build/ISSApp-unsigned-yyyyMMdd_HHmmSS.ipa (and Payload/ under build/)
#

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Project root is one level above ISSApp/ (iOS/)
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
APP_TARGET="${1:-ISSApp}"
CONFIGURATION="${2:-Release-Production}"
OUTPUT_DIR="$PROJECT_DIR/build"
PAYLOAD_DIR="$OUTPUT_DIR/Payload"
DATETIME="$(date +%Y%m%d_%H%M%S)"
IPA_NAME="${APP_TARGET}-unsigned-${DATETIME}.ipa"
IPA_PATH="$OUTPUT_DIR/$IPA_NAME"

cd "$PROJECT_DIR"
mkdir -p "$OUTPUT_DIR"

echo "Cleaning build for target: $APP_TARGET..."
xcodebuild \
  -project ISSApp.xcodeproj \
  -target "$APP_TARGET" \
  -configuration "$CONFIGURATION" \
  -sdk iphoneos \
  clean

echo "Building target: $APP_TARGET (config: $CONFIGURATION) for iOS device (unsigned)..."
xcodebuild \
  -project ISSApp.xcodeproj \
  -target "$APP_TARGET" \
  -configuration "$CONFIGURATION" \
  -sdk iphoneos \
  -destination 'generic/platform=iOS' \
  SYMROOT="$OUTPUT_DIR" \
  CODE_SIGNING_ALLOWED=NO \
  CODE_SIGNING_REQUIRED=NO \
  CODE_SIGN_IDENTITY="" \
  DEVELOPMENT_TEAM="" \
  build

# Locate the built .app (SYMROOT or DerivedData depending on xcodebuild).
DEVICE_APP="$OUTPUT_DIR/${CONFIGURATION}-iphoneos/${APP_TARGET}.app"
if [[ ! -d "$DEVICE_APP" ]]; then
  DEVICE_APP="$OUTPUT_DIR/DerivedData/Build/Products/${CONFIGURATION}-iphoneos/${APP_TARGET}.app"
fi
if [[ ! -d "$DEVICE_APP" ]]; then
  echo "Error: Built app not found. Checked:"
  echo "  $OUTPUT_DIR/${CONFIGURATION}-iphoneos/${APP_TARGET}.app"
  echo "  $OUTPUT_DIR/DerivedData/Build/Products/${CONFIGURATION}-iphoneos/${APP_TARGET}.app"
  exit 1
fi

echo "Packaging unsigned device .app into IPA..."
rm -rf "$PAYLOAD_DIR"
mkdir -p "$PAYLOAD_DIR"
cp -R "$DEVICE_APP" "$PAYLOAD_DIR/"

rm -f "$IPA_PATH"
cd "$OUTPUT_DIR"
zip -r -y "$IPA_NAME" Payload
cd "$PROJECT_DIR"

echo "Done. Unsigned device IPA: $IPA_PATH"
echo "Send this IPA to deployment team for re-signing before installing on devices."
