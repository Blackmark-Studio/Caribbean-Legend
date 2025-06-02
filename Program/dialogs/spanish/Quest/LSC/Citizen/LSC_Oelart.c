// Оеларт Котеел - канонир
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "¡Buen día, señor! ¿Le gusta el clima?";
				link.l1 = TimeGreeting()+". Me siento bien con cualquier clima excepto tormentas en el mar abierto...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha pasado algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Confía en mí, siento lo mismo. Nunca te he visto antes... mi nombre es Oelart Koteel y era maestro de cañones en el barco de guerra holandés.";
			link.l1 = ""+GetFullName(pchar)+"Sí, soy un recién llegado aquí. De hecho, acabo de llegar.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Yo también soy un novato, llevo aquí menos de un año. Y realmente espero no quedarme aquí demasiado tiempo, aunque todos intentan persuadirme de lo contrario. ¡Encantado de conocerte!";
			link.l1 = "Encantado de conocerte también, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Quieres dejar la Isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Alguna vez has pensado cómo se formó la Isla?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Alguna vez has visitado los barcos del clan?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Ninguna pregunta. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Bastante banal. Luchamos contra una goleta inglesa y casi ganamos la batalla. Huyeron, así que los perseguimos. Pasó un día, estábamos cerca de atraparlos, pero dispararon contra nuestro palo mayor y, por supuesto, lograron escapar\nEn cuanto a nosotros, casi nos hundimos por un fuerte vendaval, luego fuimos arrastrados por una corriente y al final nuestro barco fue lanzado a un arrecife cerca del anillo exterior. Solo muy pocos lograron sobrevivir...";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Este es mi sueño. No puedes imaginar lo aburrido que estoy de este lugar. Pero ¿cómo puedo dejarlo? No tengo ni idea. No hay barcos aquí y no hay oportunidad de construir uno nuevo. Sería un suicidio navegar en un bote pequeño.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Según los barcos, tiene alrededor de cien años. Pero existe la posibilidad de que sea más antiguo, por el anillo exterior. Está hecho de barcos de arriba a abajo, quizás los navíos más antiguos estén en el fondo del mar\nEn cuanto a la formación de la Isla... Creo que las corrientes y tormentas han estado trayendo barcos moribundos aquí, así que se formó un banco artificial. El anillo exterior se construyó sobre él\nLos barcos interiores en los que vivimos... o fueron los primeros o de alguna manera lograron pasar el anillo exterior. Es muy posible, al fin y al cabo, que el Almirante y sus piratas nos hayan alcanzado en su bergantín.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "He visitado a los Rivados. Black Eddy una vez necesitó una consulta sobre los cañones del barco y ahora no tengo idea de por qué. Así que uno de los chicos negros me encontró y me dio la contraseña. Visité a su 'Protector' y 'Velasco'. Los guardias son duros, así que ni siquiera intentes pasarlos sin una contraseña.";
			link.l1 = "Ya veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo allí, eh? ¡Ladrón!","¡Solo mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Mierda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chiquilla tonta!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con la espada no se tolera aquí. Guárdala.","Escucha, no te hagas el caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Está bien.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada baja.","Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Está bien.","Como digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan delante de mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Me lo estoy llevando.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
