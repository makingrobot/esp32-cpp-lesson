/*
*/

#ifndef _AUDIO_STATUS_H
#define _AUDIO_STATUS_H

#include <Arduino.h>

class AudioStatus
{
public:
    AudioStatus() { ClearCallbacks(); };
    virtual ~AudioStatus() {};

    void ClearCallbacks() { 
      metadata_fn_ = NULL; 
      status_fn_ = NULL; 
    };

    typedef void (*MetadataCallbackFn)(void *cbData, const char *type, bool isUnicode, const char *str);
    bool RegisterMetadataCallback(MetadataCallbackFn f, void *cbData) { 
      metadata_fn_ = f; 
      metadata_data_ = cbData; 
      return true; 
    }

    // Returns a unique warning/error code, varying by the object.  The string may be a PSTR, use _P functions!
    typedef void (*StatusCallbackFn)(void *cbData, int code, const char *string);
    bool RegisterStatusCallback(StatusCallbackFn f, void *cbData) { 
      status_fn_ = f; 
      status_data_ = cbData; 
      return true; 
    }

    // Safely call the md function, if defined
    inline void MetadataBack(const char *type, bool isUnicode, const char *string) { 
      if (metadata_fn_) metadata_fn_(metadata_data_, type, isUnicode, string); 
    }

    // Safely call the st function, if defined
    inline void StatusCallback(int code, const char *string) { 
      if (status_fn_) status_fn_(status_data_, code, string); 
    }

private:
    MetadataCallbackFn metadata_fn_;
    void *metadata_data_;
    StatusCallbackFn status_fn_;
    void *status_data_;
};

#endif

