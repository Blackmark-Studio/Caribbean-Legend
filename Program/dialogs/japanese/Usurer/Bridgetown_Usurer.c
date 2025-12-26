// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件は何でしょうか？"),"つい最近もその質問を私にしようとしましたね……","ああ、さては……また堂々巡りしてるんじゃないか？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ご名答です、申し訳ありません……","承知いたしました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "私はワインを積んでブルーウェルドへ向かっています。\nしかし、ある船長からブルーウェルドでコーヒーの需要が高まっていると聞きましたが、その理由は分かりません。\nワインを売って代わりにコーヒーを買おうかと考えていますが、船倉を満杯にするほどの資金が足りません。\n利子付きでお金を貸していただけませんか？";
                link.l1.go = "UsurerDone";
            }
		break;
		
		case "UsurerDone":
			dialog.text = "信用ある商人への貸付なら問題ありません。いくらご入用ですか？ご相談いたしましょう。";
			link.l1 = "承知しました。まずは貨物室に積み込み、残りの空き容量を計算いたします。その上で不足分を確認し、 必要があれば再度ご相談に参ります。";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-13");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
