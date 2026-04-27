# ISSApp iOS (Zimperium + Settings)

SwiftUI iOS app with two tabs:
- **Zimperium**: displays device status/log output from the `ZDefend` SDK and provides a **Scan Threat** action.
- **Settings**: simple app settings screen with app version and an example toggle.

The project uses Swift 6, SwiftUI, the Observation framework (`@Observable`), and strict concurrency.

## Architecture

The app is intentionally small and split by responsibility:

- **App composition**: `ISSApp/App/ISSApp.swift`
  - App entry point.
  - Starts Zimperium bootstrap once at launch.
  - Creates and injects tab view models.
- **Presentation**: `ISSApp/Presentation/...`
  - `ZimperiumView`, `ZimperiumViewModel`, `ZimperiumLogStore`
  - `SettingsView`, `SettingsViewModel`
- **Zimperium integration**: `ISSApp/Data/Zimperium/...`
  - `ZDefendBootstrapper`: license selection, callback registration, startup flow.
  - `ZimperiumStatusFormatter`: builds readable text output from SDK status/threat objects.

## Project structure

```text
iOS/
├── ISSApp/
│   ├── App/
│   │   └── ISSApp.swift
│   ├── Presentation/
│   │   ├── Zimperium/
│   │   │   ├── ZimperiumView.swift
│   │   │   ├── ZimperiumViewModel.swift
│   │   │   └── ZimperiumLogStore.swift
│   │   └── Settings/
│   │       ├── SettingsView.swift
│   │       └── SettingsViewModel.swift
│   ├── Data/
│   │   └── Zimperium/
│   │       ├── ZDefendBootstrapper.swift
│   │       └── ZimperiumStatusFormatter.swift
│   └── Assets.xcassets/
├── ISSTests/
├── ISSApp.xcodeproj/
└── README.md
```

## Schemes and bundle IDs

| Scheme | Bundle ID | Home screen name |
|---|---|---|
| `ISS` | `com.dbs.lowjx.issdev` | ISS |
| `ISS Dev` | `com.dbs.lowjx.issdev.development` | ISS Dev |

Build configurations:
- `Debug-Development`
- `Release-Development`
- `Debug-Production`
- `Release-Production`

## Zimperium license key selection

At startup, `ZDefendBootstrapper` chooses the SDK license key by bundle ID:

- `com.dbs.lowjx.issdev.development` -> `ISS_DEVELOPMENT`
- Any other bundle ID (including production scheme) -> `ISS_DEV`

If `ZDefend` is unavailable at compile time, startup and scan actions are safely skipped and a readable log message is shown instead.

## ZDefend SDK framework location

- Bundled version: **5.10.9** (`ZDefend.xcframework` at `ISSApp/ZDefend.xcframework`, relative to the `iOS` folder).
- In Xcode, select the `ISSApp` target and ensure `ZDefend.xcframework` appears under **Frameworks, Libraries, and Embedded Content** with **Embed & Sign**.
- When updating the SDK version, replace the contents of `ZDefend.xcframework` at this path, bump the app `MARKETING_VERSION` / `CURRENT_PROJECT_VERSION` in the Xcode project as needed, and let Xcode re-index the framework.

## Requirements

- Xcode 16+
- iOS 18+
- Swift 6 language mode

## Build

Open `ISSApp.xcodeproj` in Xcode and run either:
- scheme `ISS`
- scheme `ISS Dev`

Or build from command line, for example:

```bash
xcodebuild -project ISSApp.xcodeproj -scheme "ISS Dev" -configuration Debug-Development -destination 'generic/platform=iOS Simulator' build
```
