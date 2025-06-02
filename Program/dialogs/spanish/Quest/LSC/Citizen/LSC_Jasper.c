// Джаспер Пратт - каторжник
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
				dialog.text = "Buen día, señor. ¿Desea algo?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+", ¿y cuál es el tuyo? Soy nuevo aquí...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha ocurrido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte algunas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo te va. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "¿Yo? Soy Jasper, el ex convicto del estado. Por eso la gente me mira de reojo. Ah, al diablo con ellos, me he acostumbrado...";
			link.l1 = "No me importa quién eras, lo que importa es quién eres ahora.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es una lástima que no todos piensen como usted, señor.";
			link.l1 = "Bueno, soy conocido por mi actitud liberal...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Me alegro por ti. No te preocupes, a pesar de mi pasado, no soy una amenaza para las bolsas y cofres de los habitantes de la Isla. Me alegra poder vivir en paz al fin.";
			link.l1 = "Encantado de conocerte, Jasper. ¡Nos vemos!"
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha ocurrido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte algunas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sí, claro. Te responderé si puedo. Pregunta.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo te convertiste en habitante de la Isla?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Te gusta este lugar?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Has mencionado que la gente te mira de reojo. ¿Es por tu pasado?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Esta Isla es bastante interesante, ¿no crees?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No hay preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Huí de la plantación cubiana. Éramos cinco y decidimos que era preferible morir que seguir rompiéndonos la espalda por palizas. Logramos engañar a los guardias y desaparecer en la jungla, luego llegamos a la orilla y construimos una balsa\nQueríamos llegar a Tortuga, pero el destino decidió otra cosa. Ninguno de nosotros sabía cómo navegar, así que nos perdimos. Luego se nos acabó el agua... No quiero recordar eso. Al final, fui el único que llegó a la Isla y sobrevivió.";
			link.l1 = "Ya veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sabes, estoy bien con eso. Después de todo lo que he pasado en la plantación, este lugar me parece un paraíso. No necesito mucho... Un poco de comida, agua y un vaso de ron cada noche. Nadie me molesta aquí y no pienso irme de este lugar. Moriré aquí cuando llegue mi hora.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "El caso es que la Isla es un patio de recreo para un ladrón misterioso. Las cerraduras no son un problema para él. Principalmente ronda las cámaras del almirante. Aunque nuestros cofres tampoco quedan intactos. Nadie sabe quién es este ladrón, así que sospechan de personas con... hm, pasado criminal\nSin embargo, el ladrón es un poco extraño: primero, solo toma botellas con licores y algunas baratijas, nunca toma objetos valiosos. ¿Gracioso, no?";
			link.l1 = "Entendido...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sí, estoy de acuerdo. He nadado mucho alrededor de los barcos internos de la Isla. Hay muy pocas salidas del agua. San Agustín, el lugar del puente. Gloria, el mástil caído. Si nadas cerca de la plataforma Fénix y luego alrededor de Ceres Smitie, llegarás a la cabina de Mary Casper en la proa del barco.\nLa grieta en el Tártaro te llevará a la prisión. Hay un agujero en la proa de San Agustín, puedes entrar en la sala de almacenamiento del almirante, pero es una acción poco aconsejable. La puerta más baja del Tártaro suele estar cerrada, recuerda eso.\n Y por supuesto, puedes entrar en Fernanda, es el filibote solitario y destrozado. Dicen que nadie vive allí, pero a menudo noto luces dentro de la cabina y a veces puedo oír extrañas canciones de borrachos y llantos.";
			link.l1 = "Interesante... Necesito explorar más este lugar.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Mierda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chica tonta!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no juegues a ser un caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada baja.");
				link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como dices...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
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
