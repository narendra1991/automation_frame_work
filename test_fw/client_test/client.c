#include "network.h"
//#define WIFI_SWITCH
extern char buf_s[BUFFSIZE];
extern char buf_r[BUFFSIZE];
extern int socket_test;
extern int sent_bytes;
extern int read_bytes;
FILE *fp = NULL;
char command[512];
char master_test[128];
char sub_test[256];
char master_buf[896];
char startup[12][128] = {"echo >/dev/ttyUSB0",
"echo boot >/dev/ttyUSB0",
"echo root >/dev/ttyUSB0",
"echo >/dev/ttyUSB1",
"echo >/dev/ttyUSB2",
"echo boot >/dev/ttyUSB2",
"echo root >/dev/ttyUSB2",
"echo >/dev/ttyUSB3",
"echo >/dev/ttyUSB4",
"echo boot >/dev/ttyUSB4",
"echo root >/dev/ttyUSB4",
"echo >/dev/ttyUSB5"};
char uart1_stop[6][128] = {"echo usart_test stop >/dev/ttyUSB0", "echo usart_test stop >/dev/ttyUSB1", "echo usart_test stop >/dev/ttyUSB2", "echo usart_test stop >/dev/ttyUSB3", "echo usart_test stop >/dev/ttyUSB4", "echo usart_test stop >/dev/ttyUSB5"};
char uart1_triggers[36][128] = {"echo usart_test -b 9600 start >/dev/ttyUSB0",
"echo usart_test -b 19200 start >/dev/ttyUSB0",
"echo usart_test -b 38400 start >/dev/ttyUSB0",
"echo usart_test -b 57600 start >/dev/ttyUSB0",
"echo usart_test -b 115200 start >/dev/ttyUSB0",
"echo usart_test -b 230400 start >/dev/ttyUSB0",
"echo usart_test -b 9600 start >/dev/ttyUSB1",
"echo usart_test -b 19200 start >/dev/ttyUSB1",
"echo usart_test -b 38400 start >/dev/ttyUSB1",
"echo usart_test -b 57600 start >/dev/ttyUSB1",
"echo usart_test -b 115200 start >/dev/ttyUSB1",
"echo usart_test -b 230400 start >/dev/ttyUSB1",
"echo usart_test -b 9600 start >/dev/ttyUSB2",
"echo usart_test -b 19200 start >/dev/ttyUSB2",
"echo usart_test -b 38400 start >/dev/ttyUSB2",
"echo usart_test -b 57600 start >/dev/ttyUSB2",
"echo usart_test -b 115200 start >/dev/ttyUSB2",
"echo usart_test -b 230400 start >/dev/ttyUSB2",
"echo usart_test -b 9600 start >/dev/ttyUSB3",
"echo usart_test -b 19200 start >/dev/ttyUSB3",
"echo usart_test -b 38400 start >/dev/ttyUSB3",
"echo usart_test -b 57600 start >/dev/ttyUSB3",
"echo usart_test -b 115200 start >/dev/ttyUSB3",
"echo usart_test -b 230400 start >/dev/ttyUSB3",
"echo usart_test -b 9600 start >/dev/ttyUSB4",
"echo usart_test -b 19200 start >/dev/ttyUSB4",
"echo usart_test -b 38400 start >/dev/ttyUSB4",
"echo usart_test -b 57600 start >/dev/ttyUSB4",
"echo usart_test -b 115200 start >/dev/ttyUSB4",
"echo usart_test -b 230400 start >/dev/ttyUSB4",
"echo usart_test -b 9600 start >/dev/ttyUSB5",
"echo usart_test -b 19200 start >/dev/ttyUSB5",
"echo usart_test -b 38400 start >/dev/ttyUSB5",
"echo usart_test -b 57600 start >/dev/ttyUSB5",
"echo usart_test -b 115200 start >/dev/ttyUSB5",
"echo usart_test -b 230400 start >/dev/ttyUSB5",
};
char uart0_nand_test[][256] = {"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB0",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB0", //1
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB0",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB0", //2
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB0",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB0", //3
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB0", //4
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB0",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB0", //5
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB0",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB0", //6
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB0",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB0", // 7
"echo mw.w 0x80000000 0x1122 0x3E20000 >/dev/ttyUSB0", //8
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB0",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB0",//9
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB0",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB0", // 10
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB0",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB0", //11
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB0",//12
"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB1",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB1",
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB1",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB1",
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB1",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB1",
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB1",
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB1",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB1",
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB1",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB1",
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB1",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB1",
"echo mw.w 0x80000000 0x1122 0x3E20000 >/dev/ttyUSB1",
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB1",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB1",
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB1",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB1",
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB1",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB1",
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB1"
"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB2",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB2",
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB2",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB2",
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB2",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB2",
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB2",
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB2",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB2",
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB2",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB2",
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB2",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB2",
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB2",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB2",
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB2",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB2",
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB2",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB2",
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB2"
"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB3",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB3",
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB3",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB3",
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB3",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB3",
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB3",
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB3",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB3",
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB3",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB3",
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB3",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB3",
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB3",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB3",
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB3",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB3",
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB3",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB3",
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB3"
"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB4",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB4",
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB4",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB4",
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB4",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB4",
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB4",
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB4",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB4",
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB4",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB4",
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB4",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB4",
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB4",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB4",
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB4",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB4",
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB4",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB4",
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB4"
"echo mw.l 0x80000000 0x11223344 0x400000 >/dev/ttyUSB5",
"echo md.l 0x80FFFFF0 0x10 >/dev/ttyUSB5",
"echo mw.l 0x81000000 0xaabbccdd 0x400000 >/dev/ttyUSB5",
"echo md.l 0x81FFFFF0 0x10 >/dev/ttyUSB5",
"echo mw.l 0x80000000 0x11225AA5 0x1F00000 >/dev/ttyUSB5",
"echo md.l 0x87BFFFE0 0x10 >/dev/ttyUSB5",
"echo mw.l 0x80000000 0x11225AA5 0x1F10000 >/dev/ttyUSB5",
"echo mw.w 0x80000000 0x1122 0x800000 >/dev/ttyUSB5",
"echo md.w 0x80FFFFF0 0x10 >/dev/ttyUSB5",
"echo mw.w 0x81000000 0xaabb 0x800000 >/dev/ttyUSB5",
"echo md.w 0x81FFFFF0 0x10 >/dev/ttyUSB5",
"echo mw.w 0x80000000 0x1010 0x3E00000 >/dev/ttyUSB5",
"echo md.w 0x87BFFFE0 0x20 >/dev/ttyUSB5",
"echo mw.b 0x80000000 0x11 0x1000000  >/dev/ttyUSB5",
"echo md.b 0x80FFFFF0 0x20 >/dev/ttyUSB5",
"echo mw.b 0x81000000 0xaa 0x1000000  >/dev/ttyUSB5",
"echo md.b 0x81FFFFF0 0x20 >/dev/ttyUSB5",
"echo mw.b 0x80000000 0x10 0x7C00000  >/dev/ttyUSB5",
"echo md.b 0x87BFFFE0 0x30 >/dev/ttyUSB5",
"echo mw.b 0x80000000 0x25 0x7C40000   >/dev/ttyUSB5"};
char uart0_reboot[][64] = {"echo reboot >/dev/ttyUSB0", "echo reboot >/dev/ttyUSB1", "echo reboot >/dev/ttyUSB2", "echo reboot >/dev/ttyUSB3", "echo reboot >/dev/ttyUSB4", "echo reboot >/dev/ttyUSB5"};
char uart0_hostapd_conf[3][6][128] = { {"echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB0", "echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB1", "echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB2", "echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB3", "echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB4", "echo cp /opt/ipnc/hostapd1.conf /etc/hostapd.conf >/dev/ttyUSB5"}, {"echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB0", "echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB1", "echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB2", "echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB3", "echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB4", "echo cp /opt/ipnc/hostapd2.conf /etc/hostapd.conf >/dev/ttyUSB5"} };
char uart0_hostapd_sh[3][6][128] = { {"echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB0", "echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB1", "echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB2", "echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB3", "echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB4", "echo cp hostapd_script1.sh /home/root/hostapd_script.sh >/dev/ttyUSB5"}, {"echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB0", "echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB1", "echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB2", "echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB3", "echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB4", "echo cp hostapd_script2.sh /home/root/hostapd_script.sh >/dev/ttyUSB5"}, {"echo cp hostapd_script3.sh /home/root/hostapd_script.sh >/dev/ttyUSB0", "echo cp hostapd_script3.sh /home/root/hostapd_script.sh >/dev/ttyUSB1", "echo cp hostapd_script3.sh hostapd_script.sh >/dev/ttyUSB2", "echo cp hostapd_script3.sh /home/root/hostapd_script.sh >/dev/ttyUSB3", "echo cp hostapd_script3.sh /home/root/hostapd_script.sh >/dev/ttyUSB4", "echo cp hostapd_script3.sh /home/root/hostapd_script.sh >/dev/ttyUSB5"} };
char uart0_udhcpd[3][6][128] = { {"echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB0", "echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB1", "echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB2", "echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB3", "echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB4", "echo cp udhcpd1.conf /etc/udhcpd.conf >/dev/ttyUSB5"}, {"echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB0", "echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB1", "echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB2", "echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB3", "echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB4", "echo cp udhcpd2.conf /etc/udhcpd.conf >/dev/ttyUSB5"}, {"echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB0", "echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB1", "echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB2", "echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB3", "echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB4", "echo cp udhcpd3.conf /etc/udhcpd.conf >/dev/ttyUSB5"} };
char interface[][64] = {"sudo cp interfaces1 /etc/network/interfaces", "sudo cp interfaces2 /etc/network/interfaces", "sudo cp interfaces3 /etc/network/interfaces", "sudo cp interfaces4 /etc/network/interfaces", "sudo cp interfaces5 /etc/network/interfaces", "sudo cp interfaces6 /etc/network/interfaces"};
char uart0_relocate[6][128] = {"echo cd /opt/ipnc/ >/dev/ttyUSB0", "echo cd /opt/ipnc/ >/dev/ttyUSB1", "echo cd /opt/ipnc/ >/dev/ttyUSB2", "echo cd /opt/ipnc/ >/dev/ttyUSB3", "echo cd /opt/ipnc/ >/dev/ttyUSB4", "echo cd /opt/ipnc/ >/dev/ttyUSB5"};
char uart0_enter[6][128] = {"echo >/dev/ttyUSB0", "echo >/dev/ttyUSB1", "echo >/dev/ttyUSB2", "echo >/dev/ttyUSB3", "echo >/dev/ttyUSB4", "echo >/dev/ttyUSB5"};
char uart1_enter[6][128] = {"echo >/dev/ttyUSB0", "echo >/dev/ttyUSB1", "echo >/dev/ttyUSB2", "echo >/dev/ttyUSB3", "echo >/dev/ttyUSB4", "echo >/dev/ttyUSB5"};
char uart0_boot[6][128] = {"echo boot >/dev/ttyUSB0", "echo boot >/dev/ttyUSB1", "echo boot >/dev/ttyUSB2", "echo boot >/dev/ttyUSB3", "echo boot >/dev/ttyUSB4", "echo boot >/dev/ttyUSB5"};
char uart0_root[6][128] = {"echo root >/dev/ttyUSB0", "echo root >/dev/ttyUSB1", "echo root >/dev/ttyUSB2", "echo root >/dev/ttyUSB3", "echo root >/dev/ttyUSB4", "echo root >/dev/ttyUSB5"};
char uart0_server[6][128] = {"echo ./server 3000 >/dev/ttyUSB0", "echo ./server 3000 >/dev/ttyUSB1", "echo ./server 3000 >/dev/ttyUSB2", "echo ./server 3000 >/dev/ttyUSB3", "echo ./server 3000 >/dev/ttyUSB4", "echo ./server 3000 >/dev/ttyUSB5"};
char test_result_files[3][128] = {"test_result1.csv", "test_result2.csv", "test_result3.csv"};
char rm_test_result_files[3][128] = {"rm test_result1.csv", "rm test_result2.csv", "rm test_result3.csv"};
char test_config[][128] = {"test_config1", "test_config2", "test_config3"};
char socket_ip[][128] = {"192.168.42.1", "192.168.43.1", "192.168.44.1"};
char ping_test[][128] = {"./ping 192.168.42.1 -c 4", "./ping 192.168.43.1 -c 4", "./ping 192.168.44.1 -c 4"}; 
char uart0_wlan0_down[][128] = {"echo ifconfig wlan0 down >/dev/ttyUSB0", "echo ifconfig wlan0 down >/dev/ttyUSB1", "echo ifconfig wlan0 down >/dev/ttyUSB2", "echo ifconfig wlan0 down >/dev/ttyUSB3", "echo ifconfig wlan0 down >/dev/ttyUSB4", "echo ifconfig wlan0 down >/dev/ttyUSB5"};
char sky_test[512] = "sudo java -Djava.ext.dirs= -cp lib/*:out/production/jmavsim.jar me.drton.jmavsim.Simulator& PID=$! ; sleep 60; kill -15 $PID; echo finished_sky_test";
int uart0_temp = -1;
int send_receive(char *master, char *sub, char *command);
int quit_test();
int gen_rand(char *buf, int len);
int validate_wifi_size(char *sub);
int validate_wifi_counter(char *sub);
int main(int argc, char *argv[])
{
	int ADRESS_PORT = 0;
	int nIndex2 = 0;
	int nIndex = 0;
	int nboard = 0;
	int RESULT = 200;
	if(argc < 4)
	{
		printf("\nHELP: client num_boards USB0_select USB1_select\n");
		return -1;
	}
	nboard = atoi(argv[1]);
	if(nboard)
	{
		ADRESS_PORT = 3000; 
		if(nboard > 3)
		{
			printf("\nEntered out of range value for number of boards, resetting it to 1 as default\n");
			nboard = 1;
		}
		for(nIndex2 = 0; nIndex2 < nboard; nIndex2++)
		{
			int uart0 = atoi(argv[2 + 2 * nIndex2]);
			int nIndex1 = 0;
			system(uart0_wlan0_down[uart0]);
			for(nIndex1 = 0; nIndex1 < 5; nIndex1++)
			{
				system(uart0_enter[uart0]);
				printf("\nSent enter to uart0\n");
				sleep(1);
			}
		}
		for(nIndex2 = 0; nIndex2 < nboard; nIndex2++)
		{
			int uart0 = atoi(argv[2 + 2 * nIndex2]);
			int uart1 = atoi(argv[3 + 2 * nIndex2]);
			FILE *sfp = NULL;
			int nIndex1 = 0;
			if((uart0 != uart1)&&(uart0 <= 5)&&(uart1 <= 5))
			{
				system("nmcli nm wifi off");
				printf("\nnmcli nm wifi off\n");
				sleep(5);
				system(uart0_hostapd_conf[nIndex2][uart0]);
				printf("\n%s\n", uart0_hostapd_conf[nIndex2][uart0]);
				system(uart0_hostapd_sh[nIndex2][uart0]);
				printf("\n%s\n", uart0_hostapd_sh[nIndex2][uart0]);
				system(uart0_udhcpd[nIndex2][uart0]);
				printf("\n%s\n", uart0_udhcpd[nIndex2][uart0]);
				system(interface[nIndex2]);
				printf("\n%s\n", interface[nIndex2]);
				system(uart0_reboot[uart0]);
				sleep(20);
				for(nIndex1 = 0; nIndex1 < 30; nIndex1++)
				{
					system(uart0_enter[uart0]);
					printf("\nSent enter to uart0\n");
					sleep(1);
				}
				for(nIndex1 = 0; nIndex1 < 2; nIndex1++)
				{
					printf("\nNand command %d\n", nIndex1);
					system(uart0_nand_test[uart0 * 21 + nIndex1]);
					system("echo >/dev/USB0");
					sleep(5);
				}
				system(uart0_boot[uart0]);
				printf("\nSent boot to uart0\n");
				sleep(20);
				{
					int result_temp = 200;
					FILE *temfp = NULL;
					system("nmcli nm wifi on");
					while(result_temp)
					{
						system(ping_test[nIndex2]);
						sleep(5);
						temfp = fopen("test_result.txt", "r");
						printf("value: %d\n", result_temp);
						fscanf(temfp, "%d", &result_temp);
						fclose(temfp);
					}
					printf("value: %d\n", result_temp);
				}
				system(uart0_root[uart0]);
				sleep(5);
				printf("\nSent root to uart0\n");
				system(uart1_enter[uart1]);
				printf("\nSent enter to uart1\n");	
				sleep(2);
				system(uart1_enter[uart1]);
				printf("\nSent enter to uart1\n");
				system(uart0_relocate[uart0]);
				printf("\nsent reloaction command to client\n");
				sleep(5);
				system(uart0_server[uart0]);
				printf("\nsent test_trigger command to client\n");
				sleep(5);
				socket_test = make_socket(ADRESS_PORT, CLIENT_SOCKET, socket_ip[nIndex2]);
				if(socket_test <= 0)
				{
					printf("\nFailed to created socket\n");
					close_socket(socket_test);
					return 1; 
				}
				else
				{
					printf("\nCreated socket successfully: %d\n", socket_test);
				}
				{
					int test_config_len = 0;
					printf("\nSending test config file name\n");
					memset(buf_s, '\0', BUFFSIZE);
					test_config_len = strlen(test_config[nIndex2]);
					strcpy(buf_s, test_config[nIndex2]);
					do
					{
						sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
						if(buf_s[BUFFSIZE - 1] == '\0')
						{
							sent_bytes = strlen(buf_s);
						}
						if(sent_bytes == test_config_len)
						{
							sent_bytes = 0;
							break;
						}
					}while(1);
					printf("\nsent [%s] from client to server\n", buf_s);
					do
					{
						memset(buf_r, '\0', BUFFSIZE);
						read_bytes = read (socket_test, buf_r, BUFFSIZE);
						if(buf_r[BUFFSIZE - 1] == '\0')
						{
							read_bytes = strlen(buf_r);
						}
						if(strncmp(buf_r, buf_s, test_config_len) == 0)
						{
							read_bytes = 0;
							break;
						}
					}while(1);
					printf("\nread [%s] from sever to client\n", buf_r);
				}
				{
					system(rm_test_result_files[nIndex2]);
					printf("\nopening %d config %s\n", nIndex2, test_config[nIndex2]);
					sfp = fopen(test_config[nIndex2], "r");
					nIndex1 = 0;
					do
					{
						if(fgets(master_buf, 896, sfp) != NULL)
						{
							long int read_length = 0;
							int str_count = 0;
							printf("Read string: %s\n", master_buf);
							read_length = strlen(master_buf);
							printf("length of read string: %ld\n", read_length);
							memset(master_test, '\0', 128);
							memset(sub_test, '\0', 256);
							str_count = 0;
							for(nIndex = 0; nIndex < read_length; nIndex++)
							{
								if(master_buf[nIndex] != ',')
								{
									if(str_count == 0)
									{
										master_test[nIndex1] = master_buf[nIndex];
										nIndex1++;
									}
                        						else if(str_count == 1)
									{
										sub_test[nIndex1] = master_buf[nIndex];
										nIndex1++;
									}
									else if(str_count == 2)
									{
										command[nIndex1] = master_buf[nIndex];
										nIndex1++;
									}
								}
								else
								{ 
									if(str_count == 0)
									{
										master_test[nIndex1] = '\0';
										printf("Master Test: %s\n", master_test);
										nIndex1 = 0;
										str_count++;
									}
									else if(str_count == 1)
									{
										sub_test[nIndex1] = '\0';
										printf("Sub Test: %s\n", sub_test);
										nIndex1 = 0;
										str_count++;
									}
									else if(str_count == 2)
									{
										int uart_test = 0;
										command[nIndex1] = '\0';
										printf("Command: %s\n", command);
										nIndex1 = 0;
										str_count++;
										if(strcmp(master_test, "UART1_TEST") == 0)
										{
											if((!strcmp(sub_test, "uart1_40_9600")) || (!strcmp(sub_test, "uart1_50_9600")) || (!strcmp(sub_test, "uart1_60_9600")) || (!strcmp(sub_test, "uart1_70_9600")) || (!strcmp(sub_test, "uart1_80_9600")) || (!strcmp(sub_test, "uart1_90_9600")) || (!strcmp(sub_test, "uart1_48_9600")) || (!strcmp(sub_test, "uart1_58_9600")) || (!strcmp(sub_test, "uart1_68_9600")) || (!strcmp(sub_test, "uart1_78_9600")) || (!strcmp(sub_test, "uart1_88_9600")) || (!strcmp(sub_test, "uart1_98_9600")))
											{
												sleep(3);
												system(uart1_triggers[uart1 * 6]);
												sleep(3);
												uart_test = 1;
											}
											else if((!strcmp(sub_test, "uart1_40_19200")) || (!strcmp(sub_test, "uart1_50_19200")) || (!strcmp(sub_test, "uart1_60_19200")) || (!strcmp(sub_test, "uart1_70_19200")) || (!strcmp(sub_test, "uart1_80_19200")) || (!strcmp(sub_test, "uart1_90_19200")) || (!strcmp(sub_test, "uart1_48_19200")) || (!strcmp(sub_test, "uart1_58_19200")) || (!strcmp(sub_test, "uart1_68_19200")) || (!strcmp(sub_test, "uart1_78_19200")) || (!strcmp(sub_test, "uart1_88_19200")) || (!strcmp(sub_test, "uart1_98_19200")))
											{
												sleep(3);
												system(uart1_triggers[(uart1 * 6) + 1]);
												sleep(3);
												uart_test = 1;
											}
											else if((!strcmp(sub_test, "uart1_40_38400")) || (!strcmp(sub_test, "uart1_50_38400")) || (!strcmp(sub_test, "uart1_60_38400")) || (!strcmp(sub_test, "uart1_70_38400")) || (!strcmp(sub_test, "uart1_80_38400")) || (!strcmp(sub_test, "uart1_90_38400")) || (!strcmp(sub_test, "uart1_48_38400")) || (!strcmp(sub_test, "uart1_58_38400")) || (!strcmp(sub_test, "uart1_68_38400")) || (!strcmp(sub_test, "uart1_78_38400")) || (!strcmp(sub_test, "uart1_88_38400")) || (!strcmp(sub_test, "uart1_98_38400")))
											{
												sleep(3);
												system(uart1_triggers[(uart1 * 6) + 2]);
												sleep(3);
												uart_test = 1;
											}
											else if((!strcmp(sub_test, "uart1_40_57600")) || (!strcmp(sub_test, "uart1_50_57600")) || (!strcmp(sub_test, "uart1_60_57600")) || (!strcmp(sub_test, "uart1_70_57600")) || (!strcmp(sub_test, "uart1_80_57600")) || (!strcmp(sub_test, "uart1_90_57600")) || (!strcmp(sub_test, "uart1_48_57600")) || (!strcmp(sub_test, "uart1_58_57600")) || (!strcmp(sub_test, "uart1_68_57600")) || (!strcmp(sub_test, "uart1_78_57600")) || (!strcmp(sub_test, "uart1_88_57600")) || (!strcmp(sub_test, "uart1_98_57600")))
											{
												sleep(3);
												system(uart1_triggers[(uart1 * 6) + 3]);
												sleep(3);
												uart_test = 1;
											}
											else if((!strcmp(sub_test, "uart1_40_115200")) || (!strcmp(sub_test, "uart1_50_115200")) || (!strcmp(sub_test, "uart1_60_115200")) || (!strcmp(sub_test, "uart1_70_115200")) || (!strcmp(sub_test, "uart1_80_115200")) || (!strcmp(sub_test, "uart1_90_115200")) || (!strcmp(sub_test, "uart1_48_115200")) || (!strcmp(sub_test, "uart1_58_115200")) || (!strcmp(sub_test, "uart1_68_115200")) || (!strcmp(sub_test, "uart1_78_115200")) || (!strcmp(sub_test, "uart1_88_115200")) || (!strcmp(sub_test, "uart1_98_115200")))
											{
												sleep(3);
												system(uart1_triggers[(uart1 * 6) + 5]);
												sleep(3);
												uart_test = 1;
											}
											else if((!strcmp(sub_test, "uart1_40_230400")) || (!strcmp(sub_test, "uart1_50_230400")) || (!strcmp(sub_test, "uart1_60_230400")) || (!strcmp(sub_test, "uart1_70_230400")) || (!strcmp(sub_test, "uart1_80_230400")) || (!strcmp(sub_test, "uart1_90_230400")) || (!strcmp(sub_test, "uart1_48_230400")) || (!strcmp(sub_test, "uart1_58_230400")) || (!strcmp(sub_test, "uart1_68_230400")) || (!strcmp(sub_test, "uart1_78_230400")) || (!strcmp(sub_test, "uart1_88_230400")) || (!strcmp(sub_test, "uart1_98_230400")))
											{
												sleep(3);
												system(uart1_triggers[(uart1 * 6) + 5]);
												sleep(3);
												uart_test = 1;
											}
										}
										printf("\nMaster : %s\n", master_test);
										if(strcmp(master_test, "SKY_TEST") == 0)
										{
											uart0_temp = uart0;
										}
										RESULT = send_receive(master_test, sub_test, command);
										{
											FILE *base_fp = NULL;
											base_fp = fopen(test_result_files[nIndex2], "a");
											fprintf(base_fp, "%s,", master_test);
											fprintf(base_fp, "%s,", sub_test);
											if(!RESULT)
											{
												fprintf(base_fp, "PASS\n");
											}
											else if(RESULT == 1)
											{
												fprintf(base_fp, "FAIL\n");
											}
											else
											{
												fprintf(base_fp, "NOT_TESTED\n");
											}
											fclose(base_fp);
										}
										if(uart_test)
										{
											system(uart1_stop[uart1]);
										}
									}
								}
							}
						}
						else
						{
							printf("\nTest case parsing is done:\n");
							quit_test();
							close_socket(socket_test);
							break;
						}
					}while(1);
					fclose(sfp);
				}
				system(uart0_wlan0_down[uart0]);
				for(nIndex1 = 0; nIndex1 < 5; nIndex1++)
				{
					system(uart0_enter[uart0]);
					printf("\nSent enter to uart0\n");
					sleep(1);
				}
				if(nIndex2 == (nboard - 1))
				{
					system("nmcli nm wifi off");
					printf("\nnmcli nm wifi off\n");
				}
			}
			else
			{
				printf("\nPlease enter UART port numbers with in the supported range\n");
			}

		}
	}
	else
	{
		printf("\nPlease enter valid number of board to excute\n");
		return -1;
	}
	return 0;
}
int quit_test()
{
	memset(buf_s, '\0', BUFFSIZE);
	strcpy(buf_s, "quit");
	do
	{
		sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
		if(buf_s[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_s);
		}
		if(sent_bytes == 4)
		{
			sent_bytes = 0;
			break;
		}
	}while(1);
	printf("\nsent [%s] from client to server\n", buf_s);
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (socket_test, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if(strncmp(buf_r, buf_s, 4) == 0)
		{
			read_bytes = 0;
			break;
		}
	}while(1);
	printf("\nread [%s] from sever to client\n", buf_r);
	return 0;
}
int send_receive(char *master, char *sub, char *command)
{
	int len = 0;
	int ret = 200;
	len = strlen(master);
	memset(buf_s, '\0', BUFFSIZE);
	printf("\nMaster 1: %s\n", master);
	strncpy(buf_s, master, strlen(master));
	do
	{
		sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0);
		if(buf_s[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_s);
		}
		if(sent_bytes == len)
		{
			sent_bytes = 0;
			printf("\nSent Master: %s\n", buf_s);
			break;
		}
	}while(1);
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (socket_test, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if(read_bytes == len) 
		{
			if(!strncmp(buf_r, buf_s, len))
			{
				printf("\nRead back Master from Server: %s\n", buf_r);
				read_bytes = 0;	
				break;
			}
		}
	}while(1);
	len = strlen(sub);
	memset(buf_s, '\0', BUFFSIZE);
	strncpy(buf_s, sub, strlen(sub));
	do
	{
		sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
		if(buf_s[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_s);
		}
		if(sent_bytes == len)
		{
			sent_bytes = 0;
			printf("\nSent Sub: %s\n", buf_s);
			break;
		}
	}while(1);
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (socket_test, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if(read_bytes == len) 
		{
			if(!strncmp(buf_r, buf_s, len))
			{
				printf("\nRead back Sub from Server: %s\n", buf_r);
				read_bytes = 0;	
				break;
			}
		}
	}while(1);
	if(strcmp(master, "WIFI_TEST") == 0)
	{
		int size = 0;
		int ref_counter = 0;
		int counter = 0;
		size = validate_wifi_size(sub);
		ref_counter = validate_wifi_counter(sub);
		if(!size)
		{
			printf("\nSetting valid size of 1024 for invalid size input to wifi test\n");
			size = 1024;
		}
		do
		{
			memset(buf_s, '\0', BUFFSIZE);
			gen_rand(buf_s, size);
			sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
			if(buf_s[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_s);
			}
			if(sent_bytes == size)
			{
				printf("\nSent Wifi test data to server: %d\n", size);
				do
				{
					memset(buf_r, '\0', BUFFSIZE);
					read_bytes = read (socket_test, buf_r, BUFFSIZE);
					if(buf_r[BUFFSIZE - 1] == '\0')
					{
						read_bytes = strlen(buf_r);
					}
					if(read_bytes == sent_bytes) 
					{
						if(!strncmp(buf_r, buf_s, size))
						{
							printf("\nRead back data from Server: %d\n", counter);
							ret = 0;
						}
						else
						{
							ret = 1;
						}
						read_bytes = 0;	
						counter++;
						break;
					}
				}while(1);
				sent_bytes = 0;
				if((ret) || (counter == ref_counter))
				{
					break;
				}
			}
		}while(1);
	}
	else if(strcmp(master, "SKY_TEST") == 0)
	{
		len = strlen(command);
		strncpy(buf_s, command, strlen(command));
		do
		{
			sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
			if(buf_s[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_s);
			}
			if(sent_bytes == len)
			{
				sent_bytes = 0;
				printf("\nSent Command: %s\n", buf_s);
				break;
			}
		}while(1);
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (socket_test, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if(read_bytes == len) 
			{
				if(!strncmp(buf_r, buf_s, len))
				{
					printf("\nRead back Command from Server: %s\n", buf_r);
					read_bytes = 0;	
					break;
				}
			}
		}while(1);
		printf("\nBUCKD TEST: %s\n", command);
		sleep(1);
		system(sky_test);
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (socket_test, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if((read_bytes > 0)&&(read_bytes <= 10))
			{
				read_bytes = 0;	
				printf("\nReceived result from server: %s\n", buf_r);
				break;
			}
		}while(1);
		do
		{
			sent_bytes = send(socket_test, buf_r, BUFFSIZE, 0 );
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_r);
			}
			if((sent_bytes > 0)&&(sent_bytes <= 10))
			{
				sent_bytes = 0;
				printf("\nSent back result to server: %s\n", buf_r);
				break;
			}
		}while(1);
		if(strncmp(buf_r, "PASS", 4) == 0)
		{
			return 0;
		}
		else if(strncmp(buf_r, "FAIL", 4) == 0)
		{
			return 1;
		}
		else if(strncmp(buf_r, "NOT_TESTED", 10) == 0)
		{
			return -1;
		}
	}
	else
	{
		len = strlen(command);
		memset(buf_s, '\0', BUFFSIZE);
		strncpy(buf_s, command, strlen(command));
		do
		{
			sent_bytes = send(socket_test, buf_s, BUFFSIZE, 0 );
			if(buf_s[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_s);
			}
			if(sent_bytes == len)
			{
				sent_bytes = 0;
				printf("\nSent Command: %s\n", buf_s);
				break;
			}
		}while(1);
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (socket_test, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if(read_bytes == len) 
			{
				if(!strncmp(buf_r, buf_s, len))
				{
					printf("\nRead back Command from Server: %s\n", buf_r);
					read_bytes = 0;	
					break;
				}
			}
		}while(1);
		if(strcmp(master,"LTP_TEST"))
		{
			do
			{
				memset(buf_r, '\0', BUFFSIZE);
				read_bytes = read (socket_test, buf_r, BUFFSIZE);
				if(buf_r[BUFFSIZE - 1] == '\0')
				{
					read_bytes = strlen(buf_r);
				}
				if((read_bytes > 0)&&(read_bytes <= 10))
				{
					read_bytes = 0;	
					printf("\nReceived result from server: %s\n", buf_r);
					break;
				}
			}while(1);
			do
			{
				sent_bytes = send(socket_test, buf_r, BUFFSIZE, 0 );
				if(buf_r[BUFFSIZE - 1] == '\0')
				{
					sent_bytes = strlen(buf_r);
				}
				if((sent_bytes > 0)&&(sent_bytes <= 10))
				{
					sent_bytes = 0;
					printf("\nSent back result to server: %s\n", buf_r);
					break;
				}
			}while(1);

			if(strncmp(buf_r, "PASS", 4) == 0)
			{
				return 0;
			}
			else if(strncmp(buf_r, "FAIL", 4) == 0)
			{
				return 1;
			}
			else if(strncmp(buf_r, "NOT_TESTED", 10) == 0)
			{
				return -1;
			}
		}
		else
		{
			printf("\nNeed analysis code for LTP\n");
			ret = -1;			
		}
	}
	return ret;
}
int gen_rand(char *buf, int len)
{
	int nIndex = 0;
	for(nIndex = 0; nIndex < len; nIndex++)
	{
		buf[nIndex] =  'a' + (rand() % 26);
	}
	return 0;
}
int validate_wifi_size(char *sub)
{
	int size = 0;
	if((strcmp(sub, "wifi_1447_1024") == 0) || (strcmp(sub, "wifi_1447_10240") == 0) || (strcmp(sub, "wifi_1447_1024*1024_stress") == 0))
	{
		size = 1447;
	}
	else if((strcmp(sub, "wifi_1440_1024") == 0) || (strcmp(sub, "wifi_1440_10240") == 0))
	{
		size = 1440;
	}
	else if((strcmp(sub, "wifi_1200_1024") == 0) || (strcmp(sub, "wifi_1200_10240") == 0))
	{
		size = 1200;
	}
	else if((strcmp(sub, "wifi_1024_1024") == 0) || (strcmp(sub, "wifi_1024_10240") == 0))
	{
		size = 1024;
	}
	else if((strcmp(sub, "wifi_980_1024") == 0) || (strcmp(sub, "wifi_980_10240") == 0))
	{
		size = 980;
	}
	else if((strcmp(sub, "wifi_800_1024") == 0) || (strcmp(sub, "wifi_800_10240") == 0))
	{
		size = 800;
	}
	else if((strcmp(sub, "wifi_720_1024") == 0) || (strcmp(sub, "wifi_720_10240") == 0))
	{
		size = 720;
	}
	else if((strcmp(sub, "wifi_640_1024") == 0) || (strcmp(sub, "wifi_640_10240") == 0))
	{
		size = 640;
	}
	else if((strcmp(sub, "wifi_512_1024") == 0) || (strcmp(sub, "wifi_512_10240") == 0))
	{
		size = 512;
	}
	else if((strcmp(sub, "wifi_480_1024") == 0) || (strcmp(sub, "wifi_480_10240") == 0))
	{
		size = 480;
	}
	else if((strcmp(sub, "wifi_320_1024") == 0) || (strcmp(sub, "wifi_320_10240") == 0))
	{
		size = 320;
	}
	else if((strcmp(sub, "wifi_256_1024") == 0) || (strcmp(sub, "wifi_256_10240") == 0))
	{
		size = 256;
	}
	else if((strcmp(sub, "wifi_128_1024") == 0) || (strcmp(sub, "wifi_128_10240") == 0))
	{
		size = 128;
	}
	else if((strcmp(sub, "wifi_108_1024") == 0) || (strcmp(sub, "wifi_108_10240") == 0))
	{
		size = 108;
	}
	else if((strcmp(sub, "wifi_100_1024") == 0) || (strcmp(sub, "wifi_100_10240") == 0))
	{
		size = 100;
	}
	return size;
}
int validate_wifi_counter(char *sub)
{
	int counter = 0;
	if((strcmp(sub, "wifi_1447_1024") == 0) || (strcmp(sub, "wifi_1440_1024") == 0) || (strcmp(sub, "wifi_1200_1024") == 0) || (strcmp(sub, "wifi_1024_1024") == 0) || (strcmp(sub, "wifi_980_1024") == 0) || (strcmp(sub, "wifi_800_1024") == 0) || (strcmp(sub, "wifi_720_1024") == 0) || (strcmp(sub, "wifi_640_1024") == 0) || (strcmp(sub, "wifi_512_1024") == 0) || (strcmp(sub, "wifi_480_1024") == 0) || (strcmp(sub, "wifi_100_1024") == 0) || (strcmp(sub, "wifi_108_1024") == 0) || (strcmp(sub, "wifi_128_1024") == 0) || (strcmp(sub, "wifi_320_1024") == 0) || (strcmp(sub, "wifi_256_1024") == 0))
	{
		counter = 1024;
	}
	else if(strcmp(sub, "wifi_1447_1024*1024_stress") == 0)
	{
		counter = 1024 * 1024;
	}
	else if((strcmp(sub, "wifi_1200_10240") == 0) || (strcmp(sub, "wifi_1440_10240") == 0) || (strcmp(sub, "wifi_1024_10240") == 0) || (strcmp(sub, "wifi_980_10240") == 0) || (strcmp(sub, "wifi_800_10240") == 0) || (strcmp(sub, "wifi_720_10240") == 0) || (strcmp(sub, "wifi_640_10240") == 0) || (strcmp(sub, "wifi_512_10240") == 0) || (strcmp(sub, "wifi_480_10240") == 0) || (strcmp(sub, "wifi_320_10240") == 0) || (strcmp(sub, "wifi_256_10240") == 0) || (strcmp(sub, "wifi_128_10240") == 0) || (strcmp(sub, "wifi_108_10240") == 0) || (strcmp(sub, "wifi_100_10240") == 0))
	{
		counter = 10240;
	}
	return counter;
}
