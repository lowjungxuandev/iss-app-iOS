import AppIntents
import SwiftUI

@main
struct ISSApp: App {
    @State private var zimperiumViewModel: ZimperiumViewModel
    @State private var settingsViewModel: SettingsViewModel

    init() {
        ZDefendBootstrapper.shared.start()
        _zimperiumViewModel = State(initialValue: ZimperiumViewModel())
        _settingsViewModel = State(initialValue: SettingsViewModel())
    }

    var body: some Scene {
        WindowGroup {
            TabView {
                Tab("Zimperium", systemImage: "shield") {
                    ZimperiumView(viewModel: zimperiumViewModel)
                }
                Tab("Settings", systemImage: "gear") {
                    SettingsView(viewModel: settingsViewModel)
                }
            }
            .environment(\.horizontalSizeClass, .compact) // optional: force bottom tab bar on iPad
        }
    }
}