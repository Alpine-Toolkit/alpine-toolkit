# Invoke Tasks

* https://www.pyinvoke.org
* https://docs.pyinvoke.org/en/stable

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
inv -f build-x86.yaml build.build

inv -f build-x86.yaml build.unit-tests

inv -f build-x86.yaml build.run   # run ninja before to run
```

