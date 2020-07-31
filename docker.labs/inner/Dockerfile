
FROM hello-world:latest

WORKDIR /

COPY ./inner/inner.sh .
#RUN chmod +x ./inner/inner.sh

COPY ./hello.sh .
#RUN chmod +x ./outer.sh

ENTRYPOINT [ "sh", /inner/inner.sh" ]
