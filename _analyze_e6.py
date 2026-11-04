import math

data = [11175,10853,10846,10927,10943,11010,11075,11171,11262,11351,11462,11505,11618,11710,11886,12005,12057,12192,12341,12442,12571,12660,12801,12880,12999,13121,13238,13414,13521,13610,13764,13890,14027,14123,14224,14378,14451,14597,14749,14895,15065,15165,15253,15461,15560,15600,15815,15988,16105,16237]
n = len(data)

mean = sum(data)/n
sd = math.sqrt(sum((x-mean)**2 for x in data)/(n-1))
print(f"N={n}, mean={mean:.1f}, SD={sd:.1f}, SD>45: {sd>45}")

nForeID = round(n/3)
nEndID = n - 3
fore = data[:nForeID]
late = data[nEndID:]
fore_avg = sum(fore)/len(fore)
late_avg = sum(late)/len(late)
print(f"Early 1-{nForeID}: avg={fore_avg:.1f}")
print(f"Late {nEndID+1}-{n}: avg={late_avg:.1f}")
print(f"Late > Early*1.1 ({fore_avg*1.1:.1f}): {late_avg > fore_avg*1.1}, ratio={late_avg/fore_avg:.3f}")

diffs = [data[i]-data[i-1] for i in range(1,n)]
print(f"Diff avg={sum(diffs)/len(diffs):.1f}, min={min(diffs)}, max={max(diffs)}")

# backup baseline 50 cycles: span > 2/3 -> start = end - 33 = 17
start_backup = n - int(n*2/3)
baseline_seg = data[start_backup-1:]
bl_mean = sum(baseline_seg)/len(baseline_seg)
print(f"Backup baseline {start_backup}-{n}: mean={bl_mean:.1f}")

delta = [x - bl_mean for x in data]
print(f"Delta after backup subtract: cycle1={delta[0]:.0f}, cycle50={delta[-1]:.0f}")

thresh = 1000
for i in range(1, n):
    if delta[i] >= thresh and delta[i-1] < thresh:
        frac = (thresh - delta[i-1]) / (delta[i] - delta[i-1])
        ct = i + frac + 1  # 1-based cycle
        print(f"Cross DeltaRn 1000 at Ct ~ {ct:.2f}")
        break
else:
    print("No crossing DeltaRn 1000")

# linear fit slope entire curve
x = list(range(n))
xmean = sum(x)/n
ymean = mean
num = sum((x[i]-xmean)*(data[i]-ymean) for i in range(n))
den = sum((x[i]-xmean)**2 for i in range(n))
slope = num/den
print(f"Linear slope over all cycles: {slope:.1f} per cycle")

# second derivative rough on smoothed (simple diff twice)
y = data[:]
d1 = [y[i+1]-y[i] for i in range(n-1)]
d2 = [d1[i+1]-d1[i] for i in range(n-2)]
print(f"2nd deriv range: min={min(d2):.1f}, max={max(d2):.1f}, at cycle {d2.index(max(d2))+2}")
