#pragma once

#include <string>
#include "GLDebugMessageSourceType.h"
#include "GLDebugMessageType.h"
#include "GLDebugMessageSeverityType.h"

using GLDebugMessageCallbackFunction = void (GLAPIENTRY *)(
    const GLDebugMessageSourceType source​Type, const GLDebugMessageType messageType​,
    const GLDebugMessageSeverityType severity​Type, const std::string_view message, GLuint messageID​​) noexcept;