#!/bin/sh

echo ''
echo ' Building tests...'
echo ''
bjam --clean
bjam | grep -G 'error C[0-9]\+'
echo ''
echo ' Running tests...'
echo ''
bin/msvc-9.0/debug/threading-multi/test.exe

