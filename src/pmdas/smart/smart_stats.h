/*
 * S.M.A.R.T stats using smartcl and smartmontools
 *
 * Copyright (c) 2018 Red Hat.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef SMART_STATS_H
#define SMART_STATS_H

enum {
	HEALTH = 0,
	MODEL_FAMILY,
	DEVICE_MODEL,
	SERIAL_NUMBER,
	CAPACITY_BYTES,
	SECTOR_SIZE,
	ROTATION_RATE,
	FIRMWARE_VERSION,
	NUM_INFO_METRICS
};

enum {
	RAW_READ_ERROR_RATE = 1,
	THROUGHPUT_PERFORMANCE = 2,
	SPIN_UP_TIME = 3,
	START_STOP_COUNT = 4,
	REALLOCATED_SECTOR_COUNT = 5,
	SEEK_ERROR_COUNT = 7,
	SEEK_TIME_PERFORMANCE = 8,
	POWER_ON_HOURS = 9,
	SPIN_RETRY_COUNT = 10,
	CALIBRATION_RETRY_COUNT = 11,
	POWER_CYCLE_COUNT = 12,
	READ_SOFT_ERROR_RATE = 13,
	CURRENT_HELIUM_LEVEL = 22,
	ERASE_FAIL_COUNT_CHIP = 176,
	WEAR_LEVELING_COUNT = 177,
	USED_RESERVED_BLOCK_COUNT_TOTAL = 179,
	UNUSED_RESERVED_BLOCK_COUNT_TOTAL = 180,
	PROGRAM_FAIL_COUNT_TOTAL = 181,
	ERASE_FAIL_COUNT_TOTAL = 182,
	RUNTIME_BAD_BLOCK = 183,
	END_TO_END_ERROR = 184,
	REPORTED_UNCORRECT = 187,
	COMMAND_TIMEOUT = 188,
	HIGH_FLY_WRITES = 189,
	AIRFLOW_TEMP_CELSIUS = 190,
	G_SENSE_ERROR_RATE = 191,
	POWER_OFF_RETRACT_COUNT = 192,
	LOAD_CYCLE_COUNT = 193,
	TEMPERATURE_CELSIUS = 194,
	HARDWARE_ECC_RECOVERED = 195,
	REALLOCATED_EVENT_COUNT = 196,
	CURRENT_PENDING_SECTOR = 197,
	OFFLINE_UNCORRECTABLE = 198,
	UDMA_CRC_ERROR_COUNT = 199,
	MULTI_ZONE_ERROR_RATE = 200,
	SOFT_READ_ERROR_RATE = 201,
	DISK_SHIFT = 220,
	LOADED_HOURS = 222,
	LOAD_RETRY_COUNT = 223,
	LOAD_FRICTION = 224,
	LOAD_CYCLE = 225,
	LOAD_IN_TIME = 226,
	HEAD_FLYING_HOURS = 240,
	TOTAL_LBAS_WRITTEN = 241,
	TOTAL_LBAS_READ = 242,
	READ_ERROR_RETRY_RATE = 250,
	FREE_FALL_SENSOR = 254,
	NUM_SMART_STATS = 256
};

enum {
	SMART_ID = 0,
	SMART_VALUE,
	SMART_WORST,
	SMART_THRESH,
	SMART_RAW,
	NUM_METRICS
};

enum {
	CRITICAL_WARNING = 0,
	COMPOSITE_TEMPERATURE,
	AVAILABLE_SPARE,
	AVAILABLE_SPARE_THRESHOLD,
	PERCENTAGE_USED,
	DATA_UNITS_READ,
	DATA_UNITS_WRITTEN,
	HOST_READ_COMMANDS,
	HOST_WRITES_COMMANDS,
	CONTROLLER_BUSY_TIME,
	POWER_CYCLES,
	NVME_POWER_ON_HOURS,
	UNSAFE_SHUTDOWNS,
	MEDIA_AND_DATA_INTEGRITY_ERRORS,
	NUMBER_OF_ERROR_INFORMATION_LOG_ENTRIES,
	WARNING_COMPOSITE_TEMPERATRE_TIME,
	CRITICAL_COMPOSITE_TEMPERATURE_TIME,
	TEMPERATURE_SENSOR_ONE,
	TEMPERATURE_SENSOR_TWO,
	TEMPERATURE_SENSOR_THREE,
	TEMPERATURE_SENSOR_FOUR,
	TEMPERATURE_SENSOR_FIVE,
	TEMPERATURE_SENSOR_SIX,
	TEMPERATURE_SENSOR_SEVEN,
	TEMPERATURE_SENSOR_EIGHT,
	THERMAL_MANAGEMENT_TEMPERATURE_ONE_TRANSITION_COUNT,
	THERMAL_MANAGEMENT_TEMPERATURE_TWO_TRANSITION_COUNT,
	TOTAL_TIME_FOR_THERMAL_MANAGEMENT_TEMPERATURE_ONE,
	TOTAL_TIME_FOR_THERMAL_MANAGEMENT_TEMPERATURE_TWO,
	NUM_NVME_STATS
};

struct device_info {
	char			health[9];
	char			model_family[41];
	char			device_model[41];
	char			serial_number[21];
	uint64_t		capacity_bytes;
	char			sector_size[64];
	char			rotation_rate[18];
	char			firmware_version[9];
};

struct smart_data {
	uint8_t		id[NUM_SMART_STATS];
	uint8_t		type[NUM_SMART_STATS];
	uint8_t		value[NUM_SMART_STATS];
	uint8_t		worst[NUM_SMART_STATS];
	uint8_t 		thresh[NUM_SMART_STATS];
	uint32_t		raw[NUM_SMART_STATS];
};

struct nvme_smart_data{
	char			critical_warning[9];
	uint8_t		composite_temperature;
	uint8_t		available_spare;
	uint8_t		available_spare_threshold;
	uint8_t		percentage_used;
	uint64_t		data_units_read;
	uint64_t		data_units_written;
	uint64_t		host_read_commands;
	uint64_t		host_write_commands;
	uint32_t		controller_busy_time;
	uint32_t		power_cycles;
	uint32_t		power_on_hours;
	uint32_t		unsafe_shutdowns;
	uint32_t		media_and_data_integrity_errors;
	uint32_t		number_of_error_information_log_entries;
	uint32_t		warning_composite_temperature_time;
	uint32_t		critical_composite_temperature_time;
	uint8_t		temperature_sensor_one;
	uint8_t		temperature_sensor_two;
	uint8_t		temperature_sensor_three;
	uint8_t		temperature_sensor_four;
	uint8_t		temperature_sensor_five;
	uint8_t		temperature_sensor_six;
	uint8_t		temperature_sensor_seven;
	uint8_t		temperature_sensor_eight;
};

extern int smart_device_info_fetch(int, struct device_info *, pmAtomValue *);
extern int smart_refresh_device_info(const char *, struct device_info *, int);

extern int smart_data_fetch(int, int, struct smart_data *, pmAtomValue *);
extern int smart_refresh_data(const char *, struct smart_data *, int);

extern int nvme_smart_data_fetch(int, int, struct nvme_smart_data *, pmAtomValue *, int);
extern int nvme_smart_refresh_data(const char *, struct nvme_smart_data *, int);

extern void smart_stats_setup(void);

#endif /* SMART_STATS_H */
