#!/bin/bash/sh
rm *.aux *.fdb_latexmk *.log *.fls *.synctex.gz *.toc
git add .
git commit -m "update"
git push -u origin master
