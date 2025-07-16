// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Stavamo proprio parlando di questo. Devi aver dimenticato...","È la terza volta che mi disturbi ora...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Dimmi, dove posso trovare la Signora Belinda de Ribero?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Nel palazzo del governatore, ovviamente. È una cugina di Don Fernando de Villegas. Puoi cercarla lì dopo mezzogiorno durante la sua siesta, di solito ha affari da sbrigare al mattino. È in un bel guaio ora, quindi tienilo a mente. Ma non le dispiacerà parlare con te. Donna Belinda è una brava donna.";
			link.l1 = "Grazie!";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Belinda = "seek";
			// ставим Белинду
			sld = GetCharacter(NPC_GenerateCharacter("GOT_Belinda", "Belinda", "woman", "towngirl", 3, SPAIN, -1, true, "quest"));
			SetFantomParamFromRank(sld, 3, true);
			sld.name = "Belinda";
			sld.lastname = "de Ribero";
			sld.dialog.FileName = "Quest\Sharlie\guardoftruth.c";
			sld.dialog.currentnode = "belinda";
			sld.greeting = "noble_female";
			LAi_SetLoginTime(sld, 13.0, 20.0);
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cumana_TownhallRoom", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
