/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include <allegro/keyboard.h>
#define NUM_CONFIG_GROUPS 6
static struct ConfigGroup config_list[NUM_CONFIG_GROUPS] = {
	{"General",		NULL, 0},
	{"Gameplay",	NULL, 0},
	{"Radius",		NULL, 0},
	{"Player1",		NULL, 0},
	{"Player2",		NULL, 0},
	{"Highscore",	NULL, 0}
};

void configInitializeDefaults() {
	int id, group;
	
	static int initialized = 0; 
	/* Variavel static em funcoes mantem seu valor entre chamadas. */
	if(initialized != 0) return;
	initialized = 1;
	
	INIT_GROUP("General", 14);
	ADD_CONFIG("MaximumFPS",			  30, TYPE_INT, NULL);
	ADD_CONFIG("Fullscreen",			   0, TYPE_BOOLEAN, NULL);
	ADD_CONFIG("ResolutionX",			1024, TYPE_INT, NULL);
	ADD_CONFIG("ResolutionY",			 768, TYPE_INT, NULL);
	ADD_CONFIG("NumPlayers",			   2, TYPE_INT, "Hardcoded maximum: 2");
	ADD_CONFIG("DebugMode",				   0, TYPE_BOOLEAN, NULL);
	ADD_CONFIG("ButtonExit",		 KEY_ESC, TYPE_INT, "Aperte 2x seguidas para sair");
	
	ADD_CONFIG("LimitObject",			 150, TYPE_INT, NULL);
	ADD_CONFIG("LimitCoral",			  12, TYPE_INT, NULL);
	ADD_CONFIG("LimitPerson",			 100, TYPE_INT, NULL);
	
	ADD_CONFIG("PersonInitialAmmount",	  30, TYPE_INT, NULL);
	ADD_CONFIG("PersonCreatePeriod",	   5, TYPE_FLOAT, NULL);
	ADD_CONFIG("PersonAverageSpeed",	  10, TYPE_FLOAT, NULL);

	ADD_CONFIG("CoralInitialAmount",  	  12, TYPE_INT, NULL);
	CLOSE_GROUP();
	
	INIT_GROUP("Radius", 4);
	ADD_CONFIG("Person",				   5, TYPE_FLOAT, NULL);
	ADD_CONFIG("Ship",					  50, TYPE_FLOAT, NULL);
	ADD_CONFIG("Coral",					  10, TYPE_FLOAT, NULL);
	ADD_CONFIG("Boat",					  10, TYPE_FLOAT, NULL);
	CLOSE_GROUP();
	
	INIT_GROUP("Gameplay", 10);
	ADD_CONFIG("TurnRate", 			    PI/2, TYPE_FLOAT, NULL);
	ADD_CONFIG("Acceleration",			  50, TYPE_FLOAT, NULL);
	ADD_CONFIG("Friction",				 0.5, TYPE_FLOAT, "Valores negativos geram resultados imprevisiveis.");
	ADD_CONFIG("TimeStuck",				   5, TYPE_INT, NULL);
	ADD_CONFIG("InitialLives",			   3, TYPE_INT, NULL);
	ADD_CONFIG("UnloadDistance",		 120, TYPE_FLOAT, NULL);
	ADD_CONFIG("UnloadTime",			   1, TYPE_FLOAT, NULL);
	ADD_CONFIG("BoatCapacity",			  10, TYPE_INT, NULL);
	ADD_CONFIG("AnchorFrictionMultiplier",10, TYPE_FLOAT, NULL);
	ADD_CONFIG("ExtraLifeScore",		 500, TYPE_INT, NULL);
	CLOSE_GROUP();
	
	INIT_GROUP("Highscore", 5);
	ADD_CONFIG("Rank1Score",			   0, TYPE_INT, NULL);
	ADD_CONFIG("Rank2Score",			   0, TYPE_INT, NULL);
	ADD_CONFIG("Rank3Score",			   0, TYPE_INT, NULL);
	ADD_CONFIG("Rank4Score",			   0, TYPE_INT, NULL);
	ADD_CONFIG("Rank5Score",			   0, TYPE_INT, NULL);
	CLOSE_GROUP();
	
	INIT_GROUP("Player1", 6);
	ADD_CONFIG("Color",			    0xFE0000, TYPE_HEXADECIMAL, NULL);
	ADD_CONFIG("ButtonAccel",		   KEY_W, TYPE_INT, NULL);
	ADD_CONFIG("ButtonBrake",		   KEY_S, TYPE_INT, NULL);
	ADD_CONFIG("ButtonTurnLeft",	   KEY_A, TYPE_INT, NULL);
	ADD_CONFIG("ButtonTurnRight",	   KEY_D, TYPE_INT, NULL);
	ADD_CONFIG("ButtonAnchor",		   KEY_Q, TYPE_INT, NULL);
	CLOSE_GROUP();
	
	INIT_GROUP("Player2", 6);
	ADD_CONFIG("Color",			    0x00FEFF, TYPE_HEXADECIMAL, NULL);
	ADD_CONFIG("ButtonAccel",		  KEY_UP, TYPE_INT, NULL);
	ADD_CONFIG("ButtonBrake",		KEY_DOWN, TYPE_INT, NULL);
	ADD_CONFIG("ButtonTurnLeft",	KEY_LEFT, TYPE_INT, NULL);
	ADD_CONFIG("ButtonTurnRight",  KEY_RIGHT, TYPE_INT, NULL);
	ADD_CONFIG("ButtonAnchor",	   KEY_0_PAD, TYPE_INT, NULL);
	CLOSE_GROUP();
}
