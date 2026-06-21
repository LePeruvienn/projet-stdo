#ifndef UTILS_PTR_H
#define UTILS_PTR_H

#define CHECK_IS_NULL(ptr, error_msg) \
	if (ptr == NULL) \
	{ \
		LOG_ERROR(error_msg); \
	}

#define FREE_PTR_NOT_NULL(ptr, free_func) \
	if (ptr != NULL) \
	{ \
		free_func(ptr); \
	}

#endif // UTILS_PTR_H
