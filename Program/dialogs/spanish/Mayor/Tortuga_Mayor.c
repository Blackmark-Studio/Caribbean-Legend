// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Esta es la segunda vez que intentas preguntar...", "Esta es la tercera vez que intentas preguntar...", "¿Cuándo va a terminar esto? ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y todavía me estás molestando!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple(" He cambiado de opinión, lo siento.", "Ahora no. Lugar y momento equivocados."), "Es cierto, no tengo nada que decir ahora, lo siento.", "Preguntaré, más tarde.", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
		if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
		{
			link.l1 = "Monsieur Gobernador, tengo terribles noticias para usted. Seré breve: su esposa quiere robarle. Ha intentado persuadirme para que abra uno de sus cofres del gabinete. Pensé que debería saberlo.";
			link.l1.go = "FMQT";
		}
		// Jason НСО
		if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
		{
			link.l1 = TimeGreeting() + ", Monsieur. Estoy aquí por orden del Gobernador General Chevalier de Poincy. Mi tarea es llevar a un barón llamado Noel Forget a Tortuga, quien llegó del estado padre con la orden de inspeccionar las colonias. Su propósito principal es establecer una Compañía de Comercio de las Antillas Francesas. Permítame presentárselo... Él explicará todos los detalles personalmente.";
			link.l1.go = "patria_tortuga";
		}
		break;

	case "FMQT":
		dialog.text = "¿Qu-é-é? ¿Otra vez? ¡Esa perra! ¡Lo lamentará, oh lo juro! Kampacho la hará gritar. ¿Por qué sigues aquí? ¡Lárgate de aquí!";
		link.l1 = "Pensé...";
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25)
			link.l1.go = "FMQT_2";
		else
			link.l1.go = "FMQT_1";
		break;

	case "FMQT_1":
		Notification_Skill(false, 26, SKILL_LEADERSHIP);
		AddMoneyToCharacter(pchar, 1000);
		dialog.text = "¡Siempre lo mismo! ¡Aquí, toma esto! ¡Es todo lo que tengo en la mesa! ¡Ahora, vete!";
		link.l1 = "Gracias, su Excelencia. Me retiraré yo mismo.";
		link.l1.go = "FMQT_3";
		break;

	case "FMQT_2":
		AddMoneyToCharacter(pchar, 1000);
		GiveItem2Character(pchar, "pistol6");
		GiveItem2Character(pchar, "purse1");
		Log_Info("Has recibido una pistola de doble cañón y un monedero con doblones");
		dialog.text = "¡Siempre lo mismo! ¡Aquí, toma esto! ¡Es todo lo que tengo en la mesa!.. Aunque, bueno, no te ves como el resto de los idiotas y perdedores con los que está llena mi isla. Toma un poco más... ¡Ahora lárgate!";
		link.l1 = "Gracias, su Excelencia. Me retiraré yo mismo.";
		link.l1.go = "FMQT_3";
		break;

	case "FMQT_3":
		DialogExit();
		pchar.quest.FMQT_late1.over = "yes";
		ChangeCharacterNationReputation(pchar, FRANCE, 5);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		pchar.questTemp.FMQT = "end";
		FMQ_Count();
		AddQuestRecord("FMQ_Tortuga", "7");
		CloseQuestHeader("FMQ_Tortuga");
		FMQT_ClearChest();
		break;

	// Jason НСО
	case "patria_tortuga":
		dialog.text = "Bien, capitán Charles de Maure. El barón recibirá el trato adecuado y haré lo que pueda para ayudarlo con su tarea.";
		link.l1 = "";
		link.l1.go = "patria_tortuga_1";
		break;

	case "patria_tortuga_1":
		DialogExit();
		sld = characterFromId("Noel");
		sld.dialog.currentnode = "noel_5";
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
