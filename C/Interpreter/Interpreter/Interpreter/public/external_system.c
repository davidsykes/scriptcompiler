#include "../internal/xalloc.h"
#include "external_system.h"

static void set_global_variable(const char* name, int value)
{

}

static void set_local_variable(const char* name, int value)
{

}

ExternalSystem* external_system_create(void)
{
	ExternalSystem* external_system = xmalloc(sizeof(*external_system));
	external_system->set_global_variable = set_global_variable;
	external_system->set_local_variable = set_local_variable;
	return external_system;
}