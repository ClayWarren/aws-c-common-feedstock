#include <aws/common/common.h>
#include <aws/common/allocator.h>
#include <aws/common/byte_buf.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    struct aws_allocator *allocator = aws_default_allocator();
    struct aws_byte_buf buffer;
    struct aws_byte_cursor first = aws_byte_cursor_from_c_str("Windows ");
    struct aws_byte_cursor second = aws_byte_cursor_from_c_str("ARM64");
    aws_common_library_init(allocator);
    if (aws_byte_buf_init_copy_from_cursor(&buffer, allocator, first)) return 1;
    if (aws_byte_buf_append_dynamic(&buffer, &second)) return 2;
    if (buffer.len != 13 || memcmp(buffer.buffer, "Windows ARM64", 13)) return 3;
    aws_byte_buf_clean_up(&buffer);
    aws_common_library_clean_up();
    puts("Installed AWS C common allocation and buffer-growth test passed");
    return 0;
}
