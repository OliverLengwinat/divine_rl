FROM openjdk:8

ENV PATH /opt/conda/bin:$PATH
ENV DISPLAY :0

COPY installers /tmp/installers
RUN bash /tmp/installers/install_bazel.sh
RUN bash /tmp/installers/install_venv.sh
RUN apt-get update

# bash
CMD [ "/bin/bash" ]
WORKDIR /divine-rl