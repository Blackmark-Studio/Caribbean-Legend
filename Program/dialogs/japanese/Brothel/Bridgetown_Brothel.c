// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんなご質問でございますか、」 "+GetSexPhrase("若者","お嬢さん")+"?","「ご用件は何でしょうか」 "+GetSexPhrase("「イケメン」","「可愛い子」")+"？どうぞ、お聞きください。"),"「またご質問ですか？」","うふふ、もしよろしければ――ご質問をどうぞ…",""+GetSexPhrase("ふむ、ご自分の好みの美女を選んではいかが？あなたのこと、ちょっと怪しく思えてきましたわ……","ふふん、ご自分で美女をお選びになってはいかが？残念ながら、ここには男の子はいませんのよ、うふふ…")+"","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わりました、失礼します。","実は、やっぱりいいわ……"),"わたくし……失礼いたしました、今のところ質問はございませんわ。","おっしゃる通り、もう三度目ですわ。ごめんなさいませ。","「また今度にしましょう、マダム。」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "取引のためにマホガニーの積荷を買って、ブルーウェルドへ向かっているんだ。まだ道のりは長いし、 俺の部下も少なくて不安がっている……ここで水夫五十人を一晩休ませるには、いくらかかる？";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "五十人の船乗り――一万五千だ。";
			link.l1 = "大金だな……考えさせてくれ。";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
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
