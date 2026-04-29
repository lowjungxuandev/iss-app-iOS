import Observation

@MainActor
@Observable
final class ZimperiumViewModel {
    let logStore: ZimperiumLogStore

    init(logStore: ZimperiumLogStore = .shared) {
        self.logStore = logStore
    }
}
