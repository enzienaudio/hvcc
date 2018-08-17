# Heavy Compiler Collection (hvcc)

`hvcc` is a python-based dataflow audio programming language compiler that generates C/C++ code and a variety of specific framework wrappers.

## Background

The original need for `hvcc` arose from running against performance limitations while creating interactive music and sound products for the iPhone. [Pure Data](https://puredata.info) (libpd) was the only real choice for a design tool as it was embeddable and provided a high enough abstraction level that musicians or sound designers could be creative.

The goal was to leverage Pure Data as a design interface and statically interpret the resultant patches to generate a low-level, portable and optimised C/C++ program that would be structured to take advantage of modern hardware whilst still generating the same behaviour and audio output as Pure Data.

It has since then been expanded to provide further support for many different platforms and frameworks, especially targeting game audio production tools.

## Requirements

* python 2.7
    - `enum`
    - `jinja2`
    - `nose2`

## Usage

`hvcc` requires at least one argument that determines the top-level patch file to be loaded.

Generate a C/C++ program from `input.pd` and place the files in `~/myProject/`

`$ python2.7 hvcc.py ~/myProject/_main.pd`

This command will generate the following directories:

* `~/myProject/hv` heavylang representation of the input pd patch(es)
* `~/myProject/ir` heavyir representation of the heavylang patch
* `~/myProject/c` final generated C/C++ source files (this is what you would use in your project)

### `-o` Select output directory

As seen in the above command, typical output of `hvcc` is split into several directories that contain the intermediate files used by the compiler itself, the final generated source files, and any additional framework specific files and projects.

The `-o` or `--out_dir` parameter will specify where the output files are placed after a successful compile.

For example:
`$ python2.7 hvcc.py ~/myProject/_main.pd -o ~/Desktop/somewhere/else/`

Will place all the generated files in `~/Desktop/somewhere/else/`.

### `-n` Specify Patch Name

The `-n` or `--name` parameter can be used to easily namespace the generated code so that there are no conflicts when integrating multiple patches into the same project.

`$ python2.7 hvcc.py ~/myProject/_main.pd -o ~/Desktop/somewhere/else/ -n mySynth`

### `--help`
`hvcc` has a number of commandline paramters. You can see them all here:
```
$ python2.7 hvcc.py --help

usage: hvcc.py [-h] [-o OUT_DIR] [-p SEARCH_PATHS [SEARCH_PATHS ...]]
               [-n NAME] [-g GEN [GEN ...]] [--results_path RESULTS_PATH] [-v]
               [--copyright COPYRIGHT]
               in_path

This is the Enzien Audio Heavy compiler. It compiles supported dataflow
languages into C, and other supported frameworks.

positional arguments:
  in_path               The input dataflow file.

optional arguments:
  -h, --help            show this help message and exit
  -o OUT_DIR, --out_dir OUT_DIR
                        Build output path.
  -p SEARCH_PATHS [SEARCH_PATHS ...], --search_paths SEARCH_PATHS [SEARCH_PATHS ...]
                        Add a list of directories to search through for
                        abstractions.
  -n NAME, --name NAME  Provides a name for the generated Heavy context.
  -g GEN [GEN ...], --gen GEN [GEN ...]
                        List of generator outputs: unity, wwise, js, vst2, fabric
  --results_path RESULTS_PATH
                        Write results dictionary to the given path as a JSON-
                        formatted string. Target directory will be created if
                        it does not exist.
  -v, --verbose         Show debugging information.
  --copyright COPYRIGHT
                        A string indicating the owner of the copyright.
```

## Documentation

* [Introduction](/docs/01.introduction.md)
  - [What is heavy?](/docs/01.introduction.md#what-is-heavy)
  - [Supported patch formats](/docs/01.introduction.md#supported-patch-formats)
  - [Supported platforms](/docs/01.introduction.md#supported-platforms)
  - [Supported frameworks](/docs/01.introduction.md#supported-frameworks)
  - [Licensing](/docs/01.introduction.md#licensing)
* [Getting Started](/docs/02.getting_started.md)
* [Unity](/docs/05.unity.md)
* [Wwise](/docs/06.wwise.md)
* [Javascript](/docs/07.javascript.md)
* [VST](/docs/08.vst.md)
* [MIDI](/docs/09.midi.md)
* [C API](/docs/10.c.md)
* [C++ API](/docs/11.cpp.md)
* [Heavy Lang Info](/docs/12.heavy_lang.md)
* [Heavy IR Info](/docs/13.heavy_ir_lang.md)
