#!/bin/bash

{ python ../elliotgui/manage.py runserver 0.0.0.0:8000; } &
SERVER=$!
{ ./build/bin/exec; } &
PRGM=$!



trap "echo '$SERVER $PRGM' >> blob.txt || kill -9 $SERVER || kill -9 $PRGM" 2 3	
