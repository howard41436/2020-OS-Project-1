test=$1
dmesg --clear
./scheduler < OS_PJ1_Test/$test.txt > output/${test}_stdout.txt
dmesg | grep Project1 | cut -d ']' -f 2- | cut -d ' ' -f 2- > output/${test}_dmesg.txt
