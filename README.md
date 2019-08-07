# hello-extension

The simplest possible C++ extension for Python3. No Boost.

The module's name according to `pip` is `helloworld`.
The module's name according to `import` is `libhelloworld`.

Beware that this module is *not* available on PyPI! If you run the
simple command `pip install helloworld`, you will get some completely
different thing from PyPI — something with a pseudonymous maintainer
and a dozen heavyweight dependencies, which hasn't been updated since 2010.
So don't run `pip install helloworld`.


## Installing and testing the module with `pip`

Run the following command to install the module from github.com/Quuxplusone.
This command does NOT interact with the code you have checked out in your
local repo; it fetches a clean copy from github.com/Quuxplusone and then
compiles it.

    pip install -r example-of-use/requirements.txt

>     Obtaining helloworld from git+git://github.com/Quuxplusone/hello-extension.git#egg=helloworld (from -r example-of-use/requirements.txt (line 1))
>       Updating /Users/ajo/env3/src/helloworld clone
>       Running command git fetch -q --tags
>       Running command git reset --hard -q 9aead276daca2e417016f7b2a6ba1c45271b96b3
>     Installing collected packages: helloworld
>       Running setup.py develop for helloworld
>     Successfully installed helloworld

Now that you have the module installed, you should see `helloworld`
show up in the output of `pip freeze`.

    pip freeze | grep helloworld

>      -e git://github.com/Quuxplusone/hello-extension.git@9aead276daca2e417016f7b2a6ba1c45271b96b3#egg=helloworld

And now you can successfully run Python scripts that `import libhelloworld`!

    python example-of-use/example.py 

>      hello world

To remove the module, you can use `pip uninstall` as usual.

    pip uninstall helloworld
