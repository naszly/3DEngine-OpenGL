
#include "system.h"
#include "engine.h"

System::System(Context &context, Input &input)
        : context(context), input(input), entityManager(Engine::getInstance().getEntityManager()) {}

