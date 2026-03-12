#!/bin/bash

echo "| Потоки | Float GM (%) | Double GM (%) |" > summary.md
echo "|--------|--------------|---------------|" >> summary.md

tail -n +2 summary.csv | while IFS=, read -r threads floatgm doublegm
do
    echo "| $threads | $floatgm | $doublegm |" >> summary.md
done

echo "Markdown table saved to summary.md"
