// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"È la seconda volta che stai cercando di chiedere...","È la terza volta che stai cercando di chiedere di nuovo...","Quando finirà?! Sono un uomo impegnato, lavoro sulle questioni della colonia e tu stai ancora cercando di chiedere qualcosa!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Posto e tempo sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Voglio vedere il Cavaliere de Poincy. Riguarda il debito di mio fratello.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Aha, bene, sono informato su quel debito... Hai la somma richiesta con te?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Certo che ho. Come potrebbe essere altrimenti?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "No, non ho ancora così tanti soldi.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Allora torna quando avrai e non disturbare il Cavaliere.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Passa dalla porta a destra allora. Il Cavaliere ti riceverà.";
			link.l1 = "Grazie!";
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
