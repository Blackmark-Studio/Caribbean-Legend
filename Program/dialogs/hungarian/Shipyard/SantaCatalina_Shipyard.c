// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kíváncsi emberekkel még nem találkoztam sem a hajógyáramban, sem máshol ebben a városban.",
                          "Mi ez a sok kérdés? Az én munkám az, hogy hajókat építsek. Gondoskodjunk errôl.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Hm, nos...", "Folytasd csak...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "...méltó választás, uram. Szóval, megegyeztünk?";
			link.l1 = "Igen! Egészségünkre! Csomagolja be és küldje a mólóra. És siess, egy hölgy vár rám az utcán!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Ötvenezer ezüst mindenért, uram.";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "Mennyit mondott? Ötvenezer? Nos, számolja meg maga! És vigyen még ötezret borravalónak. Gyerünk, menjünk!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Nem, nem, lehet, hogy gazdag vagyok, hic! ...fickó, de ennyiért nem fogadom el. Nem, uram! Viszontlátásra, hajós.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Köszönöm, uram. Jó szolgálatot tegyen önnek!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Igen, tûnj el, gazdag fickó. Három órája zártunk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
