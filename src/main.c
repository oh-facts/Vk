
#include <yk.h>



//ToDo(facts): Better Debug profiles.
// 11/23 1758
//ToDo(facts): Fix flickering triangle (sync problem I think)
//             Fixed.
//                  1. I was handling cmds incorrectly in win32
//                  2. My rendering attatchment info was outside of loop
//ToDo(facts): Destroy resources
//ToDo(facts): Posix window so my linux friends can see my triangle
//ToDo(facts): Window Abstraction
//ToDo(facts): Renderer Abstraction :skull:
//ToDo(facts): VkAssertResult profiles?




struct YkMemory
{
    int is_initialized;
    u64 perm_storage_size;
    void *perm_storage;
    u64 temp_storage_size;
    void *temp_storage;
};

typedef struct YkMemory YkMemory;



#if DEBUG
    LPVOID base_address = (LPVOID)Terabytes(2);
#else
    LPVOID base_address = 0;
#endif

int main(int argc, char *argv[])
{


    YkMemory engine_memory = {0};
    engine_memory.perm_storage_size = Megabytes(64);
    engine_memory.temp_storage_size = Megabytes(64);

    u64 total_size = engine_memory.perm_storage_size + engine_memory.temp_storage_size;

    engine_memory.perm_storage = VirtualAlloc(base_address, total_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    engine_memory.temp_storage = (u8*)engine_memory.perm_storage + engine_memory.perm_storage_size;

    YkWindow win = { 0 };
    yk_innit_window(&win);

    YkRenderer ren = { 0 };
    yk_innit_renderer(&ren, &win);
   
  
    while (1)
    {
        yk_window_poll();

        vk_draw_frame(&ren);
       
    }

    yk_renderer_wait(&ren);

    return 0;
}