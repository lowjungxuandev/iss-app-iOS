
#if !defined(__CONSUMER_C_H__)
#define __CONSUMER_C_H__

#include <stdint.h>

#if defined(WINDOWS)
    #if defined(EXPORTDLL)
        #define DLLSPEC __declspec(dllexport)
    #else 
        #define DLLSPEC __declspec(dllimport)
    #endif
    #if defined(NOEXPORTDLL)
        #undef DLLSPEC
        #define DLLSPEC
    #endif
#else 
    #if defined(NOEXPORTDLL)
        #undef DLLSPEC 
        #define DLLSPEC
        #warning NOEXPORTDLL!
    #else
        #define DLLSPEC  __attribute__((visibility("default"))) __attribute__((used))
    #endif
#endif


#if defined(__cplusplus)
extern "C" {
#endif

// ZDeviceEvent

typedef void (*zdevice_event_returnfunc_t)(void * context, const char * value);
typedef void (*zdevice_event_callback_t)(void * context, const char * event_name, const char * event_details, const char * response);
typedef void (*zdevice_event_listener_t)(void * context, const char * event_name, const char * event_details, void * ctx_returner, zdevice_event_returnfunc_t returner);

typedef uint64_t zdevice_event_registration_t;


DLLSPEC void zdevice_event_submit(const char* event_name, const char* event_details);

DLLSPEC void zdevice_event_submit_on_new_thread(const char* event_name, const char* event_details);

DLLSPEC void zdevice_event_submit_on_thread_pool(const char* event_name, const char* event_details);

DLLSPEC void zdevice_event_submit_for_response(void * context, const char * event_name, const char * event_details, zdevice_event_callback_t callback);


DLLSPEC void zdevice_event_submit_sticky(const int maxPerKey, const char* event_name, const char* event_details);

DLLSPEC zdevice_event_registration_t zdevice_event_listen(void * context, const char * event_name, zdevice_event_listener_t listener);

DLLSPEC void zdevice_event_unlisten(zdevice_event_registration_t registation);

#if defined(__cplusplus)
}
#endif

#endif

