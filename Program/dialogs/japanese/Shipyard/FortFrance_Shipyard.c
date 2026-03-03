// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に何か質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだ。さあ、それを片付けようぜ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "「お前の部下が、あんたが俺に会いたがってるって言ってたぜ。さあ、話を聞こうじゃねえか。」";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "仕事は終わった。 "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" 樽入りの樹脂が俺の貨物倉にある。";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "「ああ、ああ、船長」 "+GetFullName(pchar)+"。あなたの船が我々の港に入るのを見て、すぐに召使いをあなたのもとへ向かわせた。\nでは早速本題に入ろう。あなたは新参者だが、すでに熟練の船乗りとなり、運も味方していると聞いている。だからこそ、 あなたに商談を持ちかけたいのだ。";
			link.l1 = "面白いな！続けて、話してくれ。";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "トリニダード島でスペイン人が生産している特別な樹脂のことを聞いたことがあるか？ これは戦略的価値の高い希少な資源で、船体の強化に使われるんだ。樽一つでかなりの額になるし、 スペインはこの樹脂をすべて自国海軍のために回している。どの植民地当局もこの品の取引を厳しく管理していて、 要するに完全な密輸品ってわけだ。\nこの樹脂が特別な注文で必要なんだ。当然、うちの倉庫にもないし、地元の軍の倉庫も同じこと——いや、もしかしたら売る気がなかっただけかもしれないが、それはどうでもいい。大事なのは、 俺がその樹脂を必要としていて、手に入れるあてがあるってことだ。あとは、拿捕に慣れている船長さえいればいい。";
			link.l1 = "あんたの言いたいことが、だんだん分かってきた気がするぜ…";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "素晴らしい。さて、聞いてくれ、トリニダードの近く、正確にはサンホセの港で小さな交易船団が目撃されたんだ。 船の一隻が上質な樹脂を積んでいてな、その樹脂こそ俺がどうしても欲しいものなんだ。 もしお前が我が国の敵を略奪する気があるなら、さらに詳しく話してやるぜ。どうする？\n";
			link.l1 = "あんたの提案、気に入ったぜ。やってみる用意はできてる。";
			link.l1.go = "FMQM_3";
			link.l2 = "遠慮しておくぜ、旦那。今は俺の船も乗組員も万全じゃねえんだ。";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "わかった、好きにするのはあんたの権利だ。時間を取らせて悪かったな、船長。";
			link.l1 = "さようなら。";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "では聞け。護送船団は三隻で構成されている。樹脂は他の積荷と一緒に\n "+sTemp+" 『ベンセチョ』と呼ばれている。これが主な標的だ。前にも言ったが、スペイン人たちはサンホセ＝ トリニダードからサンファン＝プエルトリコへ航海している。やつらは明日出航するから、 どこで襲うかはお前の自由だぜ。";
			link.l1 = "了解だ。で、報酬はどうなるんだ？";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "俺が興味あるのは樹脂だけだ。その樽一つにつき金のドゥブロン十五枚払うぜ。俺の情報によれば、「ベンセチョ」 には百樽ほど積んでるらしい。";
			link.l1 = "なんてこった！そりゃあ大金だな！";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "ああ。もう言ったが、この品物は特に高価で珍しいんだ。";
			link.l1 = "これも密輸品だとあんたが言ったじゃねえか。";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "心配するな、店や密輸業者のところに持って行く必要はねえ。仕事が終わったら俺のところに来い。 お前の船は俺の造船所に係留して修理してやるし、夜中にこっそり全部の積み荷を降ろすぜ。誰にもバレやしねえよ。";
			link.l1 = "俺より先を読んでるな、旦那。よし、無駄にしてる暇はねえ。今すぐ出航の準備に向かうぜ。";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "ご武運を、船長。";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "素晴らしい！約束通り、君の船をドックに入れよう。今夜そこで荷を降ろす。自分の船に戻ってくれ、 こちらで金の用意をしておくからな。";
			link.l1 = "やろうぜ。";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
