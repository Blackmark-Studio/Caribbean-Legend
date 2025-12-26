// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お聞きしましょう、ご質問は何でしょうか？"),"これで二度目のお尋ねですね…","あなたが尋ねようとしたのはこれで三度目です…","いつまで続くのだ！？私は植民地の案件で忙しい身なのに、まだ私を煩わせるのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も違う。"),"「確かに……だが、今ではなく、後で……」","聞いてみます……でも、もう少し後で……","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "閣下、投獄されている士官ロペ・モントロの件で参りました……";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでにすべて奪われております。これ以上何をお望みですか？","「まだお取りにならなかった物が何か残っておりますか？」");
            link.l1 = RandPhraseSimple("少し見て回っているだけです……","ちょっと確認しているだけです、何か取り忘れたかもしれませんので……");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "くそっ、盗賊どもめ！ハバナを襲うとは何事だ！？何が目的だ！？";
			link.l1 = "少し考えてみれば、お分かりいただけます。";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "金に決まってるだろう！他にお前ら野郎どもが興味あるものなんて金しかねえじゃねえか！？だが、 うちには金なんてない……倉庫にちょっとばかりあるだけだ。";
			link.l1 = "ははは……いや、俺たちは金には興味ねえ。ここに来たのは象牙のためさ……黒い象牙だ。わかるか？";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "はっ！奴隷目当てで来たのだろうと睨んでいたぞ。しかし奴らは砦に収容されている。援軍はすでに向かっており、 貴様らの一味はすぐに壊滅するだろう。";
				link.l1 = "くそっ！よし、そこに座って動くな……さあ、ここを出るぞ！ちくしょう……";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "「しかし、どうして……どうやってそれを知ったのですか？」";
				link.l1 = "はっ！5,000人もの奴隷を一箇所に集めて誰にも気付かれないと思うなんて、馬鹿だけだぜ。 ここからトルトゥーガのクソったれな場所まで臭ってくるじゃねえか……分かってるだろうが、俺たちはそいつらをお前から取り上げるからな。";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "よろしい、どうせあなたの勝ちですし、我々はその暴力に屈するしかありません。しかし、 あの強奪やスペイン軍艦二隻を沈めた後で、正義の裁きを逃れられるとは思わないでください。";
			link.l1 = "そんなに息巻くなよ、心臓発作を起こすぞ。ここに座って、動くんじゃない…";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "これは興味深い……また苦情ですか？";
			link.l1 = "いえいえ、とんでもございません、閣下。ロペは昔からの軍の友人でして、ヨーロッパで共に戦った仲でございます……彼の力になりたいと存じておりますので、どうか閣下のお力添えを賜りたく参りました。";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "ふむ……まあ、私のところへ来たということは、すでにこの…馬鹿げた話をご存知なのでしょう？";
			link.l1 = "はい、閣下。";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "ドン・ロサリオ・グスマンに連絡を取ることをお勧めいたします。\n彼もあなたと同様に、ドン・ロペ・モンテロを助けたいと考えております。\n彼は被害者と接触を試みましたが、交渉は実を結びませんでした。\n彼に会ってください、詳細を説明してくれるでしょう。\nドン・ロサリオは午後四時から八時まで街中で見つけることができます。\n彼は毎日、市衛兵の詰所をすべて巡回しております。";
			link.l1 = "「ありがとうございます、閣下！」";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
