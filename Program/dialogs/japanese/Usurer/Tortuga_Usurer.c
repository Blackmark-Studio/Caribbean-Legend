// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件をお伺いしましょうか？"),"つい最近もその質問を私にしようとしましたね……","ああ、どうせまた堂々巡りしてるんだろう？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","お察しの通りです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "こんにちは、船長。私どもと私の会社がどのようにお役に立てますでしょうか？";
			link.l1 = "トルトゥーガの名高い守備隊の年金基金に寄付をしたいのですが。";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "承知しました。最近はかなり人気ですね！いくらご負債が……いえ、ご寄付をご希望ですか？";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" ドブロン。ところで、ペソは受け取ってもらえますか？";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "もちろんですが、しかし少々割高になります。正確にご説明いたしましょう… "+pchar.questTemp.TonzagQuest.Bail+" ドゥブロンは "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" ペソ。";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "少し高いとおっしゃいますか？はい、必要な全額をご用意しました。";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "少し高いとおっしゃいますか？残念ながら、今その金額は手元にありません。 この件について融資を受けることは可能でしょうか？";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "素晴らしいですね。すぐにお取引相手にご連絡いたします！\nそれでは、船長。……そして、ご武運を。私どもはあなたのご活躍を長らく楽しみにしておりました。";
			link.l1 = "それでは。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "そのような機会はいつでもご用意しております、船長！例えば、 二十万ペソを半年後にご返済いただくというのはいかがでしょうか？";
			link.l1 = "仕方ないな。どこに署名すればいいんだ？";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
