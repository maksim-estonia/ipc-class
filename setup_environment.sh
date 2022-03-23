# enable command to be printed to terminal
set -x

# ask for sudo and elevate privilege
[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

# try to find Bazel
BAZEL_NEED_TO_BE_INSTALLED=true
if ! [ -x "$(command -v bazel)" ]; then
    BAZEL_NEED_TO_BE_INSTALLED=true
else
    BAZEL_NEED_TO_BE_INSTALLED=false

fi

# try to find g++
if ! [ -x "$(command -v g++)" ]; then
    GPLUSPLUS_NEED_TO_BE_INSTALLED=true
else
    GPLUSPLUS_NEED_TO_BE_INSTALLED=false
fi

# try to find git
GIT_NEED_TO_BE_INSTALLED=true
if ! [ -x "$(command -v git)" ]; then
     GIT_NEED_TO_BE_INSTALLED=true
else
     GIT_NEED_TO_BE_INSTALLED=false
fi

# install missing programs
if  $BAZEL_NEED_TO_BE_INSTALLED || $GPLUSPLUS_NEED_TO_BE_INSTALLED || $GIT_NEED_TO_BE_INSTALLED
then
    sudo apt update
    if $GPLUSPLUS_NEED_TO_BE_INSTALLED
    then
        apt install g++
    fi
    if $GIT_NEED_TO_BE_INSTALLED
    then
        apt install git
    fi
    if $BAZEL_NEED_TO_BE_INSTALLED
    then
        sudo apt install apt-transport-https curl gnupg
        curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
        sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
        echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
        sudo apt update && sudo apt install bazel
    fi
fi

chmod +x ./build_and_run_tests.sh 

set +x