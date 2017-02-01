#!/bin/sh

mkdir out
make run
make conv
make render
make mp4
