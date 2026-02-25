#if canImport(ZDefend)
import ZDefend

enum ZimperiumStatusFormatter {
    static func buildStatusText(status: ZDeviceStatus) -> String {
        var lines = [
            "=== Device Status ===",
            "Device ID: \(status.deviceId)",
            "SDK Version: \(status.sdkVersion)",
            "Status Date: \(status.statusDate)",
            "Login Status: \(status.nameForLoginStatus) (Error: \(status.nameForLoginLastError))",
            "Initial Scan Progress: \(status.initialScanProgressPercentage)%",
            ""
        ]

        lines.append("--- Policies (\(status.devicePolicies.count)) ---")
        lines.append(contentsOf: status.devicePolicies.map { "  • \($0.policyName) | \($0.policyHash)" })
        lines.append("")

        appendSection(title: "Threat Detected", threats: status.allThreats, to: &lines)
        appendSection(title: "Active New Threats", threats: status.activeNewThreats, to: &lines)
        appendSection(title: "Mitigated New Threats", threats: status.mitigatedNewThreats, to: &lines)
        appendSection(title: "Active Threats", threats: status.activeThreats, to: &lines)
        appendSection(title: "Mitigated Threats", threats: status.mitigatedThreats, to: &lines)

        return lines.joined(separator: "\n")
    }

    private static func appendSection(title: String, threats: [ZDefendThreat], to lines: inout [String]) {
        lines.append("--- \(title) (\(threats.count)) ---")
        lines.append(contentsOf: groupedThreatLines(threats))
        lines.append("")
    }

    private static func groupedThreatLines(_ threats: [ZDefendThreat]) -> [String] {
        guard !threats.isEmpty else { return ["  • none"] }

        var lines: [String] = []
        let groupedByName = Dictionary(grouping: threats, by: \.internalName)
        for (internalName, threatGroup) in groupedByName.sorted(by: { $0.key < $1.key }) {
            if threatGroup.count == 1 {
                lines.append("  • \(internalName)")
                continue
            }

            lines.append("  • \(internalName) (\(threatGroup.count))")
            let appGroups = Dictionary(grouping: threatGroup, by: \.appName)
            for (appName, appThreats) in appGroups.sorted(by: { $0.key < $1.key }) {
                let resolvedAppName = appName.isEmpty ? "UNKNOWN_APP" : appName
                lines.append("    • \(resolvedAppName) (\(appThreats.count))")
            }
        }
        return lines
    }
}
#endif
