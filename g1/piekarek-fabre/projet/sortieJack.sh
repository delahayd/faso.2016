#!/bin/bash
amixer sset 'PCM' 100%
pico2wave -l fr-FR -w /tmp/test.wav "$1"
sudo aplay -q /tmp/test.wav
rm /tmp/test.wav
