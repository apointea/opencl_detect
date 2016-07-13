#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
	# include <OpenCL/opencl.h>
#else
	# include <CL/cl.h>
#endif

#define RED		"\033[31m[-]"
#define CLEAR	"\033[0m"

int		main(void)
{
	cl_uint			i, j;
	char			*value = NULL;
	size_t			valueSize;
	cl_platform_id	*platforms = NULL;
	cl_uint			platformCount, deviceCount, maxComputeUnits, maxClockFrequency;
	cl_device_id	*devices = NULL;
	cl_ulong		size;

	if (clGetPlatformIDs(0, NULL, &platformCount) != CL_SUCCESS)
		return dprintf(2, "%sCan't get platform count.%s\n", RED, CLEAR);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platformCount);
	if (!platforms)
		return dprintf(2, "%sCan't allocate memory for platforms.%s\n", RED, CLEAR);
	if (clGetPlatformIDs(platformCount, platforms, NULL) != CL_SUCCESS)
		return dprintf(2, "%sCan't get platforms.%s\n", RED, CLEAR);
	for (i = 0; i < platformCount; i++)
	{
		if (clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount) != CL_SUCCESS)
			return dprintf(2, "%sCan't get platforms.%s\n", RED, CLEAR);
		devices = (cl_device_id*)malloc(sizeof(cl_device_id) * deviceCount);
		if (!devices)
			return dprintf(2, "%sCan't allocate memory for devices.%s\n", RED, CLEAR);
		if (clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL) != CL_SUCCESS)
			return dprintf(2, "%sCan't get devices informations.%s\n", RED, CLEAR);
		for (j = 0; j < deviceCount; j++)
		{
			if (clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize) != CL_SUCCESS)
				return dprintf(2, "%sCan't get device name size.%s\n", RED, CLEAR);
			value = (char *)malloc(valueSize);
			if (!value)
				return dprintf(2, "%sCan't allocate memory for device name.%s\n", RED, CLEAR);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get device name.%s\n", RED, CLEAR);
			printf("%d. Device: %s\n", j + 1, value);
			free(value);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize)  != CL_SUCCESS)
				return dprintf(2, "%sCan't get device version.%s\n", RED, CLEAR);
			value = (char *)malloc(valueSize);
			if (!value)
				return dprintf(2, "%sCan't allocate memory for device version.%s\n", RED, CLEAR);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get hardware version.%s\n", RED, CLEAR);
			printf(" %d.%d Hardware version: %s\n", j + 1, 1, value);
			free(value);
			if (clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize) != CL_SUCCESS)
				return dprintf(2, "%sCan't get driver version.%s\n", RED, CLEAR);
			value = (char *)malloc(valueSize);
			if (!value)
				return dprintf(2, "%sCan't allocate memory for driver version.%s\n", RED, CLEAR);
			if (clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get software version.%s\n", RED, CLEAR);
			printf(" %d.%d Software version: %s\n", j + 1, 2, value);
			free(value);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize) != CL_SUCCESS)
				return dprintf(2, "%sCan't get device OpenCL C version.%s\n", RED, CLEAR);
			value = (char *)malloc(valueSize);
			if (!value)
				return dprintf(2, "%sCan't allocate memory for device's OpenCL version.%s\n", RED, CLEAR);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get OpenCL C version.%s\n", RED, CLEAR);
			printf(" %d.%d OpenCL C version: %s\n", j + 1, 3, value);
			free(value);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits), &maxComputeUnits, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get max compute units.%s\n", RED, CLEAR);
			printf(" %d.%d Parallel compute units: %d\n", j + 1, 4, maxComputeUnits);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(maxClockFrequency), &maxClockFrequency, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get max clock frequency.%s\n", RED, CLEAR);
			printf(" %d.%d Max clock frequency: %d\n", j + 1, 4, maxClockFrequency);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(size), &size, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get global mem cache size.%s\n", RED, CLEAR);
			printf(" %d.%d mem cache size: %llu\n", j + 1, 5, (long long unsigned int)size);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(size), &size, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get global mem size.%s\n", RED, CLEAR);
			printf(" %d.%d global mem size: %llu\n", j + 1, 6, (long long unsigned int)size);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(size), &size, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get local mem size.%s\n", RED, CLEAR);
			printf(" %d.%d local mem size: %llu\n", j + 1, 7, (long long unsigned int)size);
			if (clGetDeviceInfo(devices[j], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size), &size, NULL) != CL_SUCCESS)
				return dprintf(2, "%sCan't get max mem alloc size.%s\n", RED, CLEAR);
			printf(" %d.%d max mem alloc size: %llu\n", j + 1, 8, (long long unsigned int)size);
		}
		free(devices);
	}
	free(platforms);
	return 0;

}
