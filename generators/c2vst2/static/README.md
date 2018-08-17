# Heavy VST2 Wrapper

Unfortunately due to legal restrictions, Enzien is unable to distribute the VST2 header files by Steinberg. In order to compile the VST on your own, download the latest VST3 Audio Plug-Ins SDK from the [Steinberg Developer site](http://www.steinberg.net/en/company/developers.html).
* Make a local directory in `source` called `vst2`.
* Copy all of the files in the VST SDK `public.sdk/source/vst2.x` directory, *except* for `vstplugmain.cpp`, into the local `source/vst2` directory.
* Copy the VST SDK `pluginterfaces/vst2.x` directory to the `source/vst2` directory.

The resulting directory structure should look like this:
* `/YOUR_HEAVY_VST_DIRECTORY`
  * `README.md`
  * `/xcode`
    * `Xcode project`
    * `Info.plist`
  * `/vs2015`
    * `Visual Studio solution`
    * `Visual Studio project`
  * `/source`
    * Heavy source files (`*.h`, `*.c`)
    * `HeavyVst2_PATCHNAME.h`
    * `HeavyVst2_PATCHNAME.cpp`
    * `/vst2`
      * `aeffeditor.h`
      * `audioeffect.cpp`
      * `audioeffect.h`
      * `audioeffectx.cpp`
      * `audioeffectx.h`
      * `/pluginterfaces`
        * `/vst2.x`
          * `aeffect.h`
          * `aeffectx.h`
          * `vstfxstore.h`

Now open the included Xcode or Visual Studio projects and you're ready to go!
