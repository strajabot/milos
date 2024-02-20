set confirm off
set architecture riscv:rv64
symbol-file kernel
tbreak entry
target remote localhost:26000
set disassemble-next-line auto

define break_save
  save breakpoints ./breakpoints
end

define break_restore
  source ./breakpoints
end
