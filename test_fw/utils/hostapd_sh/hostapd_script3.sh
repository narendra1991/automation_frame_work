/sbin/udevd -d &

insmod /opt/ipnc/modules/compat.ko
insmod /opt/ipnc/modules/cfg80211.ko
insmod /opt/ipnc/modules/ath6kl_usb.ko reg_domain=0x10

#ifconfig wlan0 up
ifconfig wlan0 192.168.44.1 up

/usr/local/bin/hostapd -d /etc/hostapd.conf &

cd /sbin/
udhcpd -f /etc/udhcpd.conf &
