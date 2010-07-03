/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "configuration.h"
#include <string.h>

enum configValueType { TYPE_INT, TYPE_FLOAT, TYPE_BOOLEAN, TYPE_HEXADECIMAL };

typedef struct {
	char* name;
	configValue val;
	char* comment;
	enum configValueType type;
} ConfigItem;

struct ConfigGroup {
	char* groupName;
	ConfigItem* list;
	int list_size;
};

static void AddConfig(ConfigItem* target, int* id, char* config, float val, 
		enum configValueType type, char* comment) {
	target[*id].name = config;
	target[*id].val.num = (int)val;
	target[*id].val.real = val;
	target[*id].comment = comment;
	target[*id].type = type;
	++(*id);
}

void configSort(ConfigItem* target, int size) {
	/* TODO: inserir uma ordenacao aqui. */
}

#define ADD_CONFIG(str, val, comment, type) AddConfig(config_list[group].list, &id, str, val, comment, type)
#define INIT_GROUP(str, size) id=0, group = getGroupID(str); \
	AUTOMALLOCV(config_list[group].list, config_list[group].list_size = size);
#define CLOSE_GROUP() configSort(config_list[group].list, config_list[group].list_size)
	
#include "values_default.c"


void configurationInit(char* config_file) {
	FILE* source = fopen(config_file, "r");
	configInitializeDefaults();
	if(source) {
		configurationRead(source);
		fclose(source);
	}
	configurationGet();
}

void configurationWrite(FILE* target) {
	int group, i;
	for(group = 0; group < NUM_CONFIG_GROUPS; ++group) {
		fprintf(target, "[%s]\n", config_list[group].groupName);
		for(i = 0; i < config_list[group].list_size; ++i) {
			fprintf(target, "%s = ", config_list[group].list[i].name);
			switch(config_list[group].list[i].type) {
			case TYPE_INT:
				fprintf(target, "%d", config_list[group].list[i].val.num);
				break;
			case TYPE_FLOAT:
				fprintf(target, "%f", config_list[group].list[i].val.real);
				break;
			case TYPE_BOOLEAN:
				fprintf(target, "%s", config_list[group].list[i].val.num != 0 ? "true" : "false");
				break;
			case TYPE_HEXADECIMAL:
				fprintf(target, "%#.6x", config_list[group].list[i].val.num);
				break;
			default: break;
			}
			if(config_list[group].list[i].comment != NULL)
				fprintf(target, " // %s", config_list[group].list[i].comment);
			fprintf(target, "\n");
		}
		fprintf(target, "\n");
	}
}

void configurationFinish() {
	int group;
	for(group = 0; group < NUM_CONFIG_GROUPS; ++group)
		free(config_list[group].list);
	LEGACY_configurationFinish();
}

/* Setters */
static int config_currentGroup = -1;
void setCurrentGroup(char* new) {
	config_currentGroup = getGroupID(new);
}

int configSet(char* str, configValue val) {
	int i;
	for(i = 0; i < config_list[config_currentGroup].list_size; ++i) {
		if(strcasecmp(config_list[config_currentGroup].list[i].name, str) == 0 ) {
			config_list[config_currentGroup].list[i].val = val;
			return 0;
		}
	}
	return 1;
}

/* ConfigValue getters */
configValue configGetValue(char* group, char* config) {
	int groupid = getGroupID(group);
	return configGetValueFromID(groupid, getConfigID(groupid, config));
}
configValue configGetValueFromID(int groupid, int configid) {
	return config_list[groupid].list[configid].val;
}

/* ID getters */
int getGroupID(char* group) {
	int i;
	for(i = 0; i < NUM_CONFIG_GROUPS; ++i)
		if(strcasecmp(group, config_list[i].groupName) == 0)
			return i;
	return -1;
}
int getConfigID(int groupid, char* config) {
	int i;
	for(i = 0; i < config_list[groupid].list_size; ++i)
		if(strcasecmp(config, config_list[groupid].list[i].name) == 0 )
			return i;
	return -1;
}