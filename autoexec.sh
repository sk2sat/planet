#!/bin/sh

alias tweet="~/python/twitter/tweet.py"

tweet "starting autoexec.sh"
make run
tweet "finish simulation."
make conv
tweet "finish convert."
make render
tweet "finish rendering."
make mp4
tweet "finish making mp4."
