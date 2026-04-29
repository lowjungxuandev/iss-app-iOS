import SwiftUI

struct ZimperiumView: View {
    @State private var viewModel: ZimperiumViewModel

    init(viewModel: ZimperiumViewModel) {
        _viewModel = State(initialValue: viewModel)
    }

    var body: some View {
        NavigationStack {
            ScrollView {
                Text(logText)
                    .font(.system(size: 12, weight: .regular, design: .monospaced))
                    .lineSpacing(3)
                    .textSelection(.enabled)
                    .frame(maxWidth: .infinity, alignment: .leading)
                    .padding(16)
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .defaultScrollAnchor(.bottom)
            .navigationTitle("Zimperium")
        }
    }

    private var logText: String {
        if !viewModel.logStore.text.isEmpty {
            return viewModel.logStore.text
        }
        return "No Zimperium logs yet.\n\nLogs appear here after startup callbacks."
    }
}
