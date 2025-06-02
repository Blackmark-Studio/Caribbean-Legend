// Гхерад Смиитс - матрос
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
				dialog.text = "¡Buen día, camarada, ja-ja! ¿Qué haces aquí?";
				link.l1 = TimeGreeting()+"¿Te conozco?";
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
			dialog.text = "Claro, no sabes, pero es fácil de arreglar, ¿verdad? Soy Gerard Smeets, marinero, un hombre de mar de Róterdam. Y tú pareces un contramaestre, ni más ni menos...";
			link.l1 = "Algo así. Mi nombre es "+GetFullName(pchar)+"Encantado de conocerte.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Pareces más un armador o un pagador... Sin duda eres un hombre bien educado. Encantado de conocerte. ¿Cómo llegaste aquí?";
			link.l1 = "He decidido explorar un área desconocida. Los bucaneros de Cuba me dijeron que había algo en esta área y decidí comprobarlo... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "¿Eres el único sobreviviente? ¿Dónde se hundió tu barco? ¿Cerca del anillo?";
			link.l1 = "Soy el único. Y mi tartana está en el fondo del mar, ni siquiera llegó al anillo.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ya veo. Bueno, estarás atrapado aquí por un tiempo. Visita a Sancho para conseguir un poco de ron, es una buena acción...";
			link.l1 = "Lo haré. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Claro, amigo. Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Cuéntame, ¿cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Quieres dejar la Isla y volver a tu vida normal?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿No te molestan los clanes?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Cómo se formó la Isla, tienes alguna idea sobre ello?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Llegué aquí con ese gallo engreído llamado Abbot. Estaba sirviendo en su barco. ¿Sabes qué? Gente como él nunca debería poner un pie en la cubierta de un barco porque traen mala suerte. El diablo debió haber hecho que navegara con nosotros. Solo teníamos que navegar de Jamaica a Belice, tan fácil como un pastel. Pero el destino nos persiguió: nuestro contramaestre cayó por la borda, un navegante cometió un error, los malditos españoles y una tormenta al final. Y aquí estamos.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ojalá lo supiera, amigo. Lo sabía antes, pero ya no. La vida aquí está bien, mucho ron y vino, buena comida, no mucha, pero de todas formas mejor que esa mierda que comía en los barcos\nTambién hay buena gente en la Isla. Hay gente con la que beber o con la que charlar. Me gusta aquí. Así que ni siquiera estoy seguro... No, supongo que no, no quiero irme. Solía estar enfadado y hambriento, ¡mira mi barriga ahora, ja-ja!";
			link.l1 = "¡Genial! Me alegro por ti.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No, no lo hacen. Simplemente no discutas con ellos y no visites sus territorios sin permiso. Realmente no les gusta. Los Narvales son buenos muchachos, la mayoría de ellos nacieron aquí y no han visto otra vida. Muchos de ellos son muy habilidosos, Jurgen Schmidt por ejemplo. ¡Es un dios de la herrería!";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Fácil como un pastel. Bancos de arena y arrecifes. El anillo exterior está hecho de barcos de arriba a abajo. Los barcos son atrapados por una tormenta, chocan contra los arrecifes o el anillo exterior mismo. Así es como crece la Isla. Aunque no tengo idea de por qué los barcos internos se mantienen sobre el agua.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!","¡Solo mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Quítala de en medio.","Escucha, no juegues a ser un caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Como desees...","Como usted diga...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que guardes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada baja.");
				link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como dices...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, compañero, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
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
