// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was willst du? Frag nur.","Ich höre Ihnen zu, was ist die Frage?"),"Es ist das zweite Mal, dass Sie versuchen zu fragen...","Es ist das dritte Mal, dass Sie wieder versuchen zu fragen...","Wann wird das endlich ein Ende haben?! Ich bin ein beschäftigter Mann, der sich um die Belange der Kolonie kümmert und du versuchst immer noch, etwas zu fragen!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ich hatte einen profitablen Handel auf Martinique und plane nun, nach Blueweld zu segeln. Ich möchte in Ihrer Kolonie Rotholz und Kaffee kaufen. Außerdem kann meine Brigg nicht so viel Ladung aufnehmen, wie ich bereit bin zu kaufen, also muss ich hier in Ihrer Werft eine Flöte kaufen. Könnte ich Ihre Unterstützung in diesen Angelegenheiten haben?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Meine Hilfe? Unser Händler ist ein sehr ehrlicher Mann, also bezweifle ich, dass er versuchen wird, Sie zu täuschen. Sprechen Sie mit dem Schiffskapitän über die Flöte, er wird Ihnen bei dieser Angelegenheit helfen. Und wenn Sie trotzdem Ärger bekommen, dann sollten Sie mich aufsuchen. Ich bin daran interessiert, die Handelsverbindungen mit unserer Kolonie auszubauen und ich werde Ihnen all meine Unterstützung zeigen.\nAußerdem organisiere ich heute Abend ein Bankett, alle hellsten Köpfe von Bridgetown werden daran teilnehmen. Sie sollten auch kommen, Kapitän.";
			link.l1 = "Danke für Ihre Einladung, aber leider bin ich zu beschäftigt. Auf Wiedersehen und danke für Ihre Vermittlung!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
