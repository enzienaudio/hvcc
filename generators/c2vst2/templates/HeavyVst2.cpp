{{copyright}}

#include "{{class_name}}.hpp"
#include "HvUtils.h"

#define HV_VST2_NUM_PARAMETERS {{receivers|length}}

extern "C" {
  HV_EXPORT AEffect *VSTPluginMain(audioMasterCallback audioMaster) {
    // Get VST Version of the Host, return NULL if old version
    if (!audioMaster(0, audioMasterVersion, 0, 0, 0, 0)) return NULL;

    // Create the AudioEffect
    AudioEffect* effect = new {{class_name}}(audioMaster);
    if (effect == NULL) return NULL;

    // Return the VST AEffect structure
    return effect->getAeffect();
  }
}

{{class_name}}::{{class_name}}(audioMasterCallback amCallback) :
    AudioEffectX(amCallback, 0, HV_VST2_NUM_PARAMETERS) {
  setUniqueID({{class_name|uniqueid}});
  setNumInputs({{num_input_channels}});
  setNumOutputs({{num_output_channels}});
  isSynth({{"true" if num_input_channels == 0 and num_output_channels > 0 else "false"}});
  programsAreChunks(true);
  canProcessReplacing(true);
  canDoubleReplacing(false);
  // initialise parameters with defaults
  {%- for k, v in receivers %}
  _parameters[{{loop.index-1}}] = {{(v.attributes.default-v.attributes.min)/(v.attributes.max-v.attributes.min)}}f; // {{v.display}}
  {%- endfor %}
  _context = nullptr;
  this->sampleRate = 0.0f; // initialise sample rate
  setSampleRate(44100.0f); // set sample rate to some default
}

{{class_name}}::~{{class_name}}() {
  delete _context;
}

void {{class_name}}::setSampleRate(float sampleRate) {
  if (this->sampleRate != sampleRate) {
    this->sampleRate = sampleRate;
    delete _context;

    _context = new Heavy_{{name}}(sampleRate, {{pool_sizes_kb.internal}}, {{pool_sizes_kb.inputQueue}}, {{pool_sizes_kb.outputQueue}});

    {%- if receivers|length > 0 %}
    // ensure that the new context has the current parameters
    for (int i = 0; i < HV_VST2_NUM_PARAMETERS; ++i) {
      setParameter(i, _parameters[i]);
    }
    {%- endif %}
  }
}

void {{class_name}}::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
  _context->process(inputs, outputs, sampleFrames);
}

VstInt32 {{class_name}}::processEvents(VstEvents* events) {
  for (int i = 0; i < events->numEvents; ++i) {
    VstEvent *vste = events->events[i];
    switch (vste->type) {
      case kVstMidiType: {
        VstMidiEvent *vstme = (VstMidiEvent *) vste;

        const unsigned char command = vstme->midiData[0] & 0xF0;
        const unsigned char channel = vstme->midiData[0] & 0x0F;
        const unsigned char data0   = vstme->midiData[1] & 0x7F;
        const unsigned char data1   = vstme->midiData[2] & 0x7F;

        switch (command) {
          case 0x80:   // note off
          case 0x90: { // note on
            _context->sendMessageToReceiverV(0x67E37CA3, // __hv_notein
                1000.0*vste->deltaFrames/sampleRate, "fff",
                (float) data0, // pitch
                (float) data1, // velocity
                (float) channel);
            break;
          }
          case 0xB0: { // control change
            _context->sendMessageToReceiverV(0x41BE0F9C, // __hv_ctlin
                1000.0*vste->deltaFrames/sampleRate, "fff",
                (float) data1, // value
                (float) data0, // controller number
                (float) channel);
            break;
          }
          case 0xC0: { // program change
            _context->sendMessageToReceiverV(0x2E1EA03D, // __hv_pgmin,
                1000.0*vste->deltaFrames/sampleRate, "ff",
                (float) data0,
                (float) channel);
            break;
          }
          case 0xD0: { // aftertouch
            _context->sendMessageToReceiverV(0x553925BD, // __hv_touchin
                1000.0*vste->deltaFrames/sampleRate, "ff",
                (float) data0,
                (float) channel);
            break;
          }
          case 0xE0: { // pitch bend
            hv_uint32_t value = (((hv_uint32_t) data1) << 7) | ((hv_uint32_t) data0);
            _context->sendMessageToReceiverV(0x3083F0F7, // __hv_bendin
                1000.0*vste->deltaFrames/sampleRate, "ff",
                (float) value,
                (float) channel);
            break;
          }
          default: break;
        }
        break;
      }
      case kVstSysExType: {
        // not handling this case at the moment, VstMidiSysexEvent *vstmse;
        break;
      }
      default: break;
    }
  }
  return 1;
}

