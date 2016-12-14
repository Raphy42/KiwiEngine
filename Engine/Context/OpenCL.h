//
// Created by Raphaël Dantzer on 13/12/16.
//

#ifndef KIWIENGINE_OPENCL_H
#define KIWIENGINE_OPENCL_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../../Core/Initializable.h"
#include "../../Core/Graphics.h"

namespace Kiwi { namespace Engine { namespace Context {
            class OpenCL : public Core::Initializable {
            public:
                virtual void PreInit() override;

                virtual void Init() override;

                virtual void PostInit() override;

                virtual void Update() override;

                void CreateKernelFromFile(const char *filename, const char *kernel_name);
                void CreateKernelFromProgram(const char *kernel_name);
                void CreateKernels(std::vector<const char *> kernel_name);

                cl_mem CreateBufferFromVBO(cl_GLuint vbo, cl_mem_flags permission);
                cl_mem CreateBuffer(size_t size, cl_mem_flags permission, void *host_ptr);

                const cl_command_queue getQueue() const;
                const cl_kernel getKernel(std::string kernel) const;
                const void getStatus(cl_int status, const char *caller);

            private:
                cl_uint                                                         _platformCount;
                cl_platform_id                                                  *_platforms;
                cl_device_id                                                    _device;
                cl_uint                                                         _deviceCount;
                cl_context                                                      _context;
                cl_command_queue                                                _queue;
                cl_int                                                          _status;
                cl_program                                                      _program;
                std::unique_ptr<std::unordered_map<std::string, cl_kernel>>     _kernels;

            };
        }
    }
}


#endif //KIWIENGINE_OPENCL_H
