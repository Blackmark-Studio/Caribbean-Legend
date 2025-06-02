// официантка Наталия Бушелл
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
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "¡Oh! Y me dijeron que te habías ahogado... ¡Mentirosos!";
			link.l1 = "¡Claro que lo hicieron! ¡Ja! ¡Estoy bien!";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Buen día, " + GetAddress_Form(NPChar) + ". ¿Primera vez aquí? No te he visto antes... Espero que nos visites más a menudo, Sancho puede ofrecer una excelente variedad de bebidas. Sí, y mi nombre es Nathalie y ayudo a Sancho con los asuntos de la taberna.";
			link.l1 = TimeGreeting() + ". Mi nombre es " + GetFullName(pchar) + " Encantado de conocerte. Y no podías verme antes. He llegado aquí recientemente.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Ah, " + GetFullName(pchar) + "! " + TimeGreeting() + ". ¿Quieres algo?";
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
		dialog.text = "¿Recientemente? ¿Otro barco se ha estrellado? No he oído nada... ¿O acaso no llegaste aquí como monsieur Turam en los restos del mástil? Oh, perdóname mi curiosidad, la naturaleza de las mujeres, ya sabes.";
		link.l1 = "No, está bien, Nathalie. He llegado aquí en una barca pero se ha hundido. Fue un placer conocerte. ¡Nos vemos por ahí!";
		link.l1.go = "exit";
		link.l2 = "No, está bien. Solo quería hacerte algunas preguntas sobre la isla.";
		link.l2.go = "int_quests"; // информационный блок
		NextDiag.TempNode = "First time";
		break;

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "Estoy escuchando.";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "Trabajas en la taberna. ¿Qué puedes decirme sobre el dueño?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Y cómo terminaste aquí?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Cuántas personas viven aquí?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Nunca te sorprende ver caras nuevas aquí?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Si me disculpas...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "Solo cosas positivas,  " + GetAddress_Form(NPChar) + "Sancho siempre tiene una gran variedad de bebidas - desde vinos añejos hasta simple cerveza y ron. Hace varios años encontró una enorme reserva de vinos de época. Sancho pasó dos meses moviendo cajas con botellas a su tienda\nY ahora estamos bien abastecidos con vino, solo los gobernadores podían permitirse tanto en el archipiélago. El ron tampoco es un problema. Sancho puede proporcionarte no solo bebidas, sino también noticias frescas, un buen consejo y una cama cálida para pasar la noche.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Oh, esa es una historia triste. Hace siete años, huí con mi pretendiente de la casa de mis padres y decidimos mudarnos a Belice desde Santiago. El navegante cometió un error cerca de Tierra Firme, así que navegamos en una dirección equivocada hacia el norte y fuimos atrapados por una tormenta. Nuestro barco se hundió no muy lejos del anillo exterior. Mi pretendiente murió ese día al igual que la mayoría de los demás. Yo y los sobrevivientes hemos comenzado nuevas vidas aquí, en la Isla.";
		link.l1 = "Historia triste...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "Bastante. Los clanes de los Rivados y los Narvales son numerosos, llevan viviendo aquí décadas. No hay tanta gente común, pero la taberna está llena cada noche. Apenas logro servir las bebidas.";
		link.l1 = "¿En serio? Interesante.";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "¿Y por qué deberíamos? Hay muchas caras nuevas que llegan muy a menudo. Ni siquiera sé cuántos de nosotros vivimos aquí. A veces veo a un hombre por primera vez y me dice que ha estado viviendo aquí durante un año.";
		link.l1 = "Bueno...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!", "¡Solo mira eso! En cuanto me perdí en la contemplación, decidiste revisar mi cofre.", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
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

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tus armas. Me pone nervioso.", "Sabes, correr con espada no se tolera aquí. Guárdala.", "Escucha, no juegues al caballero medieval corriendo con un arma. Quítatela, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que envaines tu espada.", "Escucha, soy ciudadano de la ciudad y te pediría que envaines tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando la gente camina frente a mí con su arma lista. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
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
