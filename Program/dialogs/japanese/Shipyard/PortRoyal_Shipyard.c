// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","どうされましたか？"),"少し前に俺に質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","なんだよ、その質問攻めは？俺の仕事は船を造ることだ。さっさと本題に入ろうぜ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "この造船所は船の航行速度を上げるのが得意だと聞いたぜ。だが、それにはとても貴重な絹の帆布が必要なんだ。\nこの話……詳しく聞いてみるか？";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "私はミス・マッカーサーから来たんだが、その件で…";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "船のオーバーホールを始めろ！";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "もう少しはっきり言ってくれ、若者よ。何があんたをここに連れてきたんだ？船を改良したいなら、 さっそく本題に入ろうじゃないか。";
			link.l1 = "完全ではありません。あなたが行う仕事には、店では簡単に手に入らない品が必要でしょう。そこで、 必要になるであろう同じ種類の資材をお届けしたいのです。";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "ほうほう……ふむ……この植民地では、こういった戦略物資の取り扱いは当局だけに許されていることを知っているか？ 自分の船を改良するために使う絹を持ち込むのは構わんが、売買は厳禁だ。俺から買うのも同じく禁止――そんなことをすれば重い罰金を食らうぞ。";
			link.l1 = "ここは店でもなけりゃ、税関でもねえんだが…";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "俺は絹の帆布をすべて直接取引先から仕入れているか、総督の特別な許可を得て少量だけ購入しているんだ。\n他に質問がなければ、仕事に戻らせてくれ。";
			link.l1 = "ふむ……よろしい。良い一日を、旦那。";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "ああ、わかってるよ！運がいいな、船長。船の全面改修の件かい？全部任せてくれ、 うちの造船所はプリマスの工廠にも負けてないぜ！";
			link.l1 = "これはタダじゃねえよな？";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "もちろんです、船長。クロムウェルであっても、こういったサービスが無料というわけにはいきません！ですが、 俺は約束は守ります。金だけをいただきます――密輸品を運ぶ必要はありません。";
			link.l1 = "なるほど。いくらだ？";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "旗艦の大きさによりますよ、船長。一等戦列艦なら五千ドゥブロンかかりますし、 五等艦ならたった千ドゥブロンで済みます。";
			link.l1 = "わかった、決めたらそっちに行くぜ。";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "素晴らしい、これで必要なものはすべて揃った。じゃあ、作業に取りかかるぜ。";
			link.l1 = "待っている。";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "…これで全部だな…品質は保証するぜ。";
			link.l1 = "ありがとう！ちょっと見てくるぜ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
