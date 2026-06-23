// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir vor einer Weile eine Frage zu stellen...","Ich habe noch nie Menschen mit solcher Neugier in meiner Werft oder sonst wo in dieser Stadt getroffen.","Was ist mit all den Fragen? Meine Aufgabe ist es, Schiffe zu bauen. Kümmern wir uns darum.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Hm, na ja...","Mach weiter...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ich bin auf dem Weg nach Blueweld mit einer Ladung Kaffee und würde gerne noch mehr Waren kaufen, aber hier ist das Problem: Auf dieser Brigantine, die ich von einem Kriegshund gekauft habe, ist eine abscheuliche Menge an schweren Kanonen, insgesamt 24. Ich bin nicht auf dem Weg in einen Krieg, wissen Sie. Ich möchte sie alle an Sie verkaufen und 12 Sechspfünder kaufen, mehr als genug, um einige Piraten zu erschrecken. Und den Rest des Platzes, den ich habe, werde ich mit Waren füllen.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Ja, verkaufen Sie sie ruhig. Ich habe immer genug Sechspfünder, aber ich habe immer ein Problem mit schweren Kanonen, da sie alle ständig kaufen und niemand sie verkaufen will, es sei denn, sie sind völlig kaputt, also werde ich Ihnen einen anständigen Preis dafür zahlen, wenn sie natürlich noch in funktionierendem Zustand sind.";
			link.l1 = "Wunderbar, großartig! Ich werde sofort Befehle erteilen.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
