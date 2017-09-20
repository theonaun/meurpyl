#!/bin/bash

# Change directory to meurpyl/meurpyl/documentation
cd ../rules/latex

# Run command
pdflatex -halt-on-error -output-directory=../build meurpyl.tex

# Put copy of PDF in top dir.
cp ../build/meurpyl.pdf ../../../meurpyl.pdf
