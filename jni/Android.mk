# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libams
LOCAL_SRC_FILES := ./libs/libams.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcutils
LOCAL_SRC_FILES := ./libs/libcutils.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libadr_hld
LOCAL_SRC_FILES := ./libs/libadr_hld.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := dvbagent
LOCAL_SRC_FILES := com_dvb_DvbChannel.c  com_dvb_DvbSystem.c com_dvb_DvbSearch.c com_dvb_DvbPlayer.c  com_dvb_DvbEpg.c epgTest.c com_dvb_DvbSatellite.c\
					systemTest.c com_dvb_DvbSystemSetting.c \
					alidvb/alidvb_search.c alidvb/alidvb_system.c alidvb/db_callback.c alidvb/alidvb_player.c alidvb/alidvb_epg.c alidvb/alidvb_test.c alidvb/board_config_cstm.c \
					com_dvb_DvbUdrm.c com_property.c
LOCAL_LDLIBS := -llog
LOCAL_C_INCLUDES += $(LOCAL_PATH)/alidvb/hld_inc/inc/ $(LOCAL_PATH)/alidvb/hld_inc/kernel/linux-linaro-3.4-rc3/include $(LOCAL_PATH)/alidvb/hld_inc/alidrivers/include $(LOCAL_PATH)/alidvb/ams_inc/
LOCAL_SHARED_LIBRARIES := libcutils libams libadr_hld

include $(BUILD_SHARED_LIBRARY)


