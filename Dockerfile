FROM  debian:latest

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y gcc git make nasm vim gdb curl
RUN curl 'https://raw.githubusercontent.com/JeremShy/RainFall/master/config' | tail -n +2 > /root/.gdbinit
RUN apt-get install -y bsdmainutils
RUN apt-get install -y man
RUN apt-get install -y zsh
RUN apt-get install -y clang
RUN apt-get install -y psmisc
RUN apt-get install -y procps
RUN apt-get install -y netcat
RUN apt-get install -y net-tools
RUN apt-get install -y libcurl4-openssl-dev
RUN sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)" || true
RUN git config --global user.email "magouin@student.42.fr"
RUN echo "alias mr=\"make re\"\nalias mc=\"make clean\"\nalias m=\"make\"\nalias mf=\"make fclean\"" >> /root/.zshrc

CMD cd /bind/Durex ;  /bin/zsh
