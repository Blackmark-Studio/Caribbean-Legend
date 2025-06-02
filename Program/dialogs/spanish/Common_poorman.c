#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag); // homo 25/06/06

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// --> калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000)
		{
			dialog.text = "Mire, señor, ¿no quiere comprar una pequeña cosa divertida? Es barato, solo unos pocos miles de pesos...";
			link.l1 = "¿Hmm. Probablemente robaste esta 'pequeña cosa', y ahora estás tratando de deshacerte de ella?";
			link.l1.go = "caleuche";
			break;
		}
		// <-- калеуче
		if (npchar.quest.meeting == "0")
		{
			dialog.text = LinkRandPhrase("Hola. Mi nombre es " + GetFullName(npchar) + ". No supongo que estés contento de conocerme, pero, quizás, al menos recordarás mi nombre...", "Saludos, " + GetAddress_Form(NPChar) + ". Mi nombre es " + GetFullName(npchar) + ".", "Mi nombre es " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Encantado de conocerte.");
			link.l1 = RandPhraseSimple("Saludos.", "Hola.");
			link.l1.go = "First time";
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
			{
				link.l2 = "Oye, escucha, ¿te gustaría ganar un par de miles de pesos en lugar de estas patéticas limosnas?";
				link.l2.go = "trial";
			}
			// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ese colgante con camafeo... ¿Dónde lo encontraste?";
					link.l2.go = "TBP_Kulon_1";
				}
			// <-- Тайна Бетси Прайс
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = NPCStringReactionRepeat("Mira cuán bajo he caído...", "Vivir de limosnas no es fácil...", "¡Daría todo para salir de esta pobreza!", "¿Tú otra vez?..", "block", 1, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat("Ya veo. Bueno, no es gran cosa.", "Por supuesto. Bueno, el hombre más grande de la historia fue el más pobre.", "Entonces deberías empezar a hacer algo, no estar sentado aquí todo el día.", "Ah-ha. ¿Ya te molesto?", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
			link.l2 = RandPhraseSimple("¿Qué necesitas?", "¿Qué quieres?");
			link.l2.go = "Whants";
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
			{
				DelLandQuestMark(npchar);
				link.l2 = "Oye, escucha, ¿te gustaría ganar un par de miles de pesos en lugar de estas patéticas limosnas?";
				link.l2.go = "trial";
			}
			// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ese colgante con camafeo... ¿Dónde lo encontraste?";
					link.l2.go = "TBP_Kulon_1";
				}
			// <-- Тайна Бетси Прайс
			link.l3 = LinkRandPhrase("¿Puedes contarme algo interesante?", "¿Qué hay de nuevo en el pueblo?", "Oh, me gustaría escuchar los últimos chismes...");
			link.l3.go = "rumours_poor";
		}
		NextDiag.TempNode = "First time";
		break;
	case "pester":
		dialog.text = RandPhraseSimple("¿No, por qué, ya molesto? No estoy particularmente ocupado, como puedes ver...", "Solo me hace sentir cansado. Aunque pobre, sigo siendo un hombre.");
		link.l1 = "Je, ya veo...";
		link.l1.go = "exit";
		break;
	// выходы
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	// милостыня
	case "Whants":
		if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
		{
			dialog.text = PCharRepPhrase("Mmm, " + GetAddress_Form(NPChar) + ", la gente dice muchas cosas feas sobre ti. Pero sigo creyendo en las personas, incluso en las como tú. Por favor, dame limosna para pan y agua, ten piedad de mí.", "Te lo ruego, " + GetAddress_Form(NPChar) + "¡Por favor, no te alejes de un pobre hombre, da limosna para una comida...");
			link.l1 = RandPhraseSimple("No te daré nada.", "Lo lograrás sin dinero.");
			link.l1.go = "exit";
			Link.l2 = "Está bien, ¿y cuánto necesitas exactamente?";
			Link.l2.go = "Whants_1";
		}
		else
		{
			dialog.text = PCharRepPhrase("¿De ti? Nada.", "No necesito nada, " + GetAddress_Form(NPChar) + ", gracias.");
			link.l1 = RandPhraseSimple("Mmm, está bien.", "Aparentemente, tu vida no es tan mala, compañero.");
			link.l1.go = "exit";
		}
		break;
	case "Whants_1":
		dialog.text = "No rechazaría ni un cobre insignificante, " + GetAddress_Form(NPChar) + ". Tanto como tu bolsa y tu misericordia puedan dar...";
		Link.l1.edit = 2;
		link.l1 = "";
		link.l1.go = "Whants_2";
		break;
	case "Whants_2":
		SaveCurrentNpcQuestDateParam(npchar, "wants_date");
		int iTemp = sti(dialogEditStrings[2]);
		if (iTemp <= 0 || sti(pchar.money) < iTemp)
		{
			dialog.text = "Burlarse de los débiles y cansados es un pecado...";
			link.l1 = "¡Ja-ja-ja! ¿Pensaste por un momento que te daría dinero, mendigo demente?!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			break;
		}
		if (iTemp > 0 && iTemp <= 100)
		{
			dialog.text = "Gracias por " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Ahora puedo comprar pan con ese dinero...";
			link.l1 = "Aquí, vagabundo, ve a fortalecerte un poco.";
			link.l1.go = "exit";
			pchar.money = sti(pchar.money) - iTemp;
			Achievment_SetStat(41, 1);
		}
		if (iTemp > 100 && iTemp <= 500)
		{
			dialog.text = "Gracias, " + GetAddress_Form(NPChar) + ". ¡Ahora puedo vivir una semana con ese dinero!";
			link.l1 = "Fue un placer ayudar.";
			link.l1.go = "exit";
			OfficersReaction("good");
			pchar.money = sti(pchar.money) - iTemp;
			Achievment_SetStat(41, 1);
		}
		if (iTemp > 500 && iTemp <= 1000)
		{
			dialog.text = "Gracias, " + GetAddress_Form(NPChar) + ". ¡Le contaré a todos sobre tu bondad!";
			link.l1 = "Esto realmente no es necesario.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", iTemp / 2000.0 + 0.5);
			pchar.money = sti(pchar.money) - iTemp;
			Achievment_SetStat(41, 1);
		}
		if (iTemp > 1000 && iTemp <= 5000)
		{
			dialog.text = "Gracias, respetado " + GetSexPhrase("señor", "dama") + " " + GetAddress_Form(NPChar) + ". Que el Señor te vigile...";
			link.l1 = "¡Sí, su protección ciertamente no haría daño!";
			link.l1.go = "exit";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp / 10000.0 + 0.5);
			pchar.money = sti(pchar.money) - iTemp;
			Achievment_SetStat(41, 1);
		}
		if (iTemp > 5000 && iTemp <= 10000)
		{
			dialog.text = "Gracias, " + GetSexPhrase("muy estimado señor", "dama muy estimada") + " " + GetAddress_Form(NPChar) + ". ¡Te deseo todo lo mejor!";
			link.l1 = "Gracias, compañero.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", iTemp / 5000.0);
			AddCharacterExpToSkill(pchar, "Fortune", iTemp / 5000.0);
			pchar.money = sti(pchar.money) - iTemp;
			Achievment_SetStat(41, 1);
		}
		if (iTemp > 10000 && iTemp < 25000)
		{
			dialog.text = "Escucha, " + GetAddress_Form(NPChar) + ", ¿estás loco o qué? Me estás dando " + FindRussianMoneyString(iTemp) + "¡No puedo aceptar tal dinero, seguro que hay trampa... Déjame en paz!";
			link.l1 = "Bueno, como desees...";
			link.l1.go = "exit";
		}
		if (iTemp == 25000)
		{
			dialog.text = "Veinticinco mil aceptados ... ¡Este dinero será suficiente para Lelya y para mí durante todo un año!";
			link.l1 = "Vive este año primero...";
			link.l1.go = "exit";
		}
		if (iTemp > 25000)
		{
			dialog.text = "Escucha, " + GetAddress_Form(NPChar) + ", ¿estás loco o qué? Me estás dando " + FindRussianMoneyString(iTemp) + "¡No puedo aceptar tal dinero, seguramente debe haber un truco... Déjame en paz!";
			link.l1 = "Bueno, como desees...";
			link.l1.go = "exit";
		}
		break;

	case "trial":
		DelLandQuestMark(npchar);
		dialog.text = "¡Una pregunta tonta, señor! ¡Por supuesto que lo haría! Pero... ¿qué tendré que hacer? Seguramente no me vas a dar ese dinero solo por mi hermosa sonrisa.";
		link.l1 = "Por supuesto que no. Escucha ahora. Estoy actuando en nombre del propio gobernador. Su Gracia sospecha que alguien en el astillero está saboteando deliberadamente el lanzamiento del 'Alacantara', su galeón. Y sus sospechas se han fortalecido después de que recientemente se capturó a un espía francés...";
		link.l1.go = "trial_1";
		break;

	case "trial_1":
		dialog.text = "";
		link.l1 = "Su Gracia ya escuchó las excusas del maestro carpintero de ribera, pero no está seguro de que estuviera diciendo la verdad. Necesitamos averiguar quién está saboteando el trabajo y por qué. Ve a los muelles, echa un vistazo y pregunta a los trabajadores, ¿por qué diablos 'Alacantara' aún no está listo para zarpar?";
		link.l1.go = "trial_2";
		break;

	case "trial_2":
		dialog.text = "";
		link.l1 = "Nadie te sospechará, incluso podrías hacerte con un montón de tabaco. En cuanto a mí, nadie me dirá nada. Todos sabrán para quién trabajo. Si logras aprender algo valioso, recibirás tres mil pesos. Suficiente para abandonar tu 'trabajo' al menos por un mes.";
		link.l1.go = "trial_3";
		break;

	case "trial_3":
		dialog.text = "¿Tres mil pesos? Pero, estimado señor...";
		link.l1 = "¿Estás regateando conmigo o qué? Ah, y si descubres quién está detrás de todo este estancamiento, obtendrás otros dos mil. ¿Trato?";
		link.l1.go = "trial_4";
		break;

	case "trial_4":
		dialog.text = "Está bien, señor. No debería ser demasiado difícil: muchos de mis viejos amigos están trabajando en los muelles estos días. Oye, yo también fui marinero hace mucho tiempo, como hace diez años...";
		link.l1 = "Podrás contarme tu historia de vida más tarde. Encuéntrame en el muelle por la noche después de las once. Ahora vete.";
		link.l1.go = "trial_5";
		break;

	case "trial_5":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
		pchar.questTemp.Trial = "spy_poorman";
		pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
		pchar.quest.trial_spy_poorman.win_condition.l1.date.hour = 22.00;
		pchar.quest.trial_spy_poorman.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.trial_spy_poorman.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
		pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
		pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour = 6.00;
		pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
		// SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
		AddQuestRecord("Trial", "15");
		break;

	case "trial_6":
		dialog.text = "Buenas noches, señor...";
		link.l1 = "¿Y bien? ¿Descubriste algo?";
		link.l1.go = "trial_7";
		DelLandQuestMark(npchar);
		break;

	case "trial_7":
		dialog.text = "Lo hice, señor, lo hice. No estoy seguro de cómo coincide todo con lo que me dijiste... ¿Has traído el dinero? Cinco mil pesos.";
		if (sti(pchar.money) >= 5000)
		{
			link.l1 = "No te preocupes. Aquí está tu dinero. Ahora escúpelo.";
			link.l1.go = "trial_8";
		}
		else
		{
			link.l1 = "Primero la información, y luego el dinero. ¡Vamos, no me hagas perder el tiempo!";
			link.l1.go = "trial_fail";
		}
		break;

	case "trial_fail":
		dialog.text = "¡Estás intentando engañarme, señor! Si no vas a pagar, ve y pregunta a alguien más tú mismo. ¡Y ni siquiera pienses en sacar tu espada o llamaré a los guardias!";
		link.l1 = "...";
		link.l1.go = "trial_fail_1";
		break;

	case "trial_fail_1":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		pchar.questTemp.Trial = "spy_fail";
		AddQuestRecord("Trial", "16");
		sld = characterFromId("Florian");
		sld.DeckDialogNode = "florian_failspy_5";
		break;

	case "trial_8":
		AddMoneyToCharacter(pchar, -5000);
		dialog.text = "Entonces así va la cosa: 'Alcantara' ha estado listo para zarpar durante mucho tiempo, pero no se cargó intencionalmente, y por orden del propio gobernador. Bueno, eso es lo que me dijeron. Y los carpinteros ahora están haciendo todo tipo de trabajos menores diferentes, que no afectan la salida del barco.\nTodos están esperando la llegada de alguna corteza de Cartagena. Resulta que 'Alcantara' tiene, en opinión de su capitán, un stock insuficiente de pólvora. Entonces, el barco se ha quedado aquí y ha estado esperando durante días enteros hasta que 'Puebla' traiga la pólvora.\nPero todos piensan que toda esta espera es solo una pérdida de tiempo, así que si 'Puebla' no llega en tres días, 'Alcantara' levantará el ancla sin la pólvora...";
		link.l1 = "¿Es eso verdad? ¿Y quién te lo dijo? ¿Nombre?";
		link.l1.go = "trial_9";
		break;

	case "trial_9":
		dialog.text = "Uno de los marineros del 'Alacantara', Felipe Dabinho... Pero eso en realidad no es ningún secreto, y Su Gracia el gobernador mismo lo había ordenado...";
		link.l1 = "Ya veo. Eso es lo que esperaba. Espías franceses están en la ciudad, ¡pero estos idiotas están parloteando como chismosas, es increíble! Cualquier recién llegado puede averiguar lo que quiera sobre los planes de Su Gracia. ¡Oh, ese Felipe Dabinho está en serios problemas ahora! ¡Y el contramaestre del 'Alacantara' también! ¡Es su culpa que su tripulación no sepa nada sobre disciplina!";
		link.l1.go = "trial_10";
		QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
		QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
		QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
		QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
		QuestPointerToLoc("shore47", "reload", "boat");
		break;

	case "trial_10":
		dialog.text = "¡Oh!... Entonces, ¿lo sabías desde el principio? Pero por qué... ¡No es mi culpa! ¡Me dijiste que hiciera eso!";
		link.l1 = "No fue tu culpa, no deberías preocuparte por ello, nadie te va a castigar. Ahora sabemos que la tripulación del 'Alacantara' puede soltar cualquier información a un enemigo, incluso lo que se supone que debe mantenerse en secreto. Está bien, puedes irte ahora. Gracias por tu ayuda. Ve a gastar tu dinero.";
		link.l1.go = "trial_11";
		// belamour legendary edition -->
		link.l2 = "Adiós. (Mátalo)";
		link.l2.go = "trial_11a";
		break;

	case "trial_11a":
		DialogExit();
		AddMoneyToCharacter(npchar, 5000);
		npchar.SaveItemsForDead = true;
		LAi_SetActorType(pchar);
		// если не надет пистоль или мушкет, то выдадим строевой
		if (!CheckAttribute(pchar, "equip." + GUN_ITEM_TYPE) || !CheckAttribute(pchar, "equip." + MUSKET_ITEM_TYPE))
		{
			GiveItem2Character(pchar, "pistol1");
			EquipCharacterbyItem(pchar, "pistol1");
		}
		LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0);
		break;

	case "trial_11":
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		AddCharacterExpToSkill(pchar, "Sneak", 50);
		// <-- legendary edition
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		pchar.questTemp.Trial = "spy_win";
		AddQuestRecord("Trial", "17");
		sld = characterFromId("Florian");
		sld.DeckDialogNode = "florian_12";
		AddLandQuestMark(sld, "questmarkmain");
		break;

	// --> калеуче
	case "Caleuche":
		dialog.text = "Perdóneme, buen señor... Lo gané en un juego de dados contra un desconocido, pensé que era un amuleto curativo encantado, pero me equivoqué... No cura enfermedades, y los comerciantes del mercado no están interesados en él. Y aquí estás tú, un marinero, capitán, un hombre letrado. Míralo, y puede que lo encuentres útil.\nPara ti, este par de miles es una pequeña suma, pero para mí es un pedazo de pan y un sorbo de ron durante un mes. Mira, señor...";
		link.l1 = "Bien, muestra...";
		link.l1.go = "Caleuche_1";
		break;

	case "Caleuche_1":
		Log_Info("Has conseguido un amuleto extraño");
		PlaySound("interface\important_item.wav");
		dialog.text = "Aquí...";
		link.l1 = "Así así... Cosa interesante, estoy de acuerdo. Estoy seguro de que fue robado de los asentamientos indios. Bien, lo tomaré. Aquí está tu dinero.";
		link.l1.go = "Caleuche_2";
		break;

	case "Caleuche_2":
		AddMoneyToCharacter(pchar, -2000);
		dialog.text = "¡Gracias, señor! ¡Espero que esta cosa te traiga suerte! ¡Que el Señor te proteja!";
		link.l1 = "Buena suerte, compañero. No gastes todo el dinero de una vez en la taberna.";
		link.l1.go = "Caleuche_3";
		break;

	case "Caleuche_3":
		DialogExit();
		GiveItem2Character(pchar, "kaleuche_amulet1");
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", ¿qué le importa a usted una vieja baratija?";
			link.l1 = "Si ahora mismo te doy una patada en tu estúpida cabeza, entenderás por qué me importa.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Ese colgante pertenecía a Betsy Price. ¿Dónde lo encontraste?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Estaba en un macizo de flores junto a la casa con el farol, "+GetAddress_Form(NPChar)+". Aplastado en el barro por una bota masculina. Pero nadie vive en esa casa desde hace tiempo, así que supuse que no tenía dueño...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Estaba en un macizo de flores junto a la casa con el farol, "+GetAddress_Form(NPChar)+". Aplastado en el barro por una bota masculina. Pero nadie vive en esa casa desde hace tiempo, así que supuse que no tenía dueño...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
