HOSTLIST='/tmp/host.rec'
HOSTLIST='host.rec'
NUM=$1

cat > $HOSTLIST << EOF
hostname 1.1.1.1
EOF

LINECOUNT=`wc -l $HOSTLIST | awk '{print $1}'`

[ $# -ne 0 ] || { echo 'Choose the host number :'; awk '{printf "\t%-3s\t%-32s\t%-12s\n",NR,$1,$2}' $HOSTLIST; read NUM; }

[ $NUM -le $LINECOUNT ] || { echo "Your input number is invalid!"; exit; }
PARAM=`whoami`@`awk -v num=$NUM 'NR==num {print $2}' $HOSTLIST` && rm -rf $HOSTLIST
ssh $PARAM
