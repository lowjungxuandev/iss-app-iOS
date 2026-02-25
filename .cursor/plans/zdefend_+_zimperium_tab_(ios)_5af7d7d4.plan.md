---
name: zDefend + Zimperium tab (iOS)
overview: Integrate the provided zDefend XCFramework (multi-license) into the SwiftUI app, enforce early license-key selection based on the active bundle ID, and add a new bottom-tab page (#1) called "Zimperium" that displays a combined log feed (zDefend callbacks + Android-mirrored log events).
todos:
  - id: vendorize-zdefend
    content: Create `Vendor/ZDefend/`, move `ZDefend.xcframework.zip`, unzip to `Vendor/ZDefend/ZDefend.xcframework`, and add XCFramework to Xcode with Embed & Sign.
    status: completed
  - id: bootstrap-multikey
    content: Implement `ZDefendBootstrapper` and call it at the start of `ISSApp.init()` to select `.ISS_DEVELOPMENT` vs `.ISS_DEV` based on bundle identifier and register device-status callback.
    status: completed
  - id: zimperium-tab
    content: Add a new SwiftUI tab at index 1 called “Zimperium” with a log UI backed by a shared log store.
    status: completed
  - id: android-zip-parity
    content: Unzip `zimperium.android.zip`, identify its logging/event logic, and implement an iOS adapter that emits equivalent entries into the same log store.
    status: completed
  - id: local-network-keys
    content: Add Local Network permission strings via Xcode build settings (generated Info.plist) and add Bonjour service declarations if required by SDK behavior.
    status: completed
isProject: false
---

## Context found in your project

- App entry + bottom bar is SwiftUI `TabView` in `[ISSApp/App/ISSApp.swift](/Users/jungxuanlow/Desktop/iss-app/iOS/ISSApp/App/ISSApp.swift)`.
- You already have 2 bundle identifiers configured in Xcode build configs:
  - `com.dbs.lowjx.issdev.development` (Development)
  - `com.dbs.lowjx.issdev` (Production)
  This is in `[ISSApp.xcodeproj/project.pbxproj](/Users/jungxuanlow/Desktop/iss-app/iOS/ISSApp.xcodeproj/project.pbxproj)`.
- There is **no checked-in `Info.plist`**; the target uses `GENERATE_INFOPLIST_FILE = YES`, so we’ll add privacy keys via build settings (or switch to a real plist if you prefer later).

## What we will implement

### 1) Add the zDefend framework in a clean repo location

- Create a vendor folder layout:
  - `[Vendor/ZDefend/](/Users/jungxuanlow/Desktop/iss-app/iOS/Vendor/ZDefend/)`
  - Move/keep `ZDefend.xcframework.zip` there
  - Unzip into `Vendor/ZDefend/ZDefend.xcframework`
- Add `Vendor/ZDefend/ZDefend.xcframework` to the Xcode project and set it to **Embed & Sign** (adds both link + embed phases).

### 2) Make multi-license startup safe (no “terminate on launch”)

- Add a small bootstrapper (new file, e.g. `[ISSApp/App/ZDefendBootstrapper.swift](/Users/jungxuanlow/Desktop/iss-app/iOS/ISSApp/App/ZDefendBootstrapper.swift)`) that runs **as the first line** inside `ISSApp.init()`.
- Logic:
  - Read `Bundle.main.bundleIdentifier`.
  - If it matches `com.dbs.lowjx.issdev.development` → call `selectLicenseKey(.ISS_DEVELOPMENT)`.
  - Else → call `selectLicenseKey(.ISS_DEV)`.
  - Register the zDefend device-status callback and append received events into an in-memory log store.
- We’ll confirm the exact Swift API names by inspecting the SDK’s generated Swift interface after unzipping (so the code matches your `5.9.36` package precisely).

Existing place we’ll hook into (from `ISSApp.swift`):

- The tab bar lives here and init is available for early startup.

```4:34:/Users/jungxuanlow/Desktop/iss-app/iOS/ISSApp/App/ISSApp.swift
@main
struct ISSApp: App {
    @State private var homeViewModel: HomeViewModel
    @State private var searchViewModel: SearchViewModel
    @State private var settingsViewModel: SettingsViewModel

    init() {
        let client = APIClient()
        let repo = RemoteItemRepository(client: client)
        let useCase = FetchItemsUseCase(repository: repo)
        _homeViewModel = State(initialValue: HomeViewModel(fetchItemsUseCase: useCase))
        _searchViewModel = State(initialValue: SearchViewModel())
        _settingsViewModel = State(initialValue: SettingsViewModel())
    }

    var body: some Scene {
        WindowGroup {
            TabView {
                Tab("Home", systemImage: "house") {
                    HomeView(viewModel: homeViewModel)
                }
                Tab("Search", systemImage: "magnifyingglass") {
                    SearchView(viewModel: searchViewModel)
                }
                Tab("Settings", systemImage: "gear") {
                    SettingsView(viewModel: settingsViewModel)
                }
            }
            .environment(\.horizontalSizeClass, .compact)
        }
    }
}
```

### 3) Add the new bottom tab (#1): “Zimperium” logging view

- Add a new SwiftUI screen (e.g. `[ISSApp/Presentation/Zimperium/ZimperiumView.swift](/Users/jungxuanlow/Desktop/iss-app/iOS/ISSApp/Presentation/Zimperium/ZimperiumView.swift)`) and optionally a view model / store:
  - Live-updating list of log entries
  - Minimal controls: Clear, Copy/Share, maybe a source filter
- Insert it as the **second tab** (index 1) in `TabView`, between Home and Search:
  - `Tab("Zimperium", systemImage: "shield") { ZimperiumView(...) }`

### 4) Mirror Android logging logic and combine feeds

- Unzip and inspect `[zimperium.android.zip](/Users/jungxuanlow/Desktop/iss-app/iOS/zimperium.android.zip)`.
- Identify:
  - What events are logged (SDK init, callbacks, threat/policy states)
  - How they’re formatted (tags, timestamps, severity)
- Implement a small “Android-mirrored” logger adapter in iOS that emits equivalent log entries to the same `LogStore` so the Zimperium tab shows **one combined stream**:
  - Source = `zDefend` or `androidMirror`

### 5) iOS privacy keys needed for Local Network prompt (MITM policies)

Because you use generated Info.plist today, we’ll set these via build settings in the project file:

- `INFOPLIST_KEY_NSLocalNetworkUsageDescription` with a specific purpose string
- If the SDK requires Bonjour browsing for discovery, also add:
  - `INFOPLIST_KEY_NSBonjourServices` (array) with the discovered service types

(We’ll keep Location + Wi-Fi capability steps optional and policy-driven, since enabling them without need can create extra prompts/review burden.)

## Verification steps (after implementation)

- Build and run each configuration:
  - Development (`com.dbs.lowjx.issdev.development`) selects `ISS_DEVELOPMENT`
  - Production (`com.dbs.lowjx.issdev`) selects `ISS_DEV`
- Confirm no startup termination (proves `selectLicenseKey` is called early enough).
- Open the new **Zimperium** tab and confirm logs appear:
  - Startup lines (license selected, bundle id)
  - zDefend callback events (when triggered)
  - Android-mirrored events (as implemented)
- If MITM policies enabled in zConsole, confirm Local Network permission prompt appears on first run and is properly described.

