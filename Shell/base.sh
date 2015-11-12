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


#cpu info
lscpu
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

//example 2
grep -Eo '([0-9]{1,3}\.){3}[0-9]{1,3}' ip_practices.txt

//
chmod chown chgrp --reference

//more ls
stat {file}

//file type
file {file}


//
diff cmp comm md5sum

 