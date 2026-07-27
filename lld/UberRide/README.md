# UberRide

A compact, in-memory C++17 ride-dispatch domain model. It demonstrates validated domain objects, deterministic ID generation, safe ownership (callers own users and drivers), synchronized trip transitions, driver search, and fare quotation.

## Build and test

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/uberride_demo
```

`Trip` intentionally models only the domain workflow. Persistence, authentication, payments, dispatch queues, observability, and real-time notifications belong behind infrastructure interfaces before deploying a production service.
