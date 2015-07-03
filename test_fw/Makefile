CURRENT_DIR := $(shell pwd)
BUILD_DIR := $(CURRENT_DIR)/bin
UTILS_DIR := $(CURRENT_DIR)/utils
TESTCASES_DIR := $(CURRENT_DIR)/testcases
BSP_DIR := $(TESTCASES_DIR)/bsp
CLIENT_DIR := $(CURRENT_DIR)/client_test
SERVER_DIR := $(CURRENT_DIR)/server_test
EDMA_DIR := $(BSP_DIR)/edma
EDMA_NODE_DIR := $(EDMA_DIR)/node
EDMA_STRESS_DIR := $(EDMA_DIR)/stress
I2C_DIR := $(BSP_DIR)/i2c
I2C_NODE_DIR := $(I2C_DIR)/node
UART_DIR := $(BSP_DIR)/uart
UART_NODE_DIR := $(UART_DIR)/node
PING_DIR := $(CLIENT_DIR)/ping_test
HOSTAPD_CONF := $(UTILS_DIR)/hostapd_conf
UDHCPD_CONF := $(UTILS_DIR)/udhcpd_conf
HOSTAPD_SH := $(UTILS_DIR)/hostapd_sh
INTERFACES_DIR := $(UTILS_DIR)/interface
TEST_CONFIG_DIR := $(TESTCASES_DIR)/test_config
WIFI_DIR :=  $(BSP_DIR)/wifi
BUCK_TEST_DIR := $(CURRENT_DIR)/gpTestBuckD
CROSS_COMPILE := arm-arago-linux-gnueabi
SDCARD_DIR := /media/ROOTFS/opt/ipnc

all: client ping server edma edma_stress edma_node i2c i2c_node uart uart_node wifi buck_test

all_sd_card: client ping server edma edma_stress edma_node i2c i2c_node uart uart_node wifi buck_test sd_card_cp

