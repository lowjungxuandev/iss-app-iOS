import Foundation
import Observation

@MainActor
@Observable
final class SettingsViewModel {
    var versionText: String {
        "Version 1.0.0"
    }
    var isExampleOn: Bool = false
}
