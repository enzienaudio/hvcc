{{copyright}}

#ifndef _HEAVY_VST2_{{name|upper}}_
#define _HEAVY_VST2_{{name|upper}}_

#include "vst2/audioeffectx.h"
#include "Heavy_{{name}}.hpp"

class {{class_name}} : public AudioEffectX {
 public:
  {{class_name}}(audioMasterCallback amCallback);
  ~{{class_name}}();

  void setSampleRate(float sampleRate) override;

  void setParameter(VstInt32 index, float value) override;
  float getParameter(VstInt32 index) override;

  void getParameterDisplay(VstInt32 index, char* text) override;
  void getParameterName(VstInt32 index, char* text) override;
  bool string2parameter(VstInt32 index, char* text) override;

  VstInt32 canDo(char *text) override;

  void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override;

  VstInt32 processEvents(VstEvents* events) override;

  bool getEffectName(char* name) override;
  bool getVendorString(char* text) override;

  VstInt32 getChunk(void** data, bool isPreset) override;
  VstInt32 setChunk(void* data, VstInt32 byteSize, bool isPreset) override;

 private:
  {%- if receivers|length > 0 %}
  // parameters
  float _parameters[{{receivers|length}}]; // in range of [0,1]
  {%- endif %}

  // heavy context
  HeavyContextInterface *_context;
};

#endif // _HEAVY_VST2_{{name|upper}}_
{# newline #}
