#dir size
du -h --max-depth=1 {dir}

#check file
if [ ! -f /tmp/foo.txt ]; then
    echo "File not found!"
fi
#check dir
if [ -d "$LINK_OR_DIR" ]; then 
  if [ -L "$LINK_OR_DIR" ]; then
    # It is a symlink!
    # Symbolic link specific commands go here.
    rm "$LINK_OR_DIR"
  else
    # It's a directory!
    # Directory command goes here.
    rmdir "$LINK_OR_DIR"
  fi
fi

#process
ipcs ipcrm (shared memory,IPC message queue,signal)
#cpu info
lscpu vmstat mpstat iostat sar
#mem
free vmstat mpstat iostat sar
free -m | grep Mem | awk '{print ($3 / $2)*100}'
#hardware info
lshw
hwinfo
#pci bus info
lspci
#usb bus info
lsusb
#block device info
lsblk
#SCSI device info
lsscsi
#all
sosreport
#network
netstat ss

//
chmod chown chgrp --reference

//more ls
stat {file}

//file type
file {file}

//
diff cmp comm md5sum

//
alias   ''{cmd} \{cmd}
unalias

//xargs
file * | grep ASCII | cut -d":" -f1 | xargs -t -n2 ls -ltr  
ls | xargs -t -i mv {} {}.bak

//rename
rename


find . -name "sqlplus*" -ok {} \;

//word replace 
m4 

//freeze process
skill -STOP -CONT 
//priority of process
snice


