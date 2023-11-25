#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"
#include "sokol_log.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

int main() {
	SDL_Window *window = NULL;
	SDL_GLContext gl_ctx;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL_Init failed (%s)", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_LoadLibrary(NULL);

	const Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow("SDL3 + Sokol", 800, 600, window_flags);
	if (window == NULL) {
		SDL_Log("SDL_CreateWindow failed (%s)", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	gl_ctx = SDL_GL_CreateContext(window);
	if (SDL_GL_SetSwapInterval(-1) != 0) {
		SDL_Log("SDL_GL_SetSwapInterval failed (%s)", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	sg_desc desc = { 0 };
	desc.logger.func = slog_func;
	sg_setup(desc);

	// clang-format off
	const float vertices[] = {
        // positions        // colors
         0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f
    };
	// clang-format on

	sg_buffer_desc buffer_desc = { 0 };
	buffer_desc.data = SG_RANGE(vertices);
	sg_buffer vbuf = sg_make_buffer(buffer_desc);

	sg_shader_desc shader_desc = { 0 };
	shader_desc.vs.source = "#version 330\n"
							"layout(location=0) in vec4 position;\n"
							"layout(location=1) in vec4 color0;\n"
							"out vec4 color;\n"
							"void main() {\n"
							"  gl_Position = position;\n"
							"  color = color0;\n"
							"}\n";
	shader_desc.fs.source = "#version 330\n"
							"in vec4 color;\n"
							"out vec4 frag_color;\n"
							"void main() {\n"
							"  frag_color = color;\n"
							"}\n";
	sg_shader shd = sg_make_shader(shader_desc);

	sg_pipeline_desc pipeline_desc = { 0 };
	pipeline_desc.shader = shd;
	pipeline_desc.layout = { 0 };
	pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
	pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;
	sg_pipeline pip = sg_make_pipeline(pipeline_desc);

	sg_bindings bind = { 0 };
	bind.vertex_buffers[0] = vbuf;

	sg_pass_action pass_action = { 0 };

	while (true) {
		bool finished = false;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				finished = true;
				break;
			}
		}

		if (finished) {
			break;
		}

		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		sg_begin_default_pass(&pass_action, w, h);
		sg_apply_pipeline(pip);
		sg_apply_bindings(&bind);
		sg_draw(0, 3, 1);
		sg_end_pass();
		sg_commit();

		SDL_GL_SwapWindow(window);
	}

	sg_shutdown();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
