// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺の勘違いだった。さらばだ。";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "役人殿、ここに『カンタヴロ』号の士官が拘留されていると聞いたが、本当か？";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "またドン・ロペについて伺いに来たぜ、役人。もう釈放命令は届いてるか？";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "「カンタブロ号」の士官か？ドン・ロペ・モントロか？ああ、ここで拘留している。で、あんたが何の用だ？";
			link.l1 = "彼に面会する許可をいただきたい。";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "失礼ですが、何の根拠で？";
			link.l1 = "ただの私的な用事だ。ヨーロッパにいた頃からあいつを知っていて、 投獄されたという知らせと町中に広まった噂に衝撃を受けたんだ。あいつと話がしたい。";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "ふむ……";
			link.l1 = "「おい、役人さん、あいつに面会させてくれたお礼を……“したい”んだが、どうだ？」";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "その必要はない。ドン・モントロに会うことを許可する。衛兵たちがお前を通すだろう。";
			link.l1 = "ありがとう！";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "確かに、俺の命令はドン・ロペ・モントロを直ちに司令官に引き渡すことだ。\nだが、あいつはしばらくの間、牢から出ることはなさそうだな。\nまだここにいるうちに、会いに行ってもいいぜ。";
			link.l1 = "ありがとうございます、役人殿、それが俺がここに来た理由だ。";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
