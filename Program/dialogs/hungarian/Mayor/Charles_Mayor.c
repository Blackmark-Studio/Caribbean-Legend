// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálod megkérdezni...", "Már harmadszorra próbálod újra megkérdezni...",
                          "Mikor lesz már vége?! Elfoglalt ember vagyok, a kolónia ügyein dolgozom, és te még mindig próbálsz kérdezni valamit!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Chevalier de Poincy-t akarom látni. A testvéreimrôl szól' adósság.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Aha, nos, tudok arról az adósságról... Van nálad a szükséges összeg?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Persze, hogy van. Mi más lehetne?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Nem, még nincs ennyi pénzem.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Akkor jöjjön vissza, ha lesz, és ne zavarja a lovagot.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Akkor jöjjön be a jobb oldali ajtón. A lovag úr fogadja önt.";
			link.l1 = "Köszönjük!";
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
