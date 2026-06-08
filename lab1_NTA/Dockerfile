FROM gcc:latest

WORKDIR /app

COPY *.cpp *.h ./

RUN g++ -O2 -o program \
    main.cpp \
    Operations.cpp \
    MillerRabin.cpp \
    Pollard.cpp \
    function_Brilhart.cpp \
    Brilhart.cpp

ENTRYPOINT ["./program"]