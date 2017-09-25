#!/bin/bash

# Create build dir if necessary 
if [ ! -d ../rules/build ]; then
    mkdir ../rules/build;
fi

# Change directory to meurpyl/meurpyl
cd ..

# Build PDF
pdflatex -halt-on-error -output-directory=./rules/build ./rules/latex/meurpyl.tex

# Build markdown
pandoc -s ./rules/latex/meurpyl.tex -o ./rules/build/meurpyl.md

# Build html
pandoc -s ./rules/latex/meurpyl.tex -o ./rules/build/meurpyl.html

# Move working markdown copy to root folder
cp ./rules/build/meurpyl.html ../working_copy.html