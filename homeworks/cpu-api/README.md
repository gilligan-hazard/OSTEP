# CPU API

Solutions for [Interlude: Process API](http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf) end-of-chapter exercises.

To compile:

```
prompt> make
```

To run all solutions except `p4`:

```
prompt> ./p1
```

```
prompt> ./p8
```

For `p4`, specify the `exec` variant (`execl`, `execle`, `execlp`, `execv`, `execvp`, or `execvP`) with which to run `ls`:

```
prompt> ./p4 execl
```