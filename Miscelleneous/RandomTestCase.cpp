// Random Testcase
mt19937 rng(chrono::steady_clock::now().
time_since_epoch().count());
int ran(int l,int r){
return uniform_int_distribution<int>(l,r)(rng);
}
//stress
#!/bin/bash
build $1 $2 && build $1_gen $2 && build
$1_brute $2 &&
for((i = 1; ; ++i)); do
echo -e "\nTest Case "$i
./$1_gen $i > inp
echo -e "===========\nINPUT\n----"
cat inp
./$1 < inp > out1
echo -e "\nOUTPUT\n------"
cat out1
./$1_brute < inp > out2
echo -e "\nEXPECTED\n--------"
cat out2
echo ""
diff -w out1 out2 || break
done
//run
#!/bin/bash
build "$1" && >&2 echo -e
"Running\t\t: $1\n--"
&& "./$1"
//build
#!/bin/bash
>&2 echo -e "Making [$2]\t: $1.cpp" &&
g++ -std=gnu++17
-Wshadow -Wall -Wextra -Wno-unused-result -O2
-g -fsanitize=undefined -fsanitize=address $2 "$1.cpp" -o "$1"
//debug
#!/bin/bash
build "$1" -DPARVEJ && >&2 echo -e
"Running\t\t: $1\n--" && "./$1"