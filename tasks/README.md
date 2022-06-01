# Tasks

## To list available tasks

```
inv -l
```

## To dump the configuration

```
inv build.dump-config -f build-x86.yaml
```

## To build and run

```
inv build.build -f build-x86.yaml

inv build.unit-tests -f build-x86.yaml

inv build.run -f build-x86.yaml   # run ninja before to run
```
