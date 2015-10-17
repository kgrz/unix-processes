# Even when forked, the file descriptors are the same

read_end, write_end = IO.pipe

if child_pid = fork
  # parent
  puts read_end.fileno
else
  # child
  puts read_end.fileno
end
