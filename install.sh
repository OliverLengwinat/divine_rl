if [[ "$OSTYPE" == "linux-gnu" ]]; then
    apt-get install python3 python3-dev python3-pip virtualenv openjdk-8-jdk curl npm -y
    echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
    curl https://bazel.build/bazel-release.pub.gpg | apt-key add -
    apt-get update -y && apt-get install bazel -y
    apt-get upgrade bazel
    apt-get update && apt-get install -y python3-pip python3-dev python3-tk 
fi

virtualenv -p python3 venv && source ./venv/bin/activate && pip install matplotlib numpy lxml scipy tensorflow tflearn pprint gym tensorforce stable-baselines