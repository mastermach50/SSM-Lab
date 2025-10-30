#!/bin/sh

curl -o ./SSM-Lab-main.zip -SsfL https://github.com/mastermach50/SSM-Lab/archive/refs/heads/main.zip
unzip -q ./SSM-Lab-main.zip -d .
mv ./SSM-Lab-main ./SSM-Lab
rm ./SSM-Lab-main.zip ./SSM-Lab/.gitignore ./SSM-Lab/.envrc ./SSM-Lab/shell.nix ./SSM-Lab/extract.sh