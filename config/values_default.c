/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#define NUM_CONFIG_GROUPS 4
static struct ConfigGroup config_list[NUM_CONFIG_GROUPS] = {
	{"General",		NULL, 0},
	{"Gameplay",	NULL, 0},
	{"Highscore",	NULL, 0},
	{"Radius",		NULL, 0}
};

void configInitializeDefaults() {
	int id, group;
	
	static int initialized = 0; 
	/* Variavel static em funcoes mantem seu valor entre chamadas. */
	if(initialized != 0) return;
	initialized = 1;
	
	INIT_GROUP("General", 10);
	ADD_CONFIG("MaximumFPS",			  30, NULL, 1);
	ADD_CONFIG("ResolutionX",			1024, NULL, 1);
	ADD_CONFIG("ResolutionY",			 768, NULL, 1);
	ADD_CONFIG("DebugMode",				   0, NULL, 3);
	
	ADD_CONFIG("LimitObject",			 150, NULL, 1);
	ADD_CONFIG("LimitCoral",			  12, NULL, 1);
	ADD_CONFIG("LimitPerson",			 100, NULL, 1);
	
	ADD_CONFIG("PersonInitialAmmount",	  30, NULL, 1);
	ADD_CONFIG("PersonCreateRate",		   5, NULL, 1);
	ADD_CONFIG("PersonAverageSpeed",	  10, NULL, 1);
	CLOSE_GROUP();
	
	INIT_GROUP("Radius", 4);
	ADD_CONFIG("Person",				   5, NULL, 1);
	ADD_CONFIG("Ship",					  50, NULL, 1);
	ADD_CONFIG("Coral",					  10, NULL, 1);
	ADD_CONFIG("Boat",					  10, NULL, 1);
	CLOSE_GROUP();
	
	INIT_GROUP("Gameplay", 5);
	ADD_CONFIG("TurnRate", 			    PI/2, NULL, 2);
	ADD_CONFIG("Acceleration",			  50, NULL, 1);
	ADD_CONFIG("Friction",				 0.5, "Valores negativos geram resultados imprevisiveis.", 2);
	ADD_CONFIG("TimesStuck",			   5, NULL, 1);
	ADD_CONFIG("InitialLives",			   3, NULL, 1);
	CLOSE_GROUP();
}