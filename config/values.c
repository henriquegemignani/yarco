/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "configuration.h"
#include <string.h>

typedef struct {
	char* name;
	configValue val;
	char* comment;
	int type; /* 1 == Int, 2 == Float, 3 == Boolean */
	
} ConfigItem;

struct ConfigGroup {
	char* groupName;
	ConfigItem* list;
	int list_size;
};

static void AddConfig(ConfigItem* target, int* id, char* config, float val, char* comment, int type);


#define NUM_CONFIG_GROUPS 3
static struct ConfigGroup config_list[NUM_CONFIG_GROUPS] = {
	{"General",		NULL, 0},
	{"Gameplay",	NULL, 0},
	{"Highscore",	NULL, 0}
};

#define ADD_CONFIG(str, val, comment, type) AddConfig(config_list[group].list, &id, str, val, comment, type)
void configInitializeDefaults() {
	int id, group;
	
	static int initialized = 0;
	if(initialized != 0) return;
	initialized = 1;
	
	id = 0, group = 0; /* General */
	AUTOMALLOCV(config_list[group].list, 13);
	config_list[group].list_size = 13;
	
	ADD_CONFIG("MaximumFPS",			  30, NULL, 1);
	ADD_CONFIG("ResolutionX",			1024, NULL, 1);
	ADD_CONFIG("ResolutionY",			 768, NULL, 1);
	ADD_CONFIG("LimitObject",			 150, NULL, 1);
	ADD_CONFIG("LimitCoral",			  12, NULL, 1);
	ADD_CONFIG("LimitPerson",			 100, NULL, 1);
	
	ADD_CONFIG("PersonInitialAmmount",	  30, NULL, 1);
	ADD_CONFIG("PersonCreateRate",		   5, NULL, 1);
	ADD_CONFIG("PersonAverageSpeed",	  10, NULL, 1);
	
	ADD_CONFIG("RadiusPerson",			   5, NULL, 1);
	ADD_CONFIG("RadiusShip",			  50, NULL, 1);
	ADD_CONFIG("RadiusCoral",			  10, NULL, 1);
	ADD_CONFIG("RadiusBoat",			  10, NULL, 1);
	
	id = 0, group = 1; /* Gameplay */
	AUTOMALLOCV(config_list[group].list, 5);
	config_list[group].list_size = 5;
	ADD_CONFIG("TurnRate", 			    PI/2, NULL, 2);
	ADD_CONFIG("Acceleration",			  50, NULL, 1);
	ADD_CONFIG("Friction",				 0.5, NULL, 2);
	ADD_CONFIG("TimesStuck",			   5, NULL, 1);
	ADD_CONFIG("InitialLives",			   3, NULL, 1);
}

static void AddConfig(ConfigItem* target, int* id, char* config, float val, char* comment, int type) {
	target[*id].name = config;
	target[*id].val.num = (int)val;
	target[*id].val.real = val;
	target[*id].comment = comment;
	target[*id].type = type;
	++(*id);
}

void configurationWrite(FILE* target) {
	int group, i;
	for(group = 0; group < NUM_CONFIG_GROUPS; ++group) {
		fprintf(target, "[%s]\n", config_list[group].groupName);
		for(i = 0; i < config_list[group].list_size; ++i) {
			fprintf(target, "%s = ", config_list[group].list[i].name);
			switch(config_list[group].list[i].type) {
			case 1:
				fprintf(target, "%d", config_list[group].list[i].val.num);
				break;
			case 2:
				fprintf(target, "%f", config_list[group].list[i].val.real);
				break;
			case 3:
				fprintf(target, "%s", config_list[group].list[i].val.num != 0 ? "true" : "false");
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