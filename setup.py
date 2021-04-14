import sys

from setuptools import setup

if sys.version_info < (3, 0):
    sys.exit('Sorry, Python <3 is not supported')


setup(name='hvcc',
      version='0.0.1',
      license='GPLv3',
      author='Enzien Audio, Wasted Audio',
      url='https://github.com/Wasted-Audio/hvcc',
      download_url='',
      packages=['hvcc'],
      install_requires=[
          'Jinja2==2.11.3'
      ],
      scripts=['bin/hvcc', 'bin/hvutil'],
      classifiers=[
          'Development Status :: 3 - Alpha',
          'Intended Audience :: Developers',
          'Topic :: Software Development :: Compilers',
          'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
          'Programming Language :: Python :: 3.7',
          'Programming Language :: Python :: 3.8',
          'Programming Language :: Python :: 3.9'
      ])
