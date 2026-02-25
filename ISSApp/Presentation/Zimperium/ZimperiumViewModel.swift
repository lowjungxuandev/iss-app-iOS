import Observation
#if canImport(ZDefend)
import ZDefend
#endif

@MainActor
@Observable
final class ZimperiumViewModel {
    let logStore: ZimperiumLogStore

    init(logStore: ZimperiumLogStore = .shared) {
        self.logStore = logStore
    }

    func scanThreat() {
        #if canImport(ZDefend)
        ZDefend.checkForUpdates()
        #else
        logStore.text = "ZDefend framework unavailable; scan skipped."
        #endif
    }
}
