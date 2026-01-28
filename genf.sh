#!/bin/bash

ffmpeg -i badapple/badapple.mp4 \
-filter_complex "[0:v] fps=18.2065124526,scale=80:25:flags=bicubic" \
-f image2 \
badapple/src/output_%04d.png