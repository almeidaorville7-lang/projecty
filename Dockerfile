FROM gcc:14.4.0@sha256:db19db55a3bd1f836212a76854c4f6c7c4ccb0c9a9426dbf542e3505bc8cdfec

ENV XMAKE_ROOT=y
ENV PATH="/root/.local/bin:/root/.xmake/bin:${PATH}"

RUN curl -fsSL https://xmake.io/shget.text | bash -s v3.1.1 \
    && xmake --version

WORKDIR /app

COPY . .

RUN xmake

CMD ["xmake", "run", "projecty"]
