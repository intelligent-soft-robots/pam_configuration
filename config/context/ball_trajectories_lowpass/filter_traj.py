import json
import os
import sys
from context import LowPassFilter

filename = sys.argv[1]
print("file:", filename)

window_size = 5
data = []
with open(filename, 'r') as f:
    data = json.load(f)
    filter_lp = [LowPassFilter(window_size), LowPassFilter(window_size), LowPassFilter(window_size)]
    ob_new = []
    for i in range(len(data["ob"])):
        v = data["ob"][i][3:6]
        v_filtered = [filter_lp[i].get(v[i]) for i in range(3)]
        data_point_new = data["ob"][i][:3] + v_filtered
        ob_new.append(data_point_new)
data["ob"] = ob_new
filename_new = filename.replace('ball_trajectories', 'ball_trajectories_lowpass')
print("new file:", filename_new)
with open(filename_new, 'w') as f:
    json.dump(data, f)
