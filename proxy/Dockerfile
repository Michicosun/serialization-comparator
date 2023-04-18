FROM soa-project-1-base

ARG PROXY_PORT
ARG WORKER_PORT

RUN echo "proxying: $PROXY_PORT -> $WORKER_PORT"

# put build args to environment
ENV PROXY_PORT=$PROXY_PORT
ENV WORKER_PORT=$WORKER_PORT

CMD [ "./build/proxy/proxy-bin" ]
