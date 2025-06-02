// Дугал Эббот - дворянин
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
				dialog.text = "¡No quiero hablar contigo! Atacas a civiles pacíficos sin motivo y los provocas a pelear. ¡Lárgate!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saludos, señor. Permítame presentarme - Dougall Abbot. Es bueno ver a un hombre noble aquí. Estoy cansado de los campesinos locales. Nunca podría imaginar que tendría que vivir el resto de mis días entre gente común.";
				link.l1 = TimeGreeting()+". Me llamo "+GetFullName(pchar)+"Es un placer conocerte. ¿Y por qué no te gustan los lugareños?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "No los conoces bien. ¿Acabas de llegar aquí? No recuerdo ningún naufragio reciente, sin embargo... ";
			link.l1 = "Vine aquí en un pequeño bergantín...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sí, sucede a menudo - los barcos se hunden y solo unos pocos sobrevivientes llegan aquí en los botes de sus barcos. A veces la gente vive aquí durante meses y nunca los conoces.";
			link.l1 = "Ya veo. Fue un placer conocerte, señor Abbot. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte algunas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Y cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Qué puedes contarme sobre los lugareños?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Qué puedes decirme sobre los clanes?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Y qué hay del clima? ¿Las tormentas ocurren a menudo aquí?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Fue hace cinco años, pero todavía lo recuerdo perfectamente como si hubiera sucedido ayer. Un día desgraciado decidí navegar en mi filibote desde Port Royal hasta Belice, había una carga demasiado valiosa como para confiar el trato a otros.\nAl día siguiente comenzaron mis desventuras, primero, nuestro contramaestre se emborrachó y cayó por la borda, luego casi chocamos con los arrecifes y al final nuestro navegante cometió un error, así que navegamos en la dirección equivocada.\nLuego fuimos perseguidos por un bergantín y un galeón. Intentamos huir, pero eran insistentes. El galeón se quedó atrás pero el bergantín finalmente nos alcanzó.\nEl galeón estaba demasiado lejos de allí, así que abordamos el bergantín sin disparar. Esos perros españoles no lo esperaban y ganamos, pero la mayoría de mi tripulación murió.\nUnas pocas horas después, nos atrapó una tormenta, no pudimos luchar contra el clima con tan poca tripulación y ahora ves el resultado. Mi filibote está en algún lugar del anillo exterior, los otros tres sobrevivientes y yo llegamos aquí.";
			link.l1 = "Entendido...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Escoria. Todos ellos. Vidas bajas de todo tipo. Richard Shambon es un criminal, se le nota en la cara. ¿Kassel? Matar gente para él es tan natural como respirar. Jasper Pratt es un convicto. Musket es un borracho. ¿Debería continuar?\nJosef Loderdale es el único hombre decente aquí, excepto tú, él es un exmilitar de la marina inglesa. Hay dos nobles aquí, Antonio Betancourt y Lorenzo Solderra, maldita escoria española, ni siquiera me sentaría con él en la misma mesa.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Un montón de bastardos y escoria. Sin embargo, no nos hacen daño. Están más interesados en apuñalarse y dispararse entre ellos. No pueden vivir sin ello. Tampoco me gustan los piratas, pero debo admitir que hicieron de la Isla un lugar más pacífico cuando llegaron aquí.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Nunca lo hacen. Las tormentas suceden a menudo alrededor de la Isla, pero este lugar siempre está tranquilo y quieto, tal vez sea algún tipo de magia o la voluntad de Dios, no lo sé. A veces un viento fuerte puede llegar a este lugar y eso es todo. Las lluvias tampoco pueden causar daño.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo allí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Muchacha insensata!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada baja.","Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
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
