FROM soa-project-1-base

ARG PORT
ARG METHOD

RUN echo "using port: $PORT, method: $METHOD"

# put build args to environment
ENV PORT=$PORT
ENV METHOD=$METHOD

CMD [ "./build/worker/worker-bin" ]
