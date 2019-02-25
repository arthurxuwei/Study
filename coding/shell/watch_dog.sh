 
[ 2 -gt $# ] && echo -e "\tUsage:$0 {start|stop} {cmd}\n" && exit 1
  
pid_file="/tmp/`basename $2`.pid"
case $1 in
    start)
        shift
        pid=00
        last_stat=0
        last_time=`date +%s`
        if [ -f $pid_file ]
        then
            echo "$pid_file exist, check whether `basename $1` is runing or not."
            exit 2
        fi
        echo "pid" > $pid_file || exit 3
        while :
        do
            if [ ! -f /proc/$pid/stat ]
            then
                trap "rm -f $pid_file;exit 5" 2 3 15
                $* > /dev/null 2>/dev/null &
                pid=$!
                sed -i "1c\\$pid" $pid_file
            else
                let "interval=`date +%s`-$last_time"
                [ 60 -gt $interval ] && sleep 4 && continue
                cur_stat=`cat /proc/$pid/stat|awk 'END{print $15+$16}'`
                [ $cur_stat -ne $last_stat ] && last_stat=$cur_stat || kill -9 $pid
                last_time=`date +%s`
            fi
        done >/dev/null 2>/dev/null &
        echo "$!" >> $pid_file
        ;;
    stop)
        [ ! -f $pid_file ] && echo "Pid file lost or `basename $2` not running ..." && exit 4
        cat $pid_file|xargs -i kill -9 {}
        rm -f $pid_file
        ;;
    *)
        echo -e "\tUsage:$0 {start|stop} {cmd}\n"
        ;;
esac