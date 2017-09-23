#!/bin/bash

# Create build dir if necessary 
if [ ! -d ../build ]; then
    mkdir ../build;
fi

# Change directory to meurpyl/meurpyl/documentation
cd ../rules

# Build PDF
pdflatex -halt-on-error -output-directory=./build ./latex/meurpyl.tex

# Build markdown
pandoc -s ./latex/meurpyl.tex -o ./build/meurpyl.md

# Build html
pandoc -s ./latex/meurpyl.tex -o ./build/meurpyl.html