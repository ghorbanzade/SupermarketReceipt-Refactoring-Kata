# Using Weasel

## What is Weasel

The example in this directory is a variant of the "original" example, using
the Weasel client library instead of the Approval Tests framework.

Weasel is a distributed regression testing solution. It provides open-source
client libraries (currently only in C++) that enable capturing test results
for a given version of the workflow under test. The captured results can then
be submitted to a remote Weasel Platform where they are stored, interpreted,
visualized and automatically compared to a *baseline* version of the workflow
under test. If differences are found, Weasel notifies code owners and helps
them collaborate with each other to understand the differences and take
appropriate action such as creating a bug report or promoting the baseline
version.

You can learn more about Weasel at [getweasel.com](https://getweasel.com).

## Build Instructions

The easiest way to use Weasel as a third-party dependency in your project is
to use [CMake] version 3.11 or higher. If you do not have a recent version
of CMake installed already, please consult with their documentation for
instructions to install it on your platform.

Assuming that your project is already using CMake, you can pull Weasel as a
dependency, using CMake's [FetchContent] module as shown below.

```cmake
FetchContent_Declare(
    weasel
    GIT_REPOSITORY https://github.com/getweasel/weasel-cpp.git
    GIT_TAG        origin/main
)
FetchContent_MakeAvailable(weasel)
```

The above CMake code pulls the latest stable code of the Client Library and
generates a `weasel_client` CMake target to which you can link your own project.

Weasel Client Library for C++ requires OpenSSL to communicate with the Weasel
Platform through HTTPS. In most platforms, this library is automatically
discovered and used by the build recipe. But if OpenSSL is not installed in
the default location, we may need to provide its root directory as a hint to
the library's build recipe. Below is a typical example of doing so on macOS
in case OpenSSL is installed through `homebrew`.

```cmake
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
```

For convenience, a `build.sh` script is provided at the top-level cpp directory.
To get started, simply run this script from any directory.

```bash
./build.sh
```

## Running the Example

If the build was successful, you will find the generated build artifacts in
the `build` directory. The executable for this example will be located at:
`./build/test/basic`.

```bash
./build/test/basic/Supermarket.basic --help
```

Weasel client library is primarily designed to be used in a stand-alone
test application that invokes the workflow under test with different inputs
as separate testcases. However, in this example, to highlight the similaries
and differences between Weasel and other regression test tools, we are using
the Weasel-Catch2 integration layer. Note that, as of Weasel v1.2.1, the
Weasel-Catch2 integration layer is experimental and unstable.

This abstract layer allows us to configure the Weasel client library via
command-line arguments when invoking our Catch2-based unit-test executable
as shown in the command below.

```bash
./build/test/basic/Supermarket.basic --api-key "<YOUR_API_KEY>" --api-url "<YOUR_API_URL>" --revision 1.42.0
```

Where the values `YOUR_API_KEY` and `YOUR_API_URL` are provided by the
Weasel Platform after creating a user account and setting up a Team and Suite
for our workflow under test.

The value for `--api-key` is user-specific and should be considered as
sensitive information. As such, we advise passing it as an environment
variable as shown in the example below.

```bash
WEASEL_API_KEY="03dda763-62ea-436f-8395-f45296e56e4b" ./build/test/basic/Supermarket.basic --api-url "https://getweasel.com/api/@/supermarket/basic" --revision 1.42.0
```
