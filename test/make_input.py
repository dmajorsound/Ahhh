# test signal for the null tests: impulse, noise burst, log sweep (stereo, 48 kHz, 3 s) -> in.f64 (float64 interleaved)
import numpy as np
sr = 48000; n = sr * 3
rng = np.random.default_rng(1)
x = np.zeros((n, 2))
x[100, 0] = 0.9; x[100, 1] = 0.5
x[sr // 2:sr // 2 + 4800, :] = rng.standard_normal((4800, 2)) * 0.3
f = np.logspace(np.log10(40), np.log10(16000), sr)
ph = 2 * np.pi * np.cumsum(f) / sr
x[sr + sr // 4:sr * 2 + sr // 4, 0] += 0.4 * np.sin(ph[:sr])
x[sr + sr // 4:sr * 2 + sr // 4, 1] += 0.3 * np.sin(ph[:sr] * 1.01)
x.astype('<f8').tofile('in.f64')
