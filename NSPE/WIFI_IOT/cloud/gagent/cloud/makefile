CC := gcc
CFLAGS := -fPIC
AR := ar 
SRC_DIR := ./src
CLOUD_INC := ./inc
LIB_TARGET := libCloud.a 
INSTALL_LIB_PATH := ../../arch/linux/dll
INC_DIR := ../include

LOCAL_INC=../local/inc
LAN_INC=../lan/inc
HAL=../../arch/linux/hal_serial
NET=../../arch/linux/net
ADAPTER=../../arch/linux/adapter
OBJ=../../arch/linux/obj
DLL=../../arch/linux/dll

include ../../arch/linux/vendor.mak
ifdef MY_DEFINE
  CFLAGS += -D$(MY_DEFINE)
endif

INC_PATH += $(INC_DIR) ../../iof ../../arch/linux  $(HAL)/ $(LAN_INC)  $(CLOUD_INC) $(LOCAL_INC) $(NET) $(ADAPTER)
ifdef MY_COMPILER  
	CFLAGS += $(MY_COMPILER)
endif

CFLAGS += $(foreach dir,$(INC_PATH),-I$(dir))

OBJS :=	$(SRC_DIR)/obj/cloud \
	$(SRC_DIR)/obj/http \
	$(SRC_DIR)/obj/mqttbase \
	$(SRC_DIR)/obj/mqttlib \
	$(SRC_DIR)/obj/mqttxpg	\
	$(SRC_DIR)/obj/gagent_md5
OBJS := $(foreach obj,$(OBJS),$(obj).o)

$(SRC_DIR)/obj/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_TARGET): $(OBJS)
	$(AR) crus $(LIB_TARGET) $(OBJS)
	install -m 0755 $(LIB_TARGET) $(INSTALL_LIB_PATH)
	rm -rf $@
	@echo "----------build libCloud.a ok.----------"

.PHONY:clean  
clean:
	rm -rf $(SRC_DIR)/obj/*
	rm -rf $(SRC_DIR)/obj
	rm -rf $(LIB_TARGET)
	rm -rf $(INSTALL_LIB_PATH)/libCloud.a
	@echo "clean all"
  
.PHONY:folders  
folders:
	mkdir -p ./src/obj
  
print: $(SRC_DIR)/*.c
	lpr -p $?
	touch print

help:
	@echo "\r\n"
	@echo "------------------------ Gizwits GAgent -----------------------"
	@echo "| 1.type "make help" for help infonation." 
	@echo "| 2.run \"make clean;make\" to build lib." 
	@echo "| 3.the directory dll store the libs."
	@echo "| 4.use \"root\" or add \"sudo\" to run target !!!!!!!!"
	@echo "| * for more detail refer to the readme."
	@echo "---------------------------------------------------------------"
	@echo "|                      	By FrankLiu from Gizwits GAgent Team"
	@echo "---------------------------------------------------------------"
	@echo "\r\n"

