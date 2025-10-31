// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme una pregunta hace poco, " + GetAddress_Form(NPChar) + "...", "Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...", "¿Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Sí, realmente es la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (pchar.questTemp.Slavetrader == "FindRatPortobello")
		{
			link.l1 = "Escucha, ¿has visto a un corsario llamado François Gontier? Estuvo recientemente aquí en tu pueblo.";
			link.l1.go = "Portobello_rat_1";
		}
		// карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
		{
			link.l1 = "Escucha, ¿serías capaz de decirme dónde encontrar a un comerciante llamado Jaime Silicio? Se suponía que iba a venir a verte...";
			link.l1.go = "trial";
		}
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
		{
			link.l1 = "Mira, estoy buscando a un hombre llamado Bertrand Pinette, ¿has oído hablar de él? Un caballero imponente con una peluca rizada. Un comerciante. Puede que haya estado aquí...";
			link.l1.go = "FMQG";
		}
		//--> Письмо от покойника
		if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
        {
            link.l1 = "¿Podrías decirme dónde puedo encontrar a Marisa Caldera?";
            link.l1.go = "LFD_Tavern_1_1";
        }
		//<-- Письмо от покойника
		break;

	case "Portobello_rat_1":
		dialog.text = NPCStringReactionRepeat("No, no lo sé. No pasó por la taberna y tampoco lo vi en el pueblo.", "Ya has preguntado sobre eso y te he respondido.", "Te dije 'ya has preguntado por ese Gontier'.", "¡Escucha, aléjate y deja de molestarme! ¿Has perdido la chaveta por completo?", "block", 0, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Bueno, entonces seguiré buscando.", "Mm, supongo que sí...", "Sí, claro, he preguntado eso...", "Lo siento, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;

	case "trial":
		DelLandQuestMark(npchar);
		npchar.quest.trial = true;

		dialog.text = "Perdóname, señor, pero sólo un traidor o un borracho discutiría tales asuntos con un extraño. No quiero problemas.";
		link.l1 = "¿Un borracho, dices? Nos vemos, amigo.";
		link.l1.go = "exit";
		break;

	// Addon-2016 Jason ФМК-Гваделупа
	case "FMQG":
		dialog.text = "Nunca he oído hablar de él, amigo.";
		link.l1 = "Es un conocido de don Carlos de Milyar. ¿Seguro que nunca has oído hablar de él?";
		link.l1.go = "FMQG_1";
		break;

	case "FMQG_1":
		dialog.text = "Nunca. Si es amigo de De Milyar, ve al gobernador y pregunta por el señor Carlos. Él te contará sobre ese comerciante tuyo.";
		link.l1 = "Eso haré. ¡Gracias por el consejo!";
		link.l1.go = "FMQG_2";
		break;

	case "FMQG_2":
		DialogExit();
		AddQuestRecord("FMQ_Guadeloupe", "9");
		npchar.quest.FMQG = true;
	break;
	
	//--> Письмо от покойника
	case "LFD_Tavern_1_1":
		dialog.text = "¿Marisa? Hm... Hace tiempo que no la veo. Desde que le informaron de la muerte de su marido, no se ha dejado ver por la ciudad.";
		link.l1 = "¿Entonces es viuda?";
		link.l1.go = "LFD_Tavern_1_2";
		DelLandQuestMark(npchar);
	break;
		
	case "LFD_Tavern_1_2":
		dialog.text = "Sí. Su marido era el capitán de una pinaza mercante llamada 'Rompeolas'. Gracias a una licencia de la Compañía Neerlandesa de las Indias Occidentales, tenía acceso a casi todos los puertos del archipiélago. Se rumorea que no sobrevivió a un ataque pirata en su ruta de Belice a Capsterville. No es algo raro por aquí, pero para ella fue un golpe devastador.";
		link.l1 = "¿Y simplemente desapareció?";
		link.l1.go = "LFD_Tavern_1_3";
	break;
		
	case "LFD_Tavern_1_3":
		dialog.text = "Bueno, decir que desapareció es exagerar un poco. Pero desde entonces apenas se la ha visto en la ciudad. Curiosamente... de vez en cuando distintos hombres preguntan por ella. Igual que tú, capitán. Si no fuera tan devota, pensaría que... se ha escondido de la vista pública y se gana la vida como puede. Pero Marisa, antes de que muriera su esposo, no se perdía ni una misa. Vivía prácticamente en la iglesia, así que lo dudo mucho.";
		link.l1 = "¿Eso es todo? ¿No sabes nada más?";
		link.l1.go = "LFD_Tavern_1_4";
	break;
		
	case "LFD_Tavern_1_4":
		dialog.text = "Todo lo que sé, capitán, ya te lo he contado.";
		link.l1 = "...";
		link.l1.go = "LFD_Tavern_1_5";
	break;
		
	case "LFD_Tavern_1_5":
		DialogExit();
		AddDialogExitQuestFunction("LFD_Tavern_1");
	break;
	//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