static float scaleParameterForIndex(VstInt32 index, float value) {
  switch (index) {
    {%- for k, v in receivers %}
    case {{loop.index-1}}: return ({{v.attributes.max-v.attributes.min}}f*value) + {{v.attributes.min}}f; // {{v.display}}
    {%- endfor %}
    default: return 0.0f;
  }
}

void {{class_name}}::setParameter(VstInt32 index, float value) {
  {%- if receivers|length > 0 %}
  switch (index) {
    {%- for k, v  in receivers %}
    case {{loop.index-1}}: {
      _context->sendFloatToReceiver(
          Heavy_{{name}}::Parameter::In::{{k|upper}},
          scaleParameterForIndex(index, value));
      break;
    }
    {%- endfor %}
    default: return;
  }
  _parameters[index] = value;
  {%- else %}
  // nothing to do
  {%- endif %}
}

float {{class_name}}::getParameter(VstInt32 index) {
  {%- if receivers|length > 0 %}
  return _parameters[index];
  {%- else %}
  return 0.0f;
  {%- endif %}
}

void {{class_name}}::getParameterName(VstInt32 index, char* text) {
  switch (index) {
    {%- for k,v in receivers %}
    case {{loop.index-1}}: strncpy(text, "{{v.display}}", kVstMaxParamStrLen); break;
    {%- endfor %}
    default: text[0] = '\0'; break;
  }
  text[kVstMaxParamStrLen-1] = '\0';
}

void {{class_name}}::getParameterDisplay(VstInt32 index, char* text) {
  {%- if receivers|length > 0 %}
  snprintf(text, kVstMaxParamStrLen, "%0.3f", scaleParameterForIndex(index, _parameters[index]));
  text[kVstMaxParamStrLen-1] = '\0';
  {%- else %}
  strcpy(text, "0");
  {%- endif %}
}

bool {{class_name}}::string2parameter(VstInt32 index, char* text) {
  setParameter(index, (float) atof(text));
  return true;
}

bool {{class_name}}::getEffectName(char* name) {
  strncpy(name, "{{name}}", kVstMaxEffectNameLen);
  name[kVstMaxEffectNameLen-1] = '\0';
  return true;
}

bool {{class_name}}::getVendorString(char* text) {
  strncpy(text, "Enzien Audio, Ltd.", kVstMaxVendorStrLen);
  text[kVstMaxVendorStrLen-1] = '\0';
  return true;
}

VstInt32 {{class_name}}::canDo(char *text) {
  if (!strcmp(text, "receiveVstEvents")) return 1; // PlugCanDos::canDoReceiveVstEvents
  if (!strcmp(text, "receiveVstMidiEvent")) return 1; // PlugCanDos::canDoReceiveVstMidiEvent
  return 0;
}

VstInt32 {{class_name}}::getChunk(void **data, bool isPreset) {
  {%- if receivers|length > 0 %}
  const VstInt32 numBytes = HV_VST2_NUM_PARAMETERS * sizeof(float);
  float *chunk = (float *) malloc(numBytes);
  memcpy(chunk, _parameters, numBytes);
  *data = chunk;
  return numBytes;
  {%- else %}
  *data = nullptr;
  return 0;
  {%- endif %}
}

VstInt32 {{class_name}}::setChunk(void *data, VstInt32 byteSize, bool isPreset) {
  {%- if receivers|length > 0 %}
  float *const chunk = (float *) data;
  for (int i = 0; i < HV_VST2_NUM_PARAMETERS; ++i) {
    setParameter(i, chunk[i]);
  }
  return byteSize;
  {%- else %}
  return 0;
  {%- endif %}
}
{# newline #}
