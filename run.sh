test=$1
dmesg --clear
./scheduler < OS_PJ_1_Test/$test.txt > output/$test_stdout.txt
dmesg | grep Project1 | cut -d ' ' -f 4- > output/$test_dmesg.txt