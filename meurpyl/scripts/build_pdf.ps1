# Powershell build.

# Create build dir if necessary 
If (-Not (Test-Path -Path "../rules/build")) {
    New-Item -Path "../rules/build/" -Name "build" -ItemType "Directory";
}

# Change directory to meurpyl/meurpyl
Set-Location ../;

# Build PDF
pdflatex -halt-on-error -output-directory ./rules/build ./rules/latex/meurpyl.tex;