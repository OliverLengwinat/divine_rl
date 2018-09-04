if [[ "$OSTYPE" == "linux-gnu" ]]; then
    sudo apt-get install python3 python3-dev python3-pip virtualenv openjdk-8-jdk curl npm -y
    echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
    curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
    sudo apt-get update -y && sudo apt-get install bazel -y
    sudo apt-get upgrade bazel
    sudo apt-get update && apt-get install -y python3-pip python3-dev python3-tk 
fi

virtualenv -p python3 venv
&& source activate ./venv/bin/activate
&& pip install install matplotlib numpy lxml scipy tensorflow tflearn pprint gym