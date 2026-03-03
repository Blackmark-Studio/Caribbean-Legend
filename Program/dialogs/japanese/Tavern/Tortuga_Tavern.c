// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしてたところだぜ。お前、忘れちまったのか…","今日はこれで三度目だぜ、この質問を持ち出すのは……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、 "+NPChar.name+"、また今度だな。","そうだ、なぜか忘れちまってたんだ……","「ああ、本当にこれで三度目だな……」","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "聞けよ、フランソワ・ゴンティエはどこにいる？もうトルトゥーガに着いてるはずなんだが。";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "アンリ・ティボーを探してるんだ。どこにいるか知らねえか？";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "アンリ・ティボーを探してるんだ。どこにいるか知らねえか？";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "教えてくれ、『サンタ・マルガリータ』という名のガレオン船が最近お前の植民地に寄港したことはあるか？ もしかして私掠船の戦利品としてか？";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "なあ、相棒、ガスパール・パルマンティエを探してるんだ。どこにいるか知らねえか？";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "ちょっと手を貸してくれねえか、相棒？ジョープ・ファン・デル・ヴィンクって男を探してるんだ。知ってるか？";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "フランソワ・ゴンティエ？誰だそいつ？そんな名前の男は知らねえな。";
			link.l1 = "奴はコルベット『の船長だ"+pchar.questTemp.Slavetrader.ShipName+"「。」";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "俺にはまったく見当もつかねえ。それに、その名のコルベットがうちの港に入港したことは絶対にねえと言い切れるぜ。";
			link.l1 = "そうかい、最近この町でよそ者を見かけたか？";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "いい質問だな！ここは港町であって、村じゃねえ。よそ者なんざ毎日やって来るさ。ただ、 妙な奴らが五人ばかりいるって話は聞いたぜ。いつもつるんでて、剣を抜く準備もできてるってな。\n巡回の連中もそいつらについて聞き込みしてたが、何もわからなかったらしい。でもな、 あいつらがコルベットで来たってことはねえよ。そんな船はこの辺りで見かけなかったからな、わかったか？";
			link.l1 = "ふむ……そうか、わかった。ありがとう。 "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "ティボー旦那はトルトゥーガで有名な人物だ。彼の邸宅は港役所の近くにある。\n酒場を出たら、そのまま港に向かって進め。港へ続くアーチに近づいたら、交差点で左に曲がり、 通りの突き当たりまで進むと赤い屋根の二階建ての石造りの建物が見えるはずだ。\nそれがティボー旦那の邸宅だ。";
			link.l1 = "ありがとう！これから彼に会いに行くぜ…";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "今日はティボー旦那が大人気だよ、さっき総督の使いが慌ててここに来たんだ。あの人も興味津々だったぜ。 そんなに見つけるのが難しいのか？ティボー旦那はずっと前から二階の部屋を借りてるんだ、屋敷があるのにさ。 何のためかは知らねえが、入ってくる回数の方が出ていくよりずっと多いんだよ。しかも、 あそこにいるのはいつも夕方だけだ。";
			link.l1 = "もしかすると、今ここにいるかもしれねえな。";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "いいや。彼は今晩八時まで戻らないと言っていたぜ。屋敷で探してみてもいいが、たぶん見つからねえと思うぜ。 俺はあいつが巡回用のラガー船で海に出ていくのを見たんだ。";
				link.l1 = "ありがとう！後であいつに会いに寄るぜ。";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "ああ。よければ、上がってきてもいいぜ。";
				link.l1 = "ありがとう！俺が会いに行ってくるぜ…";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "船の名前は全然覚えてねえ、「サンタ・マルガリータ」だったか「カスティーリャの娼婦」だったか……だが、やつらは拿捕したスペインのガレオン船を持ち込んできたんだ。しかもスループで拿捕したってんだから驚きだぜ！ これぞ本物の航海術ってやつだ！ガイウス・マルシェ、その船長が二日間も酒場で自慢しっぱなしさ――初めての航海でこの大戦果だとよ！\nああ、まったく英雄的な手柄だぜ、兵士もいねえ教会ネズミどもでいっぱいのガレオンに乗り込むなんてな。 どうやらあのカトリックの野郎どもは「自分でやる者には福がある」って言葉を忘れちまったらしいな……";
			link.l1 = "ああ、自分で努力する者を神は助ける――それは確かにユグノーの言葉だな。で、その運のいい船長をどうやって見つけりゃいいんだ？ ここトルトゥーガにいるのか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ああ、そんなこと俺にわかるかよ。もう長いことあいつは俺の酒場に顔を出してねえんだ。酔いが覚めた途端、 賞金でピカピカの新しい船を買って、まるで気が狂ったみてえに甲板を走り回ってたぜ。 今じゃマルシェがどこにいるかなんて全然知らねえ。トルトゥーガにいるかもしれねえし、海の上かもしれねえな。";
			link.l1 = "よし。まあ、話を聞かせてくれてありがとな、相棒！";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "いつでもどうぞ、旦那。俺たちの大切な船長のためなら、喜んで手を貸すぜ "+pchar.name+"、サン・ピエールの救世主よ！また後で寄ってくれよ！";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "ガスパールはお前たちの間でどんどん人気者になってるみたいだな。あいつの家は城壁のそばにあるぜ。 酒場を出て左に曲がり、港の方へ向かえ。ただし港には行くな、もう一度左に曲がって、 まっすぐ進んでから右に曲がるんだ。二階建ての家だぞ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "聞いたことねえな。";
			link.l1 = "もしかしたら別の名前で呼ばれているのかもしれねえ。ブリッグ船『バンテン』の船長として聞いたことはねえか？";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "そのブリッグのことも聞いたことがねえな。";
			link.l1 = "最近ここにいたって聞いたんだが。ちょっと銀貨を渡せば、記憶がよみがえったりしないか？";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "さて、自分でどこでそれを聞いたか考えてみな。まあ、銀貨はありがたく頂くぜ。";
			link.l1 = "今回は銀貨はなしってわけか。じゃあな。";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
