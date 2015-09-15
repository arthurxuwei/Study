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

//log
2013-09-08 21:00:54 SMTP connection from [78.110.75.245]:5387 (TCP/IP connection count = 20)
2013-09-08 21:00:54 SMTP connection from [188.175.142.13]:34332 (TCP/IP connection count = 20)
2013-09-08 21:45:41 SMTP connection from [58.137.11.145]:51984 (TCP/IP connection count = 20)
2013-09-08 21:49:26 SMTP connection from [109.93.248.151]:22273 (TCP/IP connection count = 20)
2013-09-08 21:49:27 SMTP connection from [37.131.64.203]:7906 (TCP/IP connection count = 20)

//shell
awk -F'[][]' '{print $2}' ip_practices.txt 

//example 2
grep -Eo '([0-9]{1,3}\.){3}[0-9]{1,3}' ip_practices.txt


