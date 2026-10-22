# PREFERENCE.md

- [claude-fable-5.1, 2026-09-16] No build toolchain on the dev box: verify claims by static analysis only; do not attempt cmake/make/tests.
- [claude-fable-5.1, 2026-09-16] Bug-scan exercises are read-only: write the report under `tmp/` (top-N high-severity findings only, N as requested) and do not change code.
- [claude-fable-5.1, 2026-09-16] Strong bloat aversion: when a proposed fix is net-positive LoC, look for a net-neutral or negative alternative (delete the code that causes the bug rather than guard it) before proposing it.
- [claude-fable-5.1, 2026-09-16] MatrixNotifier must write the complete recording (tail included) to disk; trimming is a post-processing step, because two recordings may later need to be concatenated into one. Do not move the tail decision to write time.
- [claude-fable-5.1, 2026-09-16] The signal handler in main.cpp calling `drogon::app().quit()` is intentional: it bridges Drogon's event system and the feed loop. Verify a library's contract in its upstream docs/source before changing integration code, and do not remove a mechanism whose intent is unclear.
- [gpt-6, 2026-09-17] Branch-versus-main reviews should report newly introduced issues under `tmp/` and distinguish new regressions from pre-existing weaknesses.
- [gpt-6, 2026-10-20] GoogleTest suites must configure and build independently of the application's heavy dependencies in the sandboxed development environment.
- [gpt-6, 2026-10-20] Upgrade dependencies selectively: keep small release gaps of one or two minor revisions; review years-old pins even when the semantic minor-number gap is small.
- [gpt-6, 2026-10-20] For requested dependency upgrades, choose the newest stable upstream release at least 28 days old, stepping back through releases until that age requirement is met.
- [gpt-6, 2026-10-20] For this dependency update, change only GnuTLS; let CPR follow the baseline without an override.
- [gpt-6, 2026-10-20] Keep implementation commit chains clear by separating reversals, production refactors, test infrastructure, and tests when each is a distinct change.
- [claude-opus-5.5, 2026-10-20] Building/running `tests/` must not touch production code; use the system toolchain and keep build output under `tmp/<model-name>/`. The toolchain is now installed (gcc-c++, cmake, make, EPEL gtest), so the no-toolchain note above no longer applies to `tests/`.
- [claude-opus-5.5, 2026-10-20] Do not pin libgnutls; let the vcpkg baseline choose its version. The old 3.7.8 pin's possible CPU-use reason is not a concern.
- [claude-opus-5.5, 2026-10-21] Testable logic goes in `src/matrix-pipeline/core/`: no OpenCV, CUDA, TensorRT, drogon or spdlog there. `tests/` may include only `core/`.
- [claude-opus-5.5, 2026-10-21] When a dedicated branch is proposed, the user may keep the work on the current branch and ask for a branch rename that matches its content.
