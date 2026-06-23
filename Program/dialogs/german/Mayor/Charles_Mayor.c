// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was wollen Sie? Fragen Sie nur.","Ich höre Ihnen zu, was ist die Frage?"),"Es ist das zweite Mal, dass Sie versuchen zu fragen...","Es ist das dritte Mal, dass Sie wieder versuchen zu fragen...","Wann wird es endlich vorbei sein?! Ich bin ein beschäftigter Mann, der sich um die Angelegenheiten der Kolonie kümmert und Sie versuchen immer noch, etwas zu fragen!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Ich möchte Chevalier de Poincy sehen. Es geht um die Schulden meiner Brüder.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Aha, nun, ich bin über diese Schuld informiert... Haben Sie die erforderliche Summe bei sich?";
			if (int(pchar.money) >= 1000000)
			{
				link.l1 = "Sicher habe ich. Wie könnte es sonst sein?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Nein, ich habe noch nicht so viel Geld.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Dann komm zurück, wenn du es hast und belästige den Chevalier nicht.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Kommen Sie dann durch die Tür rechts. Chevalier wird Sie empfangen.";
			link.l1 = "Danke!";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
