#!/usr/bin/env python

from distutils.core import setup, Extension

setup(
    name='helloworld',
    version='0.0.2',
    install_requires=[
        # pip requirements go here; at the moment there are none
    ],
    package_data={'': ['LICENSE']},

    # https://docs.python.org/3/extending/building.html#building-c-and-c-extensions-with-distutils
    ext_modules=[
        Extension(
            'libhelloworld',
            sources=[
                'core-src/hello.cc',
                'glue-src/glue.cc',
            ],
            extra_compile_args=[
                '-std=c++11',
            ],
        ),
    ],
    include_dirs=[
        '.',
    ],

    # metadata for upload to PyPI
    author="Arthur O'Dwyer",
    author_email='arthur.j.odwyer@gmail.com',
    description="A C++ extension that returns 'hello world'.",
    license='MIT license',
    long_description=open('README.md').read(),
    keywords='hello hello-world',
    url='https://github.com/Quuxplusone/hello-extension',
)
