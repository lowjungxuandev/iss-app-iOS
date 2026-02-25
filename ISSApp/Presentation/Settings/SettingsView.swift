import SwiftUI

struct SettingsView: View {
    @Bindable var viewModel: SettingsViewModel

    init(viewModel: SettingsViewModel) {
        self.viewModel = viewModel
    }

    var body: some View {
        NavigationStack {
            Form {
                Section("About") {
                    LabeledContent("Version", value: viewModel.versionText)
                }
                Section("Preferences") {
                    Toggle("Example setting", isOn: $viewModel.isExampleOn)
                }
            }
            .navigationTitle("Settings")
        }
    }
}
