#ifndef _MINIX86_MEMORY_H
#define _MINIX86_MEMORY_H

#include <cstddef>

typedef unsigned char* exec_ptr;

exec_ptr exec_alloc(size_t size);
exec_ptr exec_realloc(exec_ptr ptr, size_t size);
void exec_free(exec_ptr ptr);

class ExecBuffer {
public:
	ExecBuffer(size_t size);
	~ExecBuffer();

	void resize(size_t size);

private:
	ExecBuffer(const ExecBuffer& buf);
	ExecBuffer& operator=(const ExecBuffer& buf);

	size_t m_size;
	exec_ptr m_mem;
};

#endif