read_end, write_end = IO.pipe

if child_pid = fork
  # parent
  read_end.close
  Process.waitpid(child_pid)

  # This prints out true since we closed the fd in the parent
  puts "Is read end closed in parent?: #{read_end.closed?}"
else
  # child
  # sleep for 2 seconds to ensure parent completes the closing first
  sleep(2)


  # This prints out false since this is not closed in the child. The close call
  # in parent doesn't affect the fd copy of the child
  puts "Is read end closed in child?: #{read_end.closed?}"
  read_end.close
end
