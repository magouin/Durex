docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -t -i --name durex_test -v "/Users/$(whoami)/Docker_binded":/bind -p 4242:4242 --rm durex
