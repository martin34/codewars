https://github.com/buchgr/bazel-remote

```shell
docker pull buchgr/bazel-remote-cache
docker run -u 1000:1000 -v /tmp/remote-cache:/data \\n\t-p 9090:8080 -p 9092:9092 buchgr/bazel-remote-cache
bazel build --copt -g //... --remote_cache=http://localhost:9090

sudo apt install mini-httpd
htpasswd -cb ./foo martin 1234
docker run -v /tmp/remote-cache:/data \
    -v /home/martin/repo/codewars/foo:/etc/bazel-remote/htpasswd \
    -p 9090:8080 -p 9092:9092 buchgr/bazel-remote-cache \
    --htpasswd_file /etc/bazel-remote/htpasswd --max_size=5
bazel build --copt -g //... --remote_cache=http://martin:1234@localhost:9090
```

https://rollout.io/blog/how-to-set-up-mutual-tls-authentication/
