import Foundation
#if canImport(ZDefend)
import ZDefend
#endif

@MainActor
final class ZDefendBootstrapper {
    static let shared = ZDefendBootstrapper()

    private enum SelectedLicense {
        case issDev
        case issDevelopment

        var enumRawValue: Int {
            switch self {
            case .issDev: return 0
            case .issDevelopment: return 1
            }
        }

        var keyName: String {
            switch self {
            case .issDev: return "ISS_DEV"
            case .issDevelopment: return "ISS_DEVELOPMENT"
            }
        }
    }

    private var started = false
    #if canImport(ZDefend)
    private var deviceStatusRegistration: ZDeviceStatusRegistration?
    private var linkedFunctionRegistration: ZLinkedFunctionRegistrationV2?
    #endif

    private init() {}

    func start() {
        guard !started else { return }
        started = true

        let bundleID = Bundle.main.bundleIdentifier ?? "unknown.bundle.id"
        let selectedLicense = selectLicense(for: bundleID)

        #if canImport(ZDefend)
        guard let licenseKeyEnum = ZDefendLicenseKeyNames(rawValue: selectedLicense.enumRawValue) else {
            ZimperiumLogStore.shared.text = """
            Zimperium startup error:
            Bundle ID: \(bundleID)
            Selected license key: \(selectedLicense.keyName)
            selectLicenseKey failed: enum raw value mismatch.
            """
            return
        }
        ZDefendLicenseKeys.selectLicenseKey(licenseKeyEnum)

        deviceStatusRegistration = ZDefend.addDeviceStatusCallback { status in
            Task { @MainActor in
                ZimperiumLogStore.shared.text = ZimperiumStatusFormatter.buildStatusText(status: status)
            }
        }

        linkedFunctionRegistration = ZDefend.registerLinkedFunction(
            "THREAT_DETECTED",
            function: { event in
                let baseText = ZimperiumStatusFormatter.buildStatusText(status: event.deviceStatus)
                let threatNames = event.relatedThreats.map(\.internalName).joined(separator: ", ")
                let eventType: String
                switch event.eventType {
                case .ACTIVATED_LINKED_FUNCTION:
                    eventType = "ACTIVATED"
                case .MITIGATED_LINKED_FUNCTION:
                    eventType = "MITIGATED"
                @unknown default:
                    eventType = "UNKNOWN"
                }
                let message = """
                \(baseText)

                --- Linked Function Event ---
                Label: \(event.label)
                Type: \(eventType)
                Related threats: \(threatNames.isEmpty ? "none" : threatNames)
                """
                Task { @MainActor in ZimperiumLogStore.shared.text = message }
            },
            mitigateFunction: { event in
                let baseText = ZimperiumStatusFormatter.buildStatusText(status: event.deviceStatus)
                let threatNames = event.relatedThreats.map(\.internalName).joined(separator: ", ")
                let message = """
                \(baseText)

                --- Linked Function Event ---
                Label: \(event.label)
                Type: MITIGATED
                Related threats: \(threatNames.isEmpty ? "none" : threatNames)
                """
                Task { @MainActor in ZimperiumLogStore.shared.text = message }
            }
        )

        ZDefend.checkForUpdates()
        #else
        ZimperiumLogStore.shared.text = "ZDefend framework unavailable; bootstrap skipped."
        #endif
    }

    private func selectLicense(for bundleID: String) -> SelectedLicense {
        bundleID == "com.dbs.lowjx.issdev.development" ? .issDevelopment : .issDev
    }
}
