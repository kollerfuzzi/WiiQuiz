#!/bin/sh
make
env QT_QPA_PLATFORM=xcb dolphin-emu WiiQuiz.dol
