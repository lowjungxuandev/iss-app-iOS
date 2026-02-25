import Observation

@MainActor
@Observable
final class ZimperiumLogStore {
    static let shared = ZimperiumLogStore()

    var text = ""

    private init() {}
}
