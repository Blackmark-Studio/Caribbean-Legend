// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたじゃねえか」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…","「また質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこに行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "フランスの植民地から聖職者たちが何かの使節団と一緒にここへ来たって聞いたぜ、何か取り決めでもするためか？ たぶん、あのマルティニークでの血なまぐさい虐殺の後、捕虜交換でもするんじゃねえか？";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "いや旦那、その話はずっと前に聖職者抜きで片付いたぜ。お前さん、ヤシの木の下で暮らしてるんじゃねえか？ 教皇インノケンティウス十世とマザラン枢機卿がついに合意したって話を知らねえとはな。ヨーロッパの戦争はさておき、 キリスト教徒はみんな団結して世界の果ての異教の闇と戦うべきだってよ。ああ、 カエル食いどもも俺たちのところに来たさ。だが何も決まっちゃいねえ―名誉あるお客人たちは総督の屋敷で警備付きでコーヒー飲みながら椅子を温めてる。もう一月近くもだ！人々は噂して、 散々話し合って、もう慣れちまった―見ろよ、フランスの修道院長が夕方に教会で祈祷をやってる。まるで見世物みてえだ、あはは！";
			link.l1 = "面白いじゃねえか！あのフランス野郎を見てみるか、ジョッキを眺めてるよりはよっぽどマシだぜ。";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
