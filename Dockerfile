FROM drogonframework/drogon:latest

WORKDIR /app

COPY . .

RUN mkdir -p build \
 && cd build \
 && cmake .. \
 && cmake --build .

EXPOSE 8080

CMD ["/app/build/cpp_trabalho_lp1_api"]
