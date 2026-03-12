#!/bin/bash

echo "threads,float_gm_percent,double_gm_percent" > summary.csv

for t in 1 2 4 8 16
do
    echo "Running with $t threads..."

    OPENBLAS_NUM_THREADS=$t ./bench_syrk > result_${t}_threads.txt

    float_gm=$(awk '
        /===== FLOAT SYRK TEST =====/ {section="float"}
        /===== DOUBLE SYRK TEST =====/ {section="double"}
        /Geometric mean relative performance:/ {
            if (section=="float") {
                gsub("%", "", $5)
                print $5
                exit
            }
        }
    ' result_${t}_threads.txt)

    double_gm=$(awk '
        /===== FLOAT SYRK TEST =====/ {section="float"}
        /===== DOUBLE SYRK TEST =====/ {section="double"}
        /Geometric mean relative performance:/ {
            if (section=="double") {
                gsub("%", "", $5)
                print $5
                exit
            }
        }
    ' result_${t}_threads.txt)

    echo "$t,$float_gm,$double_gm" >> summary.csv
done

echo
echo "Выполнено"
echo "Сводная таблица сохранена в summary.csv"

