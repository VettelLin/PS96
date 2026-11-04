import numpy as np
from itertools import product

inp = np.array([
5909.407,5880.114,5853.121,5849.829,5821.536,5850.243,5868.95,5922.657,6006.364,6190.071,
6312.779,6482.486,6525.193,6680.9,6775.607,6962.314,7331.021,7907.729,8655.436,9971.143,
11700.85,13934.56,16403.26,19517.97,22596.68,24770.39,27275.09,27631.8,28703.51,29011.21,
29407.92,29533.63,29905.34,30025.04,30221.75,30196.22,30289.16,30374.87,30371.94,30417.29,
30488.99,30602.7,30642.41,30639.48,30641.95,30816.53,30813.6,30800.87,30815.34,30977.36,
30996.06,31355.77,31352.84,31325.91,31311.88,31308.95,31306.02,31303.1,31280.47,31277.54
], dtype=float)

exp = np.array([
6388.459,6389.656,6392.347,6396.786,6403.319,6411.783,6421.911,6433.392,6446.422,6598.473,
6791.42,7056.479,7437.81,7986.077,8761.985,9820.092,11194.33,12892.57,14879.76,17071.38,
19342.3,21558.42,23577.19,25305.11,26692.67,27747.94,28507.57,29048.2,29427.04,29699.2,
29898.19,30050.85,30165.65,30255.42,30327.32,30389.7,30446.81,30501.36,30554.09,30604.9,
30654.45,30701.27,30748.84,30801.18,30861.69,30929.49,31006.83,31086.32,31159.99,31220.73,
31265.58,31290.73,31301.09,31301.66,31297.24,31291.08,31286.16,31282.77,31280.69,31279.58
], dtype=float)


def kdspt_new(y, M, N):
    n = len(y)
    out = np.empty_like(y)
    if M < 0 or N < 0 or n < M + N + 1:
        return y.copy()
    for i in range(n):
        if i < M:
            start, end = 0, i + N
        elif i < n - N:
            start, end = i - M, i + N
        else:
            start, end = i - M, n - 1
        if M == N:
            nPre = i - start
            nBehind = end - i
            if nPre > nBehind:
                start = i - nBehind
            else:
                end = i + nPre
        s = 0.0
        count = 0
        for k in range(start, end + 1):
            s += y[k]
            count += 1
        if M != N and i > (n - 1 - N):
            k = i + N
            while k > n - 1:
                s += y[n - 1]
                count += 1
                k -= 1
        out[i] = s / count if count else y[i]
    return out


def apply_times(y, M, N, times):
    cur = y.copy()
    for _ in range(times):
        cur = kdspt_new(cur, M, N)
    return cur


best = None
for M, N, t in product(range(0, 25), range(0, 25), range(1, 31)):
    if M + N + 1 > 60:
        continue
    out = apply_times(inp, M, N, t)
    err = float(np.max(np.abs(out - exp)))
    mae = float(np.mean(np.abs(out - exp)))
    if best is None or err < best[0]:
        best = (err, mae, M, N, t)

print('best among KdsptForwardMBackN_New:', best)

# centered moving average fixed window
best2 = None
for w in range(3, 61, 2):
    half = w // 2
    out = np.empty_like(inp)
    for i in range(len(inp)):
        a = max(0, i - half)
        b = min(len(inp), i + half + 1)
        out[i] = inp[a:b].mean()
    err = float(np.max(np.abs(out - exp)))
    if best2 is None or err < best2[0]:
        best2 = (err, w, out[0], exp[0])
print('best odd centered MA:', best2)

# cumulative / prefix weirdness: first expected vs prefix means
print('inp[0]=', inp[0], 'exp[0]=', exp[0])
print('mean whole=', inp.mean())
for w in [5, 9, 11, 15, 21, 25, 31]:
    print(f'mean first {w}=', inp[:w].mean(), 'mean center-ish points around rise', inp[8:8+w].mean() if 8+w<=60 else None)

# Check if exp could be from SG quadratic/cubic
# Or from repeated 2,2 many times - print first few for M=N=2 times=1..20
print('M=N=2 first5 for various times:')
for t in [1, 2, 3, 5, 10, 20, 30]:
    out = apply_times(inp, 2, 2, t)
    print(t, out[:5], 'err0', abs(out[0]-exp[0]))

# Maybe input is NOT turbidity but something else; check if exp is smoother version
# Fit: is exp[i] approx alpha*inp[i]+(1-alpha)*exp[i-1]?
alphas = []
for i in range(1, 60):
    # exp[i] = a*inp[i] + (1-a)*exp[i-1] => a = (exp[i]-exp[i-1])/(inp[i]-exp[i-1]) if denom!=0
    den = inp[i] - exp[i-1]
    if abs(den) > 1e-6:
        a = (exp[i] - exp[i-1]) / den
        alphas.append(a)
print('EWMA alpha stats:', np.mean(alphas), np.std(alphas), np.min(alphas), np.max(alphas))

# Try two-pass: forward then backward causal mean
def causal_mean(y, w):
    out = np.empty_like(y)
    for i in range(len(y)):
        a = max(0, i - w + 1)
        out[i] = y[a:i+1].mean()
    return out

def anticausal_mean(y, w):
    out = np.empty_like(y)
    n = len(y)
    for i in range(n):
        b = min(n, i + w)
        out[i] = y[i:b].mean()
    return out

best3 = None
for wf, wb, order in product(range(1, 25), range(1, 25), ['fb', 'bf']):
    if order == 'fb':
        out = anticausal_mean(causal_mean(inp, wf), wb)
    else:
        out = causal_mean(anticausal_mean(inp, wb), wf)
    err = float(np.max(np.abs(out - exp)))
    if best3 is None or err < best3[0]:
        best3 = (err, wf, wb, order, out[0])
print('best causal/anticausal combo:', best3)

# Check polynomial smooth FILTERTYPE style - QuadraticSmooth_5 etc from comments
# Try scipy if available
try:
    from scipy.signal import savgol_filter
    best4 = None
    for w in range(5, 61, 2):
        for poly in (2, 3, 4, 5):
            if poly >= w:
                continue
            out = savgol_filter(inp, w, poly, mode='interp')
            err = float(np.max(np.abs(out - exp)))
            if best4 is None or err < best4[0]:
                best4 = (err, w, poly, out[0], out[1])
    print('best savgol:', best4)
except Exception as e:
    print('scipy unavailable', e)

# Maybe FLU_FILTER in export is NOT mean of turbidity - check if expected equals some other transform
# e.g. subtract baseline slope then filter?
print('delta first9 exp:', np.diff(exp[:9]))
print('delta first9 inp:', np.diff(inp[:9]))
