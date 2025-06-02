// пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "prepare_convoy_quest":
		if (isBadReputation(pchar, 40))
		{
			dialog.text = RandPhraseSimple("¡Ahhh, demonios! ¡Sé quién eres! ¡Solo un completo idiota subiría a tu barco como pasajero! ¡Adiós!", "¡Oh, sé quién eres! Nunca pondré un pie a bordo de tu barco. No soy un tonto...");
			link.l1 = RandPhraseSimple("¡Já, qué cobarde!", "¡La gente se ha vuelto tan cobarde estos días!");
			link.l1.go = "convoy_refused";
		}
		else
		{
			dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "¡ Yo soy " + GetFullName(NPChar) + ". ¿Oí que estás llevando pasajeros?";
			link.l1 = "Quizás. Depende de mi beneficio.";
			link.l1.go = "prepare_convoy_quest_3";
		}
		break;

	case "prepare_convoy_quest_3":
		LookShipPassenger();
		GenerateConvoyPassengerQuest(npchar);
		dialog.text = "Necesito ser llevado a la taberna de " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", eso en " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ", en el plazo de " + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", y por eso te pagaré " + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + ". ¿Estás de acuerdo?";
		link.l1 = "Sí, lo hago.";
		link.l1.go = "convoy_agreeded";
		link.l2 = "No creo que sea una propuesta interesante.";
		link.l2.go = "convoy_refused";
		break;

	case "convoy_refused":
		chrDisableReloadToLocation = false;
		sTemp = npchar.id + "_TimeOver";
		pchar.quest.(sTemp).over = "yes";
		sTemp = npchar.id + "_dead";
		pchar.quest.(sTemp).over = "yes";
		DeleteAttribute(npchar, "GenQuest.GetPassenger");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "convoy_agreeded":
		sTitle = npchar.index + "convoy_passenger";
		AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
		sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", que está en " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
		AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sCity", sTemp);
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
		AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
		// по городу вернём его таверну
		sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
		sTemp = npchar.id + "_complited";
		pchar.quest.(sTemp).win_condition.l1 = "location";
		pchar.quest.(sTemp).win_condition.l1.location = sTavern;
		pchar.quest.(sTemp).win_condition = "AllPassangersComplited";
		pchar.quest.(sTemp).Idx = npchar.index;
		if (rand(2) == 1)
			TraderHunterOnMap();
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
		Diag.CurrentNode = "convoy_DeskTalk";
		DialogExit();
		break;

	case "complete_convoy_quest":
		dialog.text = "Gracias. Has cumplido con tus obligaciones. Estoy en mi punto de destino, aquí está tu recompensa. Aquí tienes.";
		Link.l1 = "Gracias.";
		link.l1.go = "complete_convoy_quest_1";
		break;

	case "complete_convoy_quest_1":
		// слухи
		AddSimpleRumour(LinkRandPhrase("Una persona llamada " + GetFullName(npchar) + " dice que el capitán " + GetMainCharacterNameDat() + " es fiable, ya que " + GetSexPhrase("él", "ella") + " lo llevó fácilmente a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".",
									   "Un pasajero llamado " + GetFullName(npchar) + " dice que el capitán " + GetMainCharacterNameDat() + " se puede confiar. " + GetSexPhrase("Lo llevó", "Ella lo llevó") + " a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " con total seguridad.",
									   "He oído que usted es un capitán que cumple la palabra dada a los pasajeros. El Buhonero de nombre " + GetFullName(npchar) + " te tiene en alta estima."),
						sti(npchar.nation), 40, 1);
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); // извлекаем из структуры недовольных
		//--> смотрим Deck
		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
		if (GetAttributesNum(arAll) == 0)
			pchar.quest.ConvoyMapPassenger.over = "yes";
		//<-- смотрим Deck
		AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		ChangeCharacterComplexReputation(pchar, "fame", 1);
		RemovePassenger(PChar, npchar);
		OfficersReaction("good");
		AddCharacterExpToSkill(pchar, "Sailing", 80);
		AddCharacterExpToSkill(pchar, "Leadership", 20);
		sTitle = npchar.index + "convoy_passenger";
		AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");
		CloseQuestHeader(sTitle);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "convoy_DeskTalk":
		dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "Capitán, el tiempo se ha agotado. ¿Cuándo, maldita sea, por fin llegaré a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", RandSwear() + "Capitán, ¿cuánto tiempo más vas a vagar por Dios sabe dónde?! ¿Cuándo vamos a llegar a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", RandSwear() + "Escucha, capitán, necesito llegar a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", ¡y quiero obtener una respuesta clara y simple de cuándo sucederá esto!"), RandPhraseSimple("Capitán, una vez más tengo que plantear una pregunta sobre tus obligaciones. ¿Cuándo llegaremos a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", "Capitán, la segunda vez que tengo que plantear la pregunta sobre mi viaje. ¿Cuándo, finalmente, veremos la costa de " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?"), RandPhraseSimple(RandSwear() + "Capitán, te lo pregunto por tercera vez, ¿cuándo llegaremos a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", "¡Capitán, hemos perdido un diablo de tiempo! ¿Cuándo me llevarás a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"), "¡Escucha Capitán, esto es realmente demasiado!", "block", 0, npchar, Dialog.CurrentNode);
		if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
		{
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Por favor, lo siento, tenía tantos asuntos que hacer... En siete días estarás donde necesitas estar, sin duda.", "Lo siento, " + GetAddress_Form(NPChar) + ", realmente no podría haber cumplido mis obligaciones contigo. Pero no te preocupes, llegaremos en una semana."), RandPhraseSimple("Debo disculparme contigo una vez más. Llegaremos a tu destino en una semana.", "Una vez más, lo siento. Llegaremos a su destino en una semana."), RandPhraseSimple("Y una vez más debo pedirte disculpas... Llegaremos a tu destino en una semana.", "Y una vez más, lo siento. Llegaremos a su destino en una semana, lo prometo."), "Lo entiendo, " + GetAddress_Form(NPChar) + ", pero por favor, ten paciencia... ¡En siete días como máximo te llevaré a tu destino!", npchar, Dialog.CurrentNode);
			link.l1.go = "convoy_DeskTalk_1";
		}
		link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Oh... un pasajero... Te había olvidado... Creo que encontrarás más cómodo en la bodega, donde ya no me molestarás.", "¡Vaya-vaya, no puedo creer mis propios ojos! ¡Un desconocido está en mi barco! Bien, entonces cállate y ve a mi bodega, ¡ahora!"), "¿Por segunda vez? Oh, ciertamente... Pero sabes, quizás, te enviaré a la bodega para una 'excursión'.", "¿Por tercera vez? Eso es muy malo, je-je... Bueno, compañero, bienvenido a mi bodega. No deberías haber estado paseando por la cubierta de mi barco y molestándome.", "¡Ah, ya veo, ese es el grado más alto de irritación! Bueno, basta de esta farsa. Bienvenido a la bodega. " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
		link.l2.go = "convoy_Prison_1";
		pchar.quest.Munity = "Deads"; // дверцы откроем
		break;

	case "convoy_DeskTalk_1":
		dialog.text = LinkRandPhrase("Está bien, pero reduciré tu pago por el retraso.", "Está bien, trataré de creerte... ¡Pero ten en cuenta que voy a recortar tu tarifa!", "Bueno, de todos modos, no tengo a dónde ir, pero ten en cuenta que voy a reducir tu pago....");
		Link.l1 = LinkRandPhrase("Está bien.", "Bien, entonces...", "Está bien, como usted diga.");
		link.l1.go = "convoy_DeskTalk_2";
		break;

	case "convoy_DeskTalk_2":
		dialog.text = RandPhraseSimple("Me gustaría creer que esta vez vas a cumplir tus obligaciones.", "Espero que esta sea nuestra última conversación sobre este desagradable tema.");
		Link.l1 = "Por supuesto.";
		link.l1.go = "convoy_DeskTalk_exit";
		break;

	case "convoy_DeskTalk_exit":
		DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); // извлекаем из структуры недовольных
		sTemp = npchar.id + "_TimeOver";
		SetTimerCondition(sTemp, 0, 0, 7, false);
		pchar.quest.(sTemp).win_condition = "AllPassangersTimeOver";
		pchar.quest.(sTemp).Idx = npchar.index;
		npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);
		sTitle = npchar.index + "convoy_passenger";
		AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
		AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
		Diag.CurrentNode = "convoy_DeskTalk";
		DialogExit();
		break;

	case "convoy_Prison_1":
		dialog.text = RandSwear() + "¿Qué bodega? ¡No entiendo!";
		if (GetPrisonerQty() < PRISONER_MAX)
		{
			Link.l1 = "¿Y qué más hay que entender? ¡Desde ahora eres mi prisionero! ¡Ve a la maldita bodega, muévete!";
			link.l1.go = "convoy_Prison_2";
		}
		Link.l2 = "Solo una broma... En siete días llegaremos a tu ciudad.";
		link.l2.go = "convoy_DeskTalk_1";
		break;

	case "convoy_Prison_2":
		dialog.text = RandSwear() + "Vas a pagar por esto, " + GetSexPhrase("escoria", "apestoso") + "¡!";
		Link.l1 = "¡Todos dicen eso, pero al final todos pagan!";
		link.l1.go = "convoy_Prison_3";
		break;

	case "convoy_Prison_3":
		AddSimpleRumour(LinkRandPhrase("Se ha informado de que un capitán llamado " + GetFullName(pchar) + " estaba obligado a entregar a un pasajero con el nombre de " + GetFullName(npchar) + ", pero no se mantuvo fiel a " + GetSexPhrase("su", "su") + " palabra. Además, " + GetSexPhrase("", "") + " encarceló a ese pobre tipo. Eso es lo que pasa cuando confías en gente extraña...",
									   "¡¿Qué le pasa a este mundo?! El capitán " + GetFullName(pchar) + " encarceló a un pobre tipo llamado " + GetFullName(npchar) + ", a pesar de ir como pasajero en su barco...",
									   "Capitán, la gente dice que usted es " + GetSexPhrase("un verdadero canalla", "una verdadera zorra") + ". Dicen que el pobre " + GetFullName(npchar) + " fue hecho prisionero en su barco. Y eso que prometiste entregarlo en " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Eso es muy, muy feo ..."),
						sti(npchar.nation), 40, 1);
		RemovePassenger(PChar, NPChar);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		OfficersReaction("bad");
		ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
		DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id);								  // извлекаем из структуры недовольных
		sTemp = npchar.id + "_complited";
		pchar.quest.(sTemp).over = "yes";
		sTemp = npchar.id + "_dead";
		pchar.quest.(sTemp).over = "yes";
		sTemp = npchar.id + "_TimeOver";
		pchar.quest.(sTemp).over = "yes";
		sTitle = npchar.index + "convoy_passenger";
		AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sTitle);
		AddCharacterExpToSkill(pchar, "COMMERCE", 25);
		SetCharToPrisoner(NPChar);
		DialogExit();
		break;
	}
}

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); // если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14)
		daysQty = 14;
	npchar.GenQuest.GetPassenger_Time = makeint(sti(daysQty) * (frand(1.3) + 0.7));
	iTradeMoney = (sti(daysQty) * 500 * sti(pchar.GenQuest.GetPassenger.Shipmod) + rand(100)) * sti(daysQty) / sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE))
		iTradeMoney = makeint(iTradeMoney * 1.3); // то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	// Log_Info(FindRussianDaysString(sti(daysQty)));
	// Log_Info(npchar.GenQuest.GetPassenger_Destination);
	// Log_Info(pchar.GenQuest.GetPassenger_City);

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx = npchar.index;

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition = "AllPassangersDead";
	pchar.quest.(sTemp).Idx = npchar.index;
}

void LookShipPassenger()
{
	switch (makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
	case 0:
		pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
	case 1:
		pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
	case 2:
		pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
	case 3:
		pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
	case 4:
		pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
	case 5:
		pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	case 6:
		pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}
