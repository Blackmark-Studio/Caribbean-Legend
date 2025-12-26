// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に何か質問しようとしただろう…","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","なんだよ、その質問攻めは？俺の仕事は船を造ることだ。さっさとそれを片付けようぜ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "俺は今、コーヒーを積んでブルーウェルドへ向かってるんだが、もっと商品を買いたいと思ってる。だが問題があってな、 このブリッグは戦争屋から買ったもんで、重砲がとんでもなく多いんだ、全部で24門もある。戦争に行くわけじゃねえんだぜ。全部あんたに売り払って、代わりに6ポンド砲を12門買いたい。海賊どもを脅かすにはそれで十分だろう。残りのスペースは商品で埋めるつもりだ。";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "ああ、売ってくれ。六ポンド砲はいつも十分にあるが、大砲となるといつも困ってるんだ。みんながすぐ買っていくし、 誰も売りたがらない。壊れきったもの以外はな。だから、もしまだ使える状態なら、ちゃんとした値段で買い取るぜ。";
			link.l1 = "おお、こりゃたまげた！すぐに指示を出すぜ。";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
