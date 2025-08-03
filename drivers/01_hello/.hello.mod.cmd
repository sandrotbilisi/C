savedcmd_/home/alex/drivers/01_hello/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/alex/drivers/01_hello/"$$0) }' > /home/alex/drivers/01_hello/hello.mod