client:
	gcc -Wall $(CLIENT_DIR)/*.c -o client
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv client $(BUILD_DIR)
	cp $(INTERFACES_DIR)/interfaces1 $(BUILD_DIR)
	cp $(INTERFACES_DIR)/interfaces2 $(BUILD_DIR)
	cp $(INTERFACES_DIR)/interfaces3 $(BUILD_DIR)
	cp $(TEST_CONFIG_DIR)/* $(BUILD_DIR)

ping:
	gcc -Wall -o ping $(PING_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv ping $(BUILD_DIR)

server:
	$(CROSS_COMPILE)-gcc -Wall -o server $(SERVER_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv server $(BUILD_DIR)

edma_node:
	$(CROSS_COMPILE)-gcc -Wall -o edma_node_test $(EDMA_NODE_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv edma_node_test $(BUILD_DIR)

edma:
	$(CROSS_COMPILE)-gcc -Wall -o edma_tests $(EDMA_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv edma_tests $(BUILD_DIR)
	cp $(EDMA_DIR)/kSt_edma_parser.ko $(BUILD_DIR)
edma_stress:
	$(CROSS_COMPILE)-gcc -Wall -o edma_tests_stress $(EDMA_STRESS_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv edma_tests_stress $(BUILD_DIR)
	cp $(EDMA_DIR)/kSt_edma_parser.ko $(BUILD_DIR)

i2c:
	$(CROSS_COMPILE)-gcc -Wall -o i2c_tests $(I2C_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv i2c_tests $(BUILD_DIR)

i2c_node:
	$(CROSS_COMPILE)-gcc -Wall -o i2c_node_test $(I2C_NODE_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv i2c_node_test $(BUILD_DIR)

uart:
	$(CROSS_COMPILE)-gcc -Wall -o test_uart1 $(UART_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv test_uart1 $(BUILD_DIR)

uart_node:
	$(CROSS_COMPILE)-gcc -Wall -o test_uart1_node $(UART_NODE_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv test_uart1_node $(BUILD_DIR)

wifi:
	$(CROSS_COMPILE)-gcc -Wall -o wifi_node_test $(WIFI_DIR)/*.c
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	mv wifi_node_test $(BUILD_DIR)

sd_card_cp:
	cp $(BUILD_DIR)/edma_node_test $(SDCARD_DIR)
	cp $(BUILD_DIR)/i2c_node_test $(SDCARD_DIR)
	cp $(BUILD_DIR)/test_uart1_node $(SDCARD_DIR)
	cp $(BUILD_DIR)/wifi_node_test $(SDCARD_DIR)
	cp $(BUILD_DIR)/server $(SDCARD_DIR)
	cp $(BUILD_DIR)/edma_tests $(SDCARD_DIR)
	cp $(BUILD_DIR)/edma_tests_stress $(SDCARD_DIR)
	cp $(BUILD_DIR)/i2c_tests $(SDCARD_DIR)
	cp $(BUILD_DIR)/test_uart1 $(SDCARD_DIR)
	cp $(BUILD_DIR)/kSt_edma_parser.ko $(SDCARD_DIR)
	cp $(BUILD_DIR)/buck_test $(SDCARD_DIR)
	cp $(HOSTAPD_CONF)/*.conf $(SDCARD_DIR)
	cp $(HOSTAPD_SH)/*.sh $(SDCARD_DIR)
	cp $(UDHCPD_CONF)/*.conf $(SDCARD_DIR)
	cp $(TEST_CONFIG_DIR)/* $(SDCARD_DIR)
buck_test:
	$(CROSS_COMPILE)-gcc -o buck_test $(BUCK_TEST_DIR)/gpTestBuckD.c
	mv  buck_test $(BUILD_DIR)
clean:
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	rm -r $(BUILD_DIR)
	if [ -f Makefile~ ]; then  rm Makefile~; fi 
	if [ -f *.sh~ ]; then rm *.sh~; fi
	if [ -f $(CLIENT_DIR)/*.c~ ]; then rm $(CLIENT_DIR)/*.c~; fi
	if [ -f $(CLIENT_DIR)/*.h~ ]; then  rm $(CLIENT_DIR)/*.h~; fi
	if [ -f $(PING_DIR)/*.c~ ]; then  rm $(PING_DIR)/*.c~; fi
	if [ -f $(SERVER_DIR)/*.c~ ]; then  rm $(SERVER_DIR)/*.c~; fi
	if [ -f $(SERVER_DIR)/*.h~ ]; then  rm $(SERVER_DIR)/*.h~; fi
	if [ -f $(EDMA_DIR)/*.c~ ]; then  rm $(EDMA_DIR)/*.c~; fi
	if [ -f $(EDMA_DIR)/*.h~ ]; then  rm $(EDMA_DIR)/*.h~; fi
	if [ -f $(EDMA_STRESS_DIR)/*.c~ ]; then  rm $(EDMA_STRESS_DIR)/*.c~; fi
	if [ -f $(EDMA_STRESS_DIR)/*.c~ ]; then  rm $(EDMA_STRESS_DIR)/*.h~; fi
	if [ -f $(EDMA_NODE_DIR)/*.c~ ]; then  rm $(EDMA_NODE_DIR)/*.c~; fi
	if [ -f $(I2C_DIR)/*.c~ ]; then  rm $(I2C_DIR)/*.c~; fi
	if [ -f $(I2C_NODE_DIR)/*.c~ ]; then  rm $(I2C_NODE_DIR)/*.c~; fi
	if [ -f $(UART_DIR)/*.c~ ]; then  rm $(UART_DIR)/*.c~; fi
	if [ -f $(UART_NODE_DIR)/*.c~ ]; then  rm $(UART_NODE_DIR)/*.c~; fi
	if [ -f $(WIFI_DIR)/*.c~ ]; then  rm $(WIFI_DIR)/*.c~; fi
	if [ -f $(TEST_CONFIG_DIR)/*~ ]; then  rm $(TEST_CONFIG_DIR)/*~; fi
	if [ -f $(HOSTAPD_CONF)/*~ ]; then  rm $(HOSTAPD_CONF)/*~; fi
	if [ -f $(UDHCPD_CONF)/*~ ]; then  rm $(UDHCPD_CONF)/*~; fi
	if [ -f $(HOSTAPD_SH)/*~ ]; then  rm $(HOSTAPD_SH)/*~; fi
	if [ -f $(INTERFACES_DIR)/*~ ]; then  rm $(INTERFACES_DIR)/*~; fi
	if [ -f $(BUCK_TEST_DIR)/*~ ]; then  rm $(BUCK_TEST_DIR)/*~; fi
