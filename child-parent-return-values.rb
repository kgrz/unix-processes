# The return value of `fork` in the child is `nil`, not `0` unlike in the case
# of the `fork()` syscall. From the `fork()` manual:
#
#
# RETURN VALUES
#      Upon successful completion, fork() returns a value of 0 to the child
#      process and returns the process ID of the child process to the parent
#      process.  Otherwise, a value of -1 is returned to the parent process, no
#      child process is created, and the global variable errno is set to
#      indicate the error.

fork_value = fork

if !!fork_value
  puts "In parent #{fork_value}"
else
  puts "In child #{fork_value.nil? ? "nil" : "zero" }"
end
