# Scala

## Get started

### Initial setup

Ref: https://docs.scala-lang.org/getting-started/index.html
Ref: https://get-coursier.io/docs/cli-installation
```
curl -fLo cs https://git.io/coursier-cli-"$(uname | tr LD ld)"
chmod +x cs
./cs install cs
```

Add to path: `export PATH="$PATH:/home/martin/.local/share/coursier/bin"`

```
./cs setup
```

### Create Project

`sbt new scala/hello-world.g8`

### Run

```
sbt
> ~run
```

### Unit tests

Ref: https://www.scalatest.org/user_guide/using_scalatest_with_sbt
Ref: https://www.scalatest.org/user_guide/writing_your_first_test
