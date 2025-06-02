// Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew")) // найм в команду
			{
				dialog.text = "Buen día, " + GetAddress_Form(NPChar) + ". Soy consciente de que eres el capitán de tu propio barco. Tengo un trato para ti.";
				link.l1 = "Estoy escuchando, " + GetAddress_FormToNPC(NPChar) + ". ¿Qué tipo de trato?";
				link.l1.go = "crew";
				link.l2 = "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", pero tengo prisa.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			dialog.text = LinkRandPhrase("¡Eh, capitán! ¿Qué quieres de un simple marinero?", "Buen día, señor. ¿En qué puedo ayudarle?", "Buen día, señor. ¿Desea algo?");
			link.l1 = "¡Encantado de conocerte, camarada! Mi nombre es " + GetFullName(pchar) + "¿Tienes un minuto para hablar?";
			link.l1.go = "question";
			link.l2 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información sobre esta colonia.");
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l3 = "Solo quería saludar. ¡Nos vemos!";
			link.l3.go = "exit";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¿Usted otra vez, señor? ¿Qué más quiere?";
			link.l1 = "¿Tienes un minuto para hablar?";
			link.l1.go = "question";
			link.l2 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información sobre esta colonia.");
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l3 = "No, amigo, no es nada. ¡Buena suerte!";
			link.l3.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "question":
		dialog.text = NPCStringReactionRepeat("" + GetFullName(npchar) + " a su servicio, ¡buen señor! ¿Qué desea saber?", "¡Encantado de hablar contigo, capitán!", "Bueno... Supongo que todavía tengo algo de tiempo para hablar...", "Desafortunadamente, tengo que irme ahora. ¡Adiós!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("¿Tienes algo interesante que contarme?", "¿Tienes algo interesante que contarme?", "¿Tienes algo interesante que contarme?", "Claro. ¡Buena suerte!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

	case "crew":
		switch (hrand(2))
		{
		case 0:
			sTemp = "Mis compañeros y yo tuvimos que bajar a tierra de nuestro último barco debido a diversas enfermedades y lesiones. Pero ahora todos estamos sanos y queremos volver a trabajar como marineros. ¿Quiere contratarnos?";
			break;
		case 1:
			sTemp = "A mí y a algunos de mis chicos nos han despedido de un mercante debido al fin de su contrato. Llevamos ya mucho tiempo sin una sola pieza de ocho, así que queremos volver a trabajar. ¿Necesita marineros hábiles para su tripulación?";
			break;
		case 2:
			sTemp = "Mis compañeros y yo acabamos de volver de un viaje hace dos semanas. El capitán del barco nos ha despedido y nos lo hemos pasado muy bien. Pero ahora nuestros bolsillos están vacíos, así que es hora de zarpar de nuevo. ¿Quiere contratarnos, capitán?";
			break;
		}
		dialog.text = sTemp;
		link.l1 = "Bueno, estoy listo para discutir tu propuesta. ¿Cuántos sois y en qué sois buenos?";
		link.l1.go = "crew_1";
		link.l2 = "Lo siento, marinero, pero ya tengo suficientes hombres. Deberías buscarte otro capitán.";
		link.l2.go = "exit";
		break;

	case "crew_1":
		switch (sti(npchar.quest.crew.type))
		{
		case 0:
			sTemp = "Somos los mejores trabajando con velas y aparejos. Sin ser demasiado modesto, diría que somos profesionales en el manejo de barcos, así que no se preocupe, no le fallaremos ni en las tormentas más fuertes.";
			break;
		case 1:
			sTemp = "Lo que más nos gusta es estar en la cubierta del cañón. Pocos de nosotros hemos servido en buques de guerra de verdad. Podemos cargar y disparar cañones como nadie de tu tripulación puede. Puedes contar con nosotros en cada combate duro.";
			break;
		case 2:
			sTemp = "Somos buenos abordadores capitán, hicimos algunas carreras en corsarios antes de esto. Conocemos el brillo de los sables y el olor de la pólvora y la sangre. Esa es nuestra vocación. No es fácil derrotarnos en una lucha cuerpo a cuerpo, ¡así que siempre puede contar con nuestras espadas, capitán!";
			break;
		}
		dialog.text = "Hay " + sti(npchar.quest.crew.qty) + " de nosotros y contrataremos solo juntos. Podemos realizar todas las tareas básicas de marinero." + sTemp + "";
		if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
		{
			link.l1 = "Suena como los hombres que estoy buscando. ¿Qué hay de tu adelanto?";
			link.l1.go = "crew_2";
			link.l2 = "Lo siento, marinero, pero necesito otras habilidades en este momento. Deberías encontrar otro capitán.";
			link.l2.go = "exit";
		}
		else
		{
			link.l1 = "Lo siento, marinero, pero no tengo suficiente espacio en mi barco. Deberías buscarte otro capitán.";
			link.l1.go = "exit";
		}
		break;

	case "crew_2":
		iTemp = sti(npchar.quest.crew.money) * sti(npchar.quest.crew.qty);
		dialog.text = "" + FindRussianMoneyString(sti(npchar.quest.crew.money)) + " por cada uno. Y luego el sueldo mensual de un marinero común. No pediremos nada excesivo, capitán.";
		if (sti(pchar.money) >= iTemp)
		{
			link.l1 = "¡Estás contratado! Toma tus monedas. Ahora ve a mi barco, se llama '" + pchar.ship.name + " , justo en el puerto. El contramaestre os asignará todas las hamacas en los camarotes de la tripulación y se encargará de vuestros desórdenes.";
			link.l1.go = "crew_3";
		}
		link.l2 = "Lamentablemente, no puedo permitirme pagar por todos ustedes. Deberían buscarse otro capitán.";
		link.l2.go = "exit";
		break;

	case "crew_3":
		iTemp = sti(npchar.quest.crew.money) * sti(npchar.quest.crew.qty);
		AddMoneyToCharacter(pchar, -iTemp);
		dialog.text = "¡A la orden, capitán! Reuniré a los muchachos y partiremos de inmediato.";
		link.l1 = "Date prisa, zarpamos en cualquier momento.";
		link.l1.go = "crew_4";
		break;

	case "crew_4":
		DialogExit();
		AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
		// увеличиваем опыт
		iTemp = makeint(sti(npchar.quest.crew.qty) * 50 / sti(pchar.ship.crew.quantity));
		switch (sti(npchar.quest.crew.type))
		{
		case 0:
			ChangeCrewExp(pchar, "Sailors", iTemp);
			break;
		case 1:
			ChangeCrewExp(pchar, "Cannoners", iTemp);
			break;
		case 2:
			ChangeCrewExp(pchar, "Soldiers", iTemp);
			break;
		}
		// увеличиваем мораль
		iTemp = makeint(sti(npchar.quest.crew.qty) / 10) + 1;
		AddCrewMorale(pchar, iTemp);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		npchar.lifeday = 0;
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Eh, enfunda tu espada, capitán. Ninguno de nosotros necesita problemas, ¿verdad?", "Eh, envaina tu espada, capitán. Ninguno de nosotros necesita problemas, ¿verdad?");
		link.l1 = LinkRandPhrase("Bien.", "Como desees.", "Como usted diga.");
		link.l1.go = "exit";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
