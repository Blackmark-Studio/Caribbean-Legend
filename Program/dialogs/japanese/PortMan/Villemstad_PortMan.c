// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用件について何も話すことがないなら、俺に質問してくるんじゃねえ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "奴隷反乱の後に姿を消したバーク船について知りたいんだ。";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "トフ・ケラーという名の船長を探したいんだ。彼は「ライデン」というフリュート船の持ち主だ。 ウィレムスタッドによく来ると聞いたから、あんたなら手伝うのは難しくないだろう。";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "ふむ……なぜそんなことに興味があるんだ？黒人があんたの専門か？";
				link.l1 = "私は総督マティアス・ベックの命令でここに来た。逃亡した黒人たちがあの船を盗み、 持ち去ったと疑う十分な理由がある。だから、捜索にあたってあらゆる手段で私に協力してほしい。";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "なるほど。まあ、俺にはどうにもできねえ。バーク船『"+pchar.questTemp.Slavetrader.ShipName+"「朝にはいなくなっていて、誰も何も見ていませんでした。私は家で寝ていました。埠頭の見張りも姿を消し、 痕跡も残っていません。\n総督はまだ手がかりが残っているうちに追跡用のスループ船を出しましたが、結局何も得られずに戻ってきました。 黒人たちも『』も、何の手がかりもありませんでした。"+pchar.questTemp.Slavetrader.ShipName+"正直言ってな、スループ船はあいつらをあまりしっかり探さなかったんだ。みんなまだパニック状態で、 カフィールどもがジャングルからピッチフォークやマチェーテを手に白人の血を求めて飛び出してくるんじゃねえかって思 ってたからな。";
				link.l1 = "あまり役に立たなかったが、とにかく礼は言っておく。じゃあな。";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "トフ・ケラーか？ああ、知ってるぜ！あいつはよくトリニダード島のサンホセやクマナに航海してるんだ。 最近もトリニダードに行ったばかりだ。たぶん、今ならそこで会えるだろう。";
			link.l1 = "ありがとう！";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
