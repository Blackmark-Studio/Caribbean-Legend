// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham, jakie jest pytanie?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Nie teraz. Złe miejsce i czas."),"Prawda, teraz nie mam nic do powiedzenia, przepraszam.","Zapytam, później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Panie Gubernatorze, mam dla was straszne wieści. Będę zwięzły: wasza żona chce was okraść. Próbowała mnie namówić, bym otworzył jeden z waszych szafek. Pomyślałem, że powinienem wam o tym powiedzieć.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" , Monsieur. Jestem tutaj na polecenie generała-gubernatora Chevaliera de Poincy. Moim zadaniem jest dostarczenie barona o imieniu Noel Forget na Tortugę, który przybył z macierzystego państwa z rozkazem przeprowadzenia inspekcji kolonii. Jego głównym celem jest założenie Francuskiej Kompanii Zachodnioindyjskiej. Pozwólcie, że go wam przedstawię... On sam wyjaśni wszystkie szczegóły.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Co-o-o? Znowu? Ta suka! Pożałuje tego, o, przysięgam! Kampacho sprawi, że będzie krzyczeć. Czemu wciąż tu jesteś? Wynoś się stąd do diabła!";
			link.l1 = " Myślałem...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Zawsze to samo! Weź to! To wszystko, co mam na stole! A teraz wynoś się!";
			link.l1 = "Dziękuję, Wasza Ekscelencjo. Sam się pożegnam.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Zawsze to samo! Weź to! To wszystko, co mam na stole!.. Chociaż, dobrze, nie wyglądasz jak reszta głupców i nieudaczników, którymi pełna jest moja wyspa. Weź trochę więcej... A teraz wynoś się!";
			link.l1 = "Dziękuję, Wasza Ekscelencjo. Wyjdę sam.";
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
			dialog.text = "Dobrze, kapitanie Charles de Maure. Baron zostanie odpowiednio potraktowany, a ja zrobię, co w mojej mocy, aby mu pomóc w jego zadaniu.";
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
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
