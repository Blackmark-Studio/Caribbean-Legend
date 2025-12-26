// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","聖職者にはやるべき仕事がたくさんあるんだ、君は俺の邪魔をしているぞ。 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は違うんだ、神父……"),"申し訳ないが、俺には何も言うことはねえ。","後で聞くぜ。すまねえな、神父。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "Gravel1":
			dialog.text = "「どうした、息子よ？何か用か？」";
			link.l1 = "「お前を探していたんだ、Georges。」";
			link.l1.go = "Gravel2";
			DelLandQuestMark(npchar);
		break;
		
		case "Gravel2":
			dialog.text = "俺が？でも、なぜだ？";
			link.l1 = "ロングウェイとファン・メルデン旦那が再調査を頼んでるんだ。ロングウェイは……前回来た時の件で、ここに顔を出せねえんだよ。";
			link.l1.go = "Gravel3";
		break;
		
		case "Gravel3":
			AddQuestRecord("PZ", "23");
			dialog.text = "頼むから声を抑えてくれ、神に誓って！だが、わかった。できる限りやってみる。";
			link.l1 = "素晴らしいぞ、Georges。お前は俺たちの最も頼りになる仲間の一人だ。また後で会おう。";
			link.l1.go = "Exit";
			DelMapQuestMarkCity("Charles");
			
			pchar.questTemp.PZ_Etap5_Start = true;
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
