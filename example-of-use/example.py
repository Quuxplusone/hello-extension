#!/usr/bin/env python

# Start by running
#     pip install -r requirements.txt

try:
    import libhelloworld
except ImportError:
    print("""
        libhelloworld wasn't found!
        Did you forget to run
            pip install -r requirements.txt
        in this directory?
    """)
    raise

print(libhelloworld.get_hello())
