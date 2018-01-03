start cmd /c dom.exe 0 ^< in_test.txt ^> otest_10.txt
timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_all.txt ^> oall_10.txt
timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_c80.txt ^> oc80_10.txt
 
timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_cages.txt ^> ocages_10.txt
 
timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_cross.txt ^> ocross_10.txt

timeout /t 10
taskkill /im dom.exe /f
start  cmd /c dom.exe 0 ^< in_cyc_cyc.txt ^> ocyc_cyc_10.txt

timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_football_1.txt ^> ofootball_1_10.txt

timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_hypercube_1.txt ^> ohypercube_1_10.txt
timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_triang_grid.txt ^> otriang_grid_10.txt

timeout /t 10
taskkill /im dom.exe /f
start cmd /c dom.exe 0 ^< in_venn.txt ^> ovenn_10.txt

timeout /t 10
taskkill /im dom.exe /f

