// Виктор Кассель - бандит
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
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
			dialog.text = "Mm... ¿Qué quieres, amigo? Si quieres hablar, tengo que decepcionarte. No tengo ganas de hablar.";
			link.l1 = "Lástima... Quería hablar. Soy un recién llegado aquí y apenas estoy conociendo a la gente...";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, " + GetFullName(pchar) + ". ¿Qué quieres?";
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha ocurrido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l1.go = "rumours_LSC";
			link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l2.go = "int_quests"; // информационный блок
			link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "¿Un recién llegado? Hm. Está bien entonces. Soy Víctor Cassel y será mejor que evites hacerme enojar mientras estoy de mal humor. Y también cuando estoy de buen humor. No pierdo el tiempo charlando, golpeo a la gente de inmediato si son demasiado insistentes.";
		link.l1 = "Bueno y yo soy " + GetFullName(pchar) + "Por cierto, puedo devolver el golpe fácilmente. Pero espero que no haya razón para hacerlo. No te molestaré si eres tan poco sociable. Adiós.";
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
		link.l2.go = "rumours_LSC";
		link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
		link.l3.go = "int_quests"; // информационный блок
		NextDiag.TempNode = "First time";
		break;

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "¿Sí? ¿Y qué puedo contarte?";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo llegaste aquí?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Cómo es la vida aquí?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Quién es la persona más... importante aquí?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Y dónde puedo conseguir monedas en la Isla?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Perdón...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "Lo siento, amigo, pero ¿cuál es tu preocupación? Simplemente acabo de llegar. No quiero hablar de esa historia, especialmente con un hombre que no conozco.";
		link.l1 = "Bueno, lo siento...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Parece un aburrimiento. Cansino, monótono y sin sentido. Me uniré a los piratas dShark, esos muchachos valen la pena. Me uniré a la tripulación con gran placer, solo necesito... explorar un poco. Estoy seguro de que encontrarán una forma de salir de la Isla.";
		link.l1 = "¿En serio? Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "¡El almirante, sin duda! Los piratas tienen a los Narvales y a los Rivados bajo su puño y los clanes no se atreven a decir nada. Los siguientes en la fila son los líderes de los clanes, Donald Greenspy de los Narvales y Black Eddy de los Rivados. Axel Yost, un comerciante de los Narvales, es también un hombre importante. Y por supuesto Sancho Carpentero, es un buen muchacho...";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "Baúles. Por supuesto, primero debes abrirlos, aquí la gente no confía en los demás, así que todos los baúles tienen cerraduras. Déjame decirte una cosa, amigo, las mejores chucherías se guardan dentro de los barcos bajo la vigilancia de sus dueños.\nTambién puedes explorar el anillo exterior, pero reza para no caer por la madera podrida. O puedes cazar cangrejos gigantes, puedes obtener un buen precio por la carne de sus pinzas.";
		link.l1 = "Entendido...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo allí, eh? ¡Ladrón!", "¡Solo mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
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

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con una hoja no se tolera aquí. Guárdala.", "Escucha, no juegues a ser un caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada enfundada.", "Escucha, soy ciudadano de la ciudad y te pediría que envaines tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como digas...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, compadre, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan frente a mí con su arma lista. Me da miedo...");
			link.l1 = RandPhraseSimple("Entendido.", "Lo estoy llevando.");
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
