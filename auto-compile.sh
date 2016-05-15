#!/usr/bin/env bash

command -v pdflatex >/dev/null 2>&1 || {
    echo >&2 "Tex Compiler not found.Pdflatex is necessary to compiler this doc."
    exit 1
}
cd lectures/git_slides/ 

rm *.pdf 2>/dev/null
pdflatex git_for_coding_and_writing.tex
