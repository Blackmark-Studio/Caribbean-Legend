// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お話を伺いましょう、ご質問は何でしょうか？"),"二度目のご質問でございますね…","また三度目のご質問でございますね……","いつまで続くのですか！？私は植民地の業務で多忙なのです、まだ何かお尋ねになりたいのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを改めました……","今は駄目だ。場所も時も間違っている。"),"「確かに……しかし、今ではなく、後で……」","聞いてみましょう……しかし、少し後で……","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "私はマルティニークで利益の上がる取引をいたしましたので、これからブルーウェルドへ航海する予定でございます。\n貴殿の植民地でレッドウッドとコーヒーを購入したく存じます。\nさらに、私のブリッグでは希望するほどの貨物を積むことができませんので、 こちらの造船所でフリュート船を購入したいと考えております。\nこれらの件につきまして、ご助力いただけますでしょうか。";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "私の助力ですか？我々の商人は非常に誠実な人物ですので、あなたを騙そうとすることはないでしょう。 フルートの件については船長に相談なさい、きっと力になってくれます。それでも何か問題があれば、 私のところに来てください。私はこの植民地との交易関係を発展させることに関心があり、 あなたを全面的に支援いたします。\nそれから、今夜は宴を催します。ブリッジタウンの名士たちが皆出席しますので、船長もぜひお越しください。";
			link.l1 = "ご招待いただきありがとうございますが、あいにく多忙でございます。\nそれでは失礼いたします、ご協力に感謝いたします！";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
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
