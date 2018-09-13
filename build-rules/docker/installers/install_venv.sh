apt-get update \
  && apt-get install -y python3-pip python3-dev python3-tk \
	&& pip3 install virtualenv lxml scipy numpy matplotlib \
        && mkdir /workspace && cd /workspace && virtualenv -p python3 venv \
            && source /workspace/venv/bin/activate && pip install matplotlib numpy lxml scipy tensorflow tflearn pprint gym